#include "AGTerrain.h"

#include "Engine/Managers/AGInputManager.h"

#include <math.h> 
#include <cmath>

AGTerrain::AGTerrain()
{
	std::string fullPath = "data/meshes/terrain.agmsh";

	ifstream in( fullPath, ios::binary );
#define READ( a ) in.read( (char*)&a, sizeof( a ) )

	char header[ 6];
	in.read( header, 5 );
	header[ 5 ] = '\0';

	if( strcmp( header, "AGMSH" ) != 0 )
	{
		return; 
	}

	int nSubMeshes;
	READ( nSubMeshes );
	if( nSubMeshes == 0 )
	{
		AGError() << "There are 0 sub meshes in "; 
		return; 
	}

	int nVertices; 
	READ( nVertices );
	int sqrnVertices = sqrt( nVertices );
	AGDebug() << nVertices << " " << sqrnVertices;

	std::vector< AGVertex > verticesForMap; 
	std::vector< AGVertex > vertices; 

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
		verticesForMap.push_back( vertex );
		vertices.push_back( vertex );
		m_vertices.push_back( vertex.pos );
		m_normals.push_back( vertex.normal );

		if( i != 0 && i % sqrnVertices == 0 )
		{
			m_vertexMap.push_back( verticesForMap );
			verticesForMap.clear(); 
		}
	}

	int nIndices; 
	READ( nIndices );
	for( int i = 0; i < nIndices; i++ )
	{
		int index;
		READ( index ); 
		m_indices.push_back( index );
	}

	m_vbo = new AGBuffer< AGVertex >( vertices, AGBufferType::Vertex );
	m_ibo = new AGBuffer< int >( m_indices, AGBufferType::Index );

	m_material = new AGMaterial; 
	m_material->loadFrom( in );
	delete m_material; 

	AGVec3 v1;
	AGVec3 v2; 

	READ( v1.x );
	READ( v1.y );
	READ( v1.z );
	READ( v2.x );
	READ( v2.y );
	READ( v2.z );

	m_border = v1; 
	m_border2 = v2; 

	m_shader = AGResourceManager::getInstance().getShader( L"terrain" );

	m_heightSlot = m_difSlot = 0; 

	m_textureSize.setSize( 512, 512 );

	D3D10_TEXTURE2D_DESC txDesc; 
	ZeroMemory( &txDesc, sizeof( txDesc ) );
	txDesc.Width = m_textureSize.getWidth(); 
	txDesc.Height = m_textureSize.getHeight(); 
	txDesc.ArraySize = txDesc.MipLevels = 1;
	txDesc.Format = DXGI_FORMAT_R8_UNORM;
	txDesc.SampleDesc.Count = 1;
	txDesc.SampleDesc.Quality = 0; 
	txDesc.Usage = D3D10_USAGE_DYNAMIC;
	txDesc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	txDesc.BindFlags = D3D10_BIND_SHADER_RESOURCE;  

	std::list< AGSurface* > surfaces = AGGraphics::getInstance().getSurfaces(); 

	m_txArray = new AGTexture2DArray; 
	m_txArray->append( L"data/textures/grass2.png" );
	m_txArray->append( L"data/textures/grass3.png" );
	m_txArray->append( L"data/textures/rock.jpg" );
	
	m_txArray->reloadArray();

	m_height = new AGTexture2D( txDesc );
	m_dif = new AGTexture2D( txDesc );
	m_rock = new AGTexture2D( txDesc );
	m_difSlot = m_shader->addNewTextureVar( "txDiff" );
	m_heightSlot = m_shader->addNewTextureVar( "txHeight" );
	m_rockSlot = m_shader->addNewTextureVar( "txRock" ); 
	m_mapsSlot = m_shader->addNewTextureVar( "txMaps" );
	m_radiusSlot = m_shader->addNewVar( "brushRadius" );
	m_cursorPosSlot = m_shader->addNewVar( "cursorPos" );

	m_circle = new AGCircleShape( 3.0f, AGColor( 0.0f, 1.0f, 0.0f ) );
	m_line = new AGLine( v1, v2 ); 

	std::vector< ID3D10Texture2D* > alphaTextures1 = m_rock->getTextures();
	std::vector< ID3D10Texture2D* > alphaTextures2 = m_height->getTextures();
	std::vector< ID3D10Texture2D* > alphaTextures3 = m_dif->getTextures();
	for( int i = 0; i < alphaTextures1.size(); i++ )
	{
		ID3D10Texture2D* alphaTexture1 = alphaTextures1[ i ];
		ID3D10Texture2D* alphaTexture2 = alphaTextures2[ i ];
		ID3D10Texture2D* alphaTexture3 = alphaTextures3[ i ];

		D3D10_MAPPED_TEXTURE2D mappedAlphaTexture1; 
		alphaTexture1->Map( D3D10CalcSubresource( 0, 0, 1 ), D3D10_MAP_WRITE_DISCARD, 0, &mappedAlphaTexture1 );

		D3D10_MAPPED_TEXTURE2D mappedAlphaTexture2; 
		alphaTexture2->Map( D3D10CalcSubresource( 0, 0, 1 ), D3D10_MAP_WRITE_DISCARD, 0, &mappedAlphaTexture2 );

		D3D10_MAPPED_TEXTURE2D mappedAlphaTexture3; 
		alphaTexture3->Map( D3D10CalcSubresource( 0, 0, 1 ), D3D10_MAP_WRITE_DISCARD, 0, &mappedAlphaTexture3 );

		unsigned char* alphaTexels1 = ( unsigned char* )mappedAlphaTexture1.pData; 
		unsigned char* alphaTexels2 = ( unsigned char* )mappedAlphaTexture2.pData; 
		unsigned char* alphaTexels3 = ( unsigned char* )mappedAlphaTexture3.pData; 

		for( int row = 0; row < m_textureSize.getHeight(); row++ )
		{
			int rowStart = row * mappedAlphaTexture1.RowPitch;
			for( int col = 0; col < m_textureSize.getWidth(); col++ )
			{ 
				alphaTexels3[ rowStart + col ] = 255;
				alphaTexels2[ rowStart + col ] = 0;
				alphaTexels1[ rowStart + col ] = 0;
			}
		}
		alphaTexture1->Unmap( D3D10CalcSubresource( 0, 0, 1 ) );
		alphaTexture2->Unmap( D3D10CalcSubresource( 0, 0, 1 ) );
		alphaTexture3->Unmap( D3D10CalcSubresource( 0, 0, 1 ) );
	} 
	m_brushMap.load( "data/textures/1.bmp" );

	setRadius( 8 );
	setHardness( 0.8f );
	setTextureIndex( 2 );
}

