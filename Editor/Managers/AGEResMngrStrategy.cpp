#include "AGEResMngrStrategy.h"

#include "UI/AGELoadingWidgets.h"

#include <windows.h>
#include <future>

AGEResMngrStrategy::AGEResMngrStrategy(QApplication& app) : m_app( app )
{

}

AGEResMngrStrategy::~AGEResMngrStrategy()
{

}

void AGEResMngrStrategy::initShaders()
{
	HANDLE findHandle = INVALID_HANDLE_VALUE; 
	WIN32_FIND_DATA findData; 

	findHandle = FindFirstFile( L"data\\shaders\\*.*", &findData );

	if( findHandle == INVALID_HANDLE_VALUE )
	{
		AGError() << "Error while finding first file in data/shaders/" << (int)GetLastError(); 
		FindClose( findHandle );
		return; 
	}
	std::vector< std::future< AGShader* > > results; 
	std::list< std::wstring > shaders; 
	AGDebug() << "List of shaders: "; 
	do
	{
		if( ~( findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) && ( findData.cFileName[ 0 ] != '.' ) )
		{
			shaders.push_back( findData.cFileName );
			std::wstring str( findData.cFileName );
			results.push_back( std::async( &AGEResMngrStrategy::loadShader, this, str ) );
			//results.push_back( std::async( &AGEResMngrStrategy::loadShader, this, findData.cFileName ) );			
		}
	}
	while( FindNextFile( findHandle, &findData ) );
	FindClose( findHandle );
	int curShader = 0;
	int progress = 1; 
	AGELoadingWidget& widget = AGELoadingWidget::getInstance();
	widget.resetAndShow();

	for( std::wstring shaderName : shaders )
	{
		std::wstring label = L"Loading shader: " + shaderName; 	
		widget.setLabel( label );
		m_app.processEvents();

		AGShader* shader = results[ curShader++ ].get();
		shaderName = shaderName.substr( 0, shaderName.find( L"." ) );
		m_effects[ shaderName ] = shader;

		widget.setProgress( (float)progress / shaders.size() * 100 );
		progress++; 
		m_app.processEvents();
		AGDebug() << "Shader: " << shaderName; 
	}
	widget.close();
}

AGShader* AGEResMngrStrategy::getShader(const std::wstring& shaderName)
{
	auto iter = m_effects.find( shaderName );

	if( iter == m_effects.end() )
		return nullptr; 
	return iter->second;
}

#define READ( a ) in.read( (char*)&a, sizeof( a ) )

AGMesh* AGEResMngrStrategy::getMesh(const std::string& fileName)
{
	auto iter = m_meshes.find( fileName ); 

	AGMesh* mesh = nullptr; 

	if( iter == m_meshes.end() )
	{
		AGELoadingWidget& widget = AGELoadingWidget::getInstance();

		widget.resetAndShow();
		widget.setLabel( "Loading mesh: " + fileName );
		mesh = loadMesh( fileName );
		assert( mesh );
		widget.close();
		m_meshes[ fileName ] = mesh; 
	}
	else 
	{
		mesh = iter->second; 
	}
	return mesh; 
}

AGTexture2D* AGEResMngrStrategy::getTexture(const std::wstring& fileName)
{
	auto iter = m_textures.find( fileName ); 

	AGTexture2D* texture = nullptr; 

	if( iter == m_textures.end() )
	{
		texture = loadTexture( fileName );
		m_textures[ fileName ] = texture; 
	}
	else 
	{
		texture = iter->second; 
	}
	return texture; 
}

///////////////////////////////////////////////////////////////////////////
///В общем файл меша состоит приблизительно из( в процентном соотношении ):
/// * 3%  - Заголовок и количество под-мешей
/// * 35% - Информация о вершинах
/// * 40% - Инфорация о индексах
/// * 20% - Инфорация о материале
/// * 1%  - Информация о текстуре 
/// * 1%  - Информации о ограничивающем объёме
///////////////////////////////////////////////////////////////////////////

const float verticesInfo = 35.0f; 
const float materialInfo = 20.0f;
const float indexInfo = 40.0f;

