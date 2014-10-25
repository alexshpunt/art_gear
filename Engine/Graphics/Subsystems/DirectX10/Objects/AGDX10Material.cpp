#include "AGDX10Material.h"

#include <vector>

#include "AGDX10Camera.h"
#include "Managers/AGLogger.h"

AGDX10Material::AGDX10Material()
{
}

AGDX10Material::~AGDX10Material()
{

}

const wstring& AGDX10Material::getTexture( int index ) const
{
	if( index >= 0 && index < 12 )
		return m_textures[ index ];
	else 
		return m_textures[ 0 ];
}

void AGDX10Material::loadFrom( ifstream& in, ID3D10Device* device )
{
	#define READ( a ) in.read( (char*)&a, sizeof( a ) )
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
		m_textures[ i ] = wbuf; 

		int zero; 
		READ( zero );
	}
	
	wstring fileName = L"data/shaders/";

	const wstring shaderNames[] = 
	{
		L"amb",
		L"dif",
		L"spcclr",
		L"spclvl",
		L"gls",
		L"slfilm",
		L"opc",
		L"fltclr",
		L"bmp",
		L"rfl",
		L"rfr",
		L"nrm"
	};

	vector< AGDX10TextureResource > textResources; 
	for( int i = 0; i < 12; i++ )
	{
		wstring texture = m_textures[ i ];
		if( texture != L"NULL" )
		{
			fileName += shaderNames[ i ];
		}
	}
	fileName += L".fx";

	int shadersFlags = D3D10_SHADER_ENABLE_STRICTNESS | D3D10_SHADER_DEBUG; 
#ifdef _DEBUG
	shadersFlags |= D3D10_SHADER_DEBUG; 
#endif 
	ID3D10Blob* blob; 
	
	HRESULT hr = S_OK; 
	hr = D3DX10CreateEffectFromFile( 
		&fileName[0], NULL, NULL, "fx_4_0", shadersFlags,
		 NULL, device, NULL, NULL, &m_effect, &blob, NULL 
	);  
	if( FAILED( hr ) )
	{
		AGError() << "Couldn't load dx10 shader: " << fileName;
		if( blob )
			AGError() << (char*)blob->GetBufferPointer();
		return; 
	}

	m_worldVar = m_effect->GetVariableByName( "mtxWorld" )->AsMatrix();
	m_viewVar = m_effect->GetVariableByName( "mtxView" )->AsMatrix();
	m_projectionVar = m_effect->GetVariableByName( "mtxProj" )->AsMatrix();

	const string textResourcesNames[] = 
	{
		"txAmb", // Ambient
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

	for( int i = 0; i < 12; i++ )
	{
		wstring texture = m_textures[ i ];
		if( texture != L"NULL" )
		{
			AGDX10TextureResource* textResource = new AGDX10TextureResource; 
			textResource->var = m_effect->GetVariableByName( textResourcesNames[ i ].c_str() )->AsShaderResource();
			wstring fullFileName = L"data/textures/";
			fullFileName += texture; 
			hr = D3DX10CreateShaderResourceViewFromFile( device, &fullFileName[ 0 ], NULL, NULL, &(textResource->view), NULL );
			if( FAILED( hr ) )
			{
				AGError() << "Couldn't load texture: " << fullFileName; 
				return; 
			}
			hr = textResource->var->SetResource( textResource->view );
			if( FAILED( hr ) )
			{
				AGError() << "Couldn't set resource " << fullFileName << " to: " << fileName; 
				return; 
			}
		}
	}
	
	m_technique = m_effect->GetTechniqueByName( "Render" );

	D3D10_INPUT_ELEMENT_DESC layout[] = 
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D10_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D10_INPUT_PER_VERTEX_DATA, 0 },
		{ "BINORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 24, D3D10_INPUT_PER_VERTEX_DATA, 0 },
		{ "TANGENT",  0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 36, D3D10_INPUT_PER_VERTEX_DATA, 0 },
		{ "UV",       0, DXGI_FORMAT_R32G32_FLOAT,    0, 48, D3D10_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = 5; 

	D3D10_PASS_DESC passDesc; 
	m_technique->GetPassByIndex( 0 )->GetDesc( &passDesc );
	hr = device->CreateInputLayout( layout, numElements, passDesc.pIAInputSignature, passDesc.IAInputSignatureSize, &m_inputLayout );

	if( FAILED( hr ) )
	{
		AGError() << "Couldn't create input layout";
		return;
	}
}

void AGDX10Material::setWorldMatrix(D3DXMATRIX world)
{
	m_worldVar->SetMatrix( world );
}

void AGDX10Material::setViewMatrix(D3DXMATRIX view)
{
	m_viewVar->SetMatrix( view );
}

void AGDX10Material::setProjMatrix(D3DXMATRIX proj)
{
	m_projectionVar->SetMatrix( proj );
}

void AGDX10Material::apply( ID3D10Device* device )
{
	D3D10_TECHNIQUE_DESC desc; 
	m_technique->GetDesc( &desc );

	device->IASetInputLayout( m_inputLayout );

	for( int i = 0; i < desc.Passes; i++ )
	{
		m_technique->GetPassByIndex( i )->Apply( 0 );
	}
}