AGTerrain::~AGTerrain()
{

}

void AGTerrain::draw(AGSurface* surface)
{
	ID3D10Device* device = surface->getDevice();

	assert( m_vbo );
	assert( m_ibo );

	m_vbo->apply( surface );
	m_ibo->apply( surface );

	m_shader->setMap( m_heightSlot, m_height, surface );
	m_shader->setMap( m_difSlot, m_dif, surface );
	m_shader->setMap( m_rockSlot, m_rock, surface );
	m_shader->setArray( m_mapsSlot, m_txArray, surface );

	m_shader->setWorldMatrix( AGMatrix() );
	m_shader->apply( surface );

	device->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

	AGRasterizeState* state = AGGraphics::getInstance().getRasterizeState( surface->getDevice() ); 

	if( surface->getSurfaceMode() == AGSurface::EdgedFaces )
	{
		m_shader->applyNextPass();
		device->RSSetState( state->solid );
		device->DrawIndexed( m_indices.size(), 0, 0 );	

		m_shader->applyNextPass();
		device->RSSetState( state->wireframe);
		device->DrawIndexed( m_indices.size(), 0, 0 );
	}
	else
	{
		if( surface->getSurfaceMode() == AGSurface::Wireframe )
		{
			m_shader->applyNextPass(); 
			m_shader->applyNextPass();
			device->RSSetState( state->wireframe );
			device->DrawIndexed( m_indices.size(), 0, 0 );	
		} 
		else 
		{
			m_shader->applyNextPass();
			device->RSSetState( state->solid ); 
			device->DrawIndexed( m_indices.size(), 0, 0 );	
		}
	}	

	device->RSSetState( state->solid );

	if( AGInputManager::getInstance().isKeyDown( '1' ) )
	{
		setTextureIndex( 1 );
	}
	else if( AGInputManager::getInstance().isKeyDown( '2' ) )
	{
		setTextureIndex( 2 );
	}
	else if( AGInputManager::getInstance().isKeyDown( '3' ) )
	{
		setTextureIndex( 3 );
	}
}

