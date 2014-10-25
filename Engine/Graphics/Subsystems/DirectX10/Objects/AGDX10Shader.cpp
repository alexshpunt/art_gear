#include "AGDX10Shader.h"

#include <vector>
#include <DxErr.h>

#include "AGDX10Material.h"
#include "AGDX10Camera.h"
#include "Managers/AGLogger.h"
#include "Graphics/Subsystems/DirectX10/AGDX10SubSys.h"

AGDX10Shader::AGDX10Shader()
{
	
}

AGDX10Shader::~AGDX10Shader()
{

}

void AGDX10Shader::initialize(const AGDX10Material* material,  ID3D10Device* device )
{
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
		wstring texture = material->getTexture( i );
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
		wstring texture = material->getTexture( i );
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

	device->IASetInputLayout( m_inputLayout );
	device->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

	D3DXMatrixIdentity( &m_world );
	//D3DXMatrixPerspectiveFovLH( &m_proj, 70, 1.77777778f, 0.1f, 10000.0f );
}


void AGDX10Shader::apply( AGDX10Camera* camera )
{
	D3D10_TECHNIQUE_DESC desc; 
	m_technique->GetDesc( &desc );

	/*D3DXVECTOR3 eye( 0.0f, 2.0f, -10.f );
	D3DXVECTOR3 at( 0.0f, 2.0f, 0.0f );
	D3DXVECTOR3 up( 0.0f, 1.0f, 0.0f );

	D3DXMatrixLookAtLH( &m_view, &eye, &at, &up );

	static float t = 0.0f;
	static DWORD dwTimeStart = 0;
	DWORD dwTimeCur = GetTickCount();
	if( dwTimeStart == 0 )
		dwTimeStart = dwTimeCur;
	t = ( dwTimeCur - dwTimeStart ) / 1000.0f;

	D3DXMatrixRotationY( &m_world, t );*/

	D3DXMATRIX view = camera->getViewMatrix();
	D3DXMATRIX proj = camera->getProjMatrix();

	m_worldVar->SetMatrix( m_world );
	m_viewVar->SetMatrix( view );
	m_projectionVar->SetMatrix( proj );

	for( int i = 0; i < desc.Passes; i++ )
	{
		m_technique->GetPassByIndex( i )->Apply( 0 );
	}
}