AGMesh* AGEResMngrStrategy::loadMesh(const std::string& fileName)
{
	AGMeshLoadingData* meshData = new AGMeshLoadingData; 
	AGMesh* mesh = new AGMesh; 

	std::string fullPath = "data/meshes/";
	fullPath += fileName; 

	std::ifstream in( fullPath, ios::binary );

	char header[ 6];
	in.read( header, 5 );
	header[ 5 ] = '\0';

	AGELoadingWidget& widget = AGELoadingWidget::getInstance();
	widget.resetAndShow(); 

	widget.setLabel( "Loading: " + fileName );
	if( strcmp( header, "AGMSH" ) != 0 )
	{
		AGError() << "Couldn't load mesh file: " << fileName; 
		return mesh; 
	}

	int nSubMeshes;
	READ( nSubMeshes );
	if( nSubMeshes == 0 )
	{
		AGError() << "There are 0 sub meshes in " << fileName; 
		return mesh; 
	}
	widget.setProgress( 3 );
	m_app.processEvents();

	for( int i = 0; i < nSubMeshes; i++ )
	{
		widget.setLabel( "Loading: " + to_string( i ) + " submesh" );
		meshData->subMeshes.push_back( new AGSubMesh( mesh, loadSubMesh( in ) ) );
	}
	AGVec3 v1;
	AGVec3 v2; 

	READ( v1.x );
	READ( v1.y );
	READ( v1.z );
	READ( v2.x );
	READ( v2.y );
	READ( v2.z );

	meshData->boundingBox = new AGBoxShape( v1, v2 );

	mesh->initFrom( meshData );
	widget.setProgress( 100 );

	return mesh;
}

AGSubMeshLoadingData* AGEResMngrStrategy::loadSubMesh( std::ifstream& in )
{
	AGSubMeshLoadingData* subMeshData = new AGSubMeshLoadingData; 

	int nVertices; 
	READ( nVertices );

	AGELoadingWidget& widget = AGELoadingWidget::getInstance();

	int curProgress = widget.getProgress(); 

	for( int i = 0; i < nVertices; i++ )
	{
		AGVertex vertex; 

		READ( vertex.pos.x );
		READ( vertex.pos.y );
		READ( vertex.pos.z );

		READ( vertex.normal.x );
		READ( vertex.normal.y );
		READ( vertex.normal.z );

		READ( vertex.binormal.x );
		READ( vertex.binormal.y );
		READ( vertex.binormal.z );

		READ( vertex.tangent.x );
		READ( vertex.tangent.y );
		READ( vertex.tangent.z );

		READ( vertex.uv.x );
		READ( vertex.uv.y );
		subMeshData->vertices.push_back( vertex );
		widget.setProgress( curProgress + (float)i / nVertices * verticesInfo ); 
		m_app.processEvents();
	}

	curProgress = widget.getProgress();

	int nIndices; 
	READ( nIndices );
	for( int i = 0; i < nIndices; i++ )
	{
		int index;
		READ( index ); 
		subMeshData->indices.push_back( index );
		widget.setProgress( curProgress + (float)i / nIndices * indexInfo ); 
		m_app.processEvents();
	}

	subMeshData->vertexBufffer = new AGBuffer< AGVertex >( subMeshData->vertices, AGBufferType::Vertex );
	subMeshData->indexBuffer = new AGBuffer< int >( subMeshData->indices, AGBufferType::Index );

	subMeshData->material = loadMaterial( in );

	return subMeshData;
}