bool AGTerrain::mouseClickEvent(AGMouseButton button, AGSurface* surface)
{	
	calculateRays( surface, AGMatrix() );
	float dist = intersect( m_rayOrigin, m_rayDir );
	return dist > 0.0f; 
}

bool AGTerrain::mouseMoveEvent(AGSurface* surface)
{
	calculateRays( surface, AGMatrix() );
	float dist = intersect( m_rayOrigin, m_rayDir );
	return dist > 0.0f; 
}

float AGTerrain::intersect(const AGVec3& rayOrigin, const AGVec3& rayDir)
{
	float retDist = -1.0f;
	int nIndices = m_indices.size() - 2;  

	AGVec3 from; 
	AGVec3 normal; 

	for( int i = 0; i < nIndices; i++ )
	{
		AGVec3 v1 = m_vertices[ m_indices[ i ] ];
		AGVec3 v2 = m_vertices[ m_indices[ i + 1 ] ];
		AGVec3 v3 = m_vertices[ m_indices[ i + 2 ] ];

		AGMath::IntersectResult res = AGMath::intersectTriangle( rayOrigin, rayDir, AGMath::Triangle( v1, v2, v3 ), false ); 

		if( res.hit )
		{
			AGVec3 u = v1 - v2; 
			AGVec3 v = v3 - v2; 
			if( retDist < 0 )
			{
				retDist = res.distance; 
				normal = m_normals[ m_indices[ i ] ];
			}
			else 
			{
				retDist = min( retDist, res.distance ); 
				if( retDist > res.distance )
				{
					normal = m_normals[ m_indices[ i ] ];
				}
			}
		}
	}

	if( retDist > 0.0f )
	{
		AGVec3 pos = rayOrigin + rayDir * retDist;
		m_intersectPos = pos; 
		m_shader->setVar( m_cursorPosSlot, pos );

		AGVec2 border( m_border.x, m_border.z );

		AGVec2 newPos( pos.x, pos.z );
		newPos += border;
		newPos.y = abs(newPos.y - border.y * 2.0f );

		newPos.x = std::floor( newPos.x * m_textureSize.getWidth() / (border.x * 2.0f) + 0.5f );
		newPos.y = std::floor( newPos.y * m_textureSize.getWidth() / (border.y * 2.0f) + 0.5f );

		int radiusInPixels = std::floor( m_radius * m_textureSize.getWidth() / ( border.x * 2.0f ) + 0.5f ); 

		if( AGInputManager::getInstance().isButtonPressed( "LMB" ) )
		{
			std::vector< ID3D10Texture2D* > alphaTextures1 = m_rock->getTextures();
			std::vector< ID3D10Texture2D* > alphaTextures2 = m_height->getTextures();
			std::vector< ID3D10Texture2D* > alphaTextures3 = m_dif->getTextures();
			for( int i = 0; i < alphaTextures1.size(); i++ )
			{
				ID3D10Texture2D* alphaTexture1 = alphaTextures1[ i ];
				ID3D10Texture2D* alphaTexture2 = alphaTextures2[ i ];
				ID3D10Texture2D* alphaTexture3 = alphaTextures3[ i ];

				assert( alphaTexture1 );
				assert( alphaTexture2 );
				assert( alphaTexture3 );

				D3D10_MAPPED_TEXTURE2D mappedAlphaTexture1; 
				alphaTexture1->Map( D3D10CalcSubresource( 0, 0, 1 ), D3D10_MAP_WRITE_DISCARD, 0, &mappedAlphaTexture1 );

				D3D10_MAPPED_TEXTURE2D mappedAlphaTexture2; 
				alphaTexture2->Map( D3D10CalcSubresource( 0, 0, 1 ), D3D10_MAP_WRITE_DISCARD, 0, &mappedAlphaTexture2 );

				D3D10_MAPPED_TEXTURE2D mappedAlphaTexture3; 
				alphaTexture3->Map( D3D10CalcSubresource( 0, 0, 1 ), D3D10_MAP_WRITE_DISCARD, 0, &mappedAlphaTexture3 );

				unsigned char* alphaTexels1 = ( unsigned char* )mappedAlphaTexture1.pData; 
				unsigned char* alphaTexels2 = ( unsigned char* )mappedAlphaTexture2.pData; 
				unsigned char* alphaTexels3 = ( unsigned char* )mappedAlphaTexture3.pData;

				for( int row = -radiusInPixels; row < radiusInPixels; row++ )
				{
					int rowStart = ( row + newPos.y ) * mappedAlphaTexture1.RowPitch;
					if( rowStart < 0 || rowStart >= m_textureSize.getHeight()*mappedAlphaTexture1.RowPitch )
					{
						break; 
					}
					for( int col = -radiusInPixels; col < radiusInPixels; col++ )
					{
						int colStart = col + newPos.x; 
						if( colStart < 0 || colStart >= mappedAlphaTexture1.RowPitch  )
						{
							continue; 
						}

						int alpha = 255 * QColor( m_scaledMap.pixel( row + radiusInPixels, col + radiusInPixels ) ).redF();

						if( m_textureIndex == 1 )
						{
							alphaTexels1[ rowStart + colStart ] = min( alphaTexels1[ rowStart + colStart ] + alpha, 255 );
							alphaTexels2[ rowStart + colStart ] = max( alphaTexels2[ rowStart + colStart ] - alpha, 0 );
							alphaTexels3[ rowStart + colStart ] = max( alphaTexels3[ rowStart + colStart ] - alpha, 0 );
						}
						else if( m_textureIndex == 2 )
						{
							alphaTexels1[ rowStart + colStart ] = max( alphaTexels1[ rowStart + colStart ] - alpha, 0 );
							alphaTexels2[ rowStart + colStart ] = min( alphaTexels2[ rowStart + colStart ] + alpha, 255 );
							alphaTexels3[ rowStart + colStart ] = max( alphaTexels3[ rowStart + colStart ] - alpha, 0 );
						}
						else if( m_textureIndex == 3 )
						{
							alphaTexels1[ rowStart + colStart ] = max( alphaTexels1[ rowStart + colStart ] - alpha, 0 );
							alphaTexels2[ rowStart + colStart ] = max( alphaTexels2[ rowStart + colStart ] - alpha, 0 );
							alphaTexels3[ rowStart + colStart ] = min( alphaTexels3[ rowStart + colStart ] + alpha, 255 );
						}
					}
				}
				alphaTexture1->Unmap( D3D10CalcSubresource( 0, 0, 1 ) );
				alphaTexture2->Unmap( D3D10CalcSubresource( 0, 0, 1 ) );
				alphaTexture3->Unmap( D3D10CalcSubresource( 0, 0, 1 ) );
			} 
		}
	}
	return retDist; 
}

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

void AGTerrain::setPaintingMode(bool value)
{
	m_paintingMode = value; 
}

void AGTerrain::setRadius( float radius)
{
	m_radius = radius; 
	m_circle->setRadius( m_radius );
	m_circle->setupShape();
	m_shader->setAsFloat( m_radiusSlot, m_radius );

	int radiusInPixels = std::floor( m_radius * m_textureSize.getWidth() / ( m_border.x * 2.0f ) + 0.5f ); 

	m_scaledMap = m_brushMap.scaled( radiusInPixels * 2, radiusInPixels * 2 );
}

void AGTerrain::setHardness(float hardness)
{
	m_harndess = hardness; 
}

void AGTerrain::setTextureIndex(int index)
{
	m_textureIndex = index; 
}

void AGTerrain::addTexture(const std::wstring& fileName)
{
	m_txArray->append( fileName );
	m_txArray->reloadArray(); 
}

const AGVec3& AGTerrain::getIntersectPos() const
{
	return m_intersectPos; 
}