AGMaterial* AGEResMngrStrategy::loadMaterial( std::ifstream& in )
{
	AGMaterialLoadingData* materialData = new AGMaterialLoadingData; 

	AGELoadingWidget& widget = AGELoadingWidget::getInstance();
	widget.setLabel( "Loading: material" );

	int curProgress = widget.getProgress(); 

	char buf[ 512 ];
	wchar_t wbuf[ 512 ];
	for( int i = 0; i < 12; i++ )
	{
		int len;
		READ( len );
		if( len > 511 )
		{
			AGError() << "Too long texture name"; 
			continue;
		}

		in.read( buf, len );
		buf[ len ] = '\0';
		mbstowcs( wbuf, buf, len + 1 ); 
		materialData->textures[ i ] = wbuf; 

		int zero; 
		READ( zero );
		widget.setProgress( curProgress + (float)i / 12 * indexInfo ); 
		m_app.processEvents();
	}

	std::wstring fileName;

	curProgress = widget.getProgress(); 

	const std::wstring shaderNames[] = 
	{
		L"amb",
		L"dif",
		L"spcclr",
		L"spclvl",
		L"gls",
		L"slfilm",
		L"opc",
		L"fltrclr",
		L"bmp",
		L"rfl",
		L"rfr",
		L"nrm"
	};

	for( int i = 0; i < 12; i++ )
	{
		std::wstring texture = materialData->textures[ i ];
		if( texture != L"NULL" )
		{
			fileName += shaderNames[ i ];
		}
		widget.setProgress( curProgress + (float)i / 12 * indexInfo ); 
		m_app.processEvents();
	}

	curProgress = widget.getProgress(); 
	materialData->shader = getShader( fileName );

	list< AGSurface* > surfaces = AGGraphics::getInstance().getSurfaces(); 

	std::future< AGTexture2D* > results[ 12 ];

	for( int i = 0; i < 12; i++ )
	{
		std::wstring textureName = materialData->textures[ i ];
		if( textureName != L"NULL" )
		{
			results[ i ] = std::async( &AGEResMngrStrategy::getTexture, this, textureName );
			widget.setLabel( L"Loading texture: " + textureName );
		}
		widget.setProgress( curProgress + (float)i / 12 * indexInfo ); 
		m_app.processEvents();
	}

	for( int i = 0; i < 12; i++ )
	{
		std::wstring textureName = materialData->textures[ i ];
		if( textureName != L"NULL" )
		{
			materialData->resources[ i ] = AGResPtr( results[ i ].get() ); 
		}
	}

	materialData->surfaces = std::move( surfaces );

	return new AGMaterial( materialData );
}

AGTexture2D* AGEResMngrStrategy::loadTexture(const std::wstring& fileName)
{
	AGTexture2DLoadingData* textureData = new AGTexture2DLoadingData; 

	std::wstring fullPath = L"data/textures/";
	fullPath += fileName; 

	std::list< AGSurface* > surfaces = AGGraphics::getInstance().getSurfaces(); 
	bool firstInit = true; 

	HANDLE texHandle;

	D3DX10_IMAGE_LOAD_INFO loadInfo; 
	ZeroMemory( &loadInfo, sizeof( D3DX10_IMAGE_LOAD_INFO ) );
	loadInfo.BindFlags = D3D10_BIND_SHADER_RESOURCE; 
	loadInfo.MiscFlags = D3D10_RESOURCE_MISC_SHARED; 
	loadInfo.Format = DXGI_FORMAT_BC1_UNORM; 

	int curSurface = 1;

	for( AGSurface* surface : surfaces )
	{
		ID3D10ShaderResourceView* view; 
		if( firstInit )
		{
			handleDXError( D3DX10CreateShaderResourceViewFromFile( surface->getDevice(), &fullPath[ 0 ], &loadInfo, NULL, &view, NULL ) );

			AGSucces() << fileName << " was loaded";

			ID3D10Resource* resource; 

			view->GetResource( &resource );

			IDXGIResource* res( NULL );
			handleDXError( resource->QueryInterface( __uuidof( IDXGIResource ), (void**)&res ) );

			handleDXError( res->GetSharedHandle( &texHandle ) );
			firstInit = false;
		}
		else 
		{
			IDXGIResource* resource;

			handleDXError( surface->getDevice()->OpenSharedResource( texHandle, __uuidof( IDXGIResource ), (void**)&resource ) );

			ID3D10Resource* res;
			handleDXError( resource->QueryInterface( __uuidof( ID3D10Resource ), (void**)&res ) ); 

			D3D10_SHADER_RESOURCE_VIEW_DESC srvDesc; 
			D3D10_RESOURCE_DIMENSION type; 
			res->GetType( &type );

			if( type == D3D10_RESOURCE_DIMENSION_TEXTURE2D )
			{
				D3D10_TEXTURE2D_DESC desc;
				ID3D10Texture2D* texture = (ID3D10Texture2D*)res; 
				texture->GetDesc( &desc );

				srvDesc.Format = desc.Format; 
				srvDesc.Texture2D.MipLevels = desc.MipLevels;
				srvDesc.Texture2D.MostDetailedMip = 0; 
				srvDesc.ViewDimension = D3D10_SRV_DIMENSION_TEXTURE2D; 
			}

			handleDXError( surface->getDevice()->CreateShaderResourceView( res, &srvDesc, &view ) );
		}
		curSurface++; 
		textureData->views.push_back( view ); 
	}

	return new AGTexture2D( textureData );
}

AGShader* AGEResMngrStrategy::loadShader(const std::wstring& shaderName)
{
	AGShaderLoadingData* shaderData = new AGShaderLoadingData; 
	shaderData->type = 0; 
	shaderData->surfaces = AGGraphics::getInstance().getSurfaces();

	int shadersFlags = D3D10_SHADER_ENABLE_STRICTNESS; 

	const wstring mapNames[] = 
	{
		L"amb",
		L"dif",
		L"spcclr",
		L"spclvl",
		L"gls",
		L"slfilm",
		L"opc",
		L"fltrclr",
		L"bmp",
		L"rfl",
		L"rfr",
		L"nrm"
	};

	const int mapTypes[] = 
	{
		AGShaderMap::Amb,
		AGShaderMap::Dif,
		AGShaderMap::SpecColor,
		AGShaderMap::SpecLvl,
		AGShaderMap::Gloss,
		AGShaderMap::SelfIllum,
		AGShaderMap::Opacity,
		AGShaderMap::FilterColor,
		AGShaderMap::Bump,
		AGShaderMap::Reflaction,
		AGShaderMap::Refraction,
		AGShaderMap::Normals
	};

	std::wstring tempStr = shaderName; 
	tempStr = tempStr.substr( 0, tempStr.find( L"." ) );
	int curMap = 0;
	int findPos = -1; 

	if( shaderName == L"billboard.fx" )
	{
		shaderData->type |= AGShaderMap::Dif; 
	}
	else 
	{
		for( int i = 0; i < 12; i++ )
		{
			findPos = tempStr.find( mapNames[ i ] );
			if( findPos != std::wstring::npos )
			{
				shaderData->type |= mapTypes[ i ];
				tempStr = tempStr.substr( findPos + mapNames[ i ].length() );
			}
		}
	}

	const string textResourcesNames[] = 
	{
		"txAmb",
		"txDiff",
		"txSpecClr",
		"txSpecLvl",
		"txGloss",
		"txSelfIllum",
		"txOpac",
		"txFiltClr",
		"txBump",
		"txRefl",
		"txRefr",
		"txNorm"
	};

	std::wstring fullPath = L"data/shaders/";
	fullPath+= shaderName; 

	for( AGSurface* surface : shaderData->surfaces )
	{
		ID3D10Effect* dxEffect; 
		ID3D10Device* device = surface->getDevice();

		handleDXShaderError( D3DX10CreateEffectFromFile( 
			&fullPath[0], NULL, NULL, "fx_4_0", shadersFlags,
			NULL, device, NULL, NULL, &dxEffect, &blob, NULL ) );

		AGEffect* agEffect = new AGEffect; 
		agEffect->dxEffect = dxEffect; 

		for( int i = 0; i < 12; i++ )
		{
			if( shaderData->type & mapTypes[ i ] )
			{
				ID3D10EffectShaderResourceVariable* resVar = dxEffect->GetVariableByName( textResourcesNames[ i ].c_str() )->AsShaderResource();
				agEffect->maps[ i ] = resVar; 
			}
		}

		agEffect->cameraPos = dxEffect->GetVariableByName( "cameraPos" )->AsVector(); 
		agEffect->worldMatrix = dxEffect->GetVariableByName( "mtxWorld" )->AsMatrix();
		agEffect->viewMatrix = dxEffect->GetVariableByName( "mtxView" )->AsMatrix();
		agEffect->projMatrix = dxEffect->GetVariableByName( "mtxProj" )->AsMatrix();

		shaderData->effects[ surface ] = agEffect; 
	}

	return new AGShader( shaderData );
}

