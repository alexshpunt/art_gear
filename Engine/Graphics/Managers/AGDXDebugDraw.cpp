#include "AGDXDebugDraw.h"

#include <string>

#include "Managers/AGLogger.h"
#include "Graphics/Objects/AGDXPrimitive.h"
#include "Graphics/Objects/AGDXCamera.h"

using namespace std;

void AGDXDebugDraw::initialize( ID3D10Device* device )
{
	wstring fileName = L"data/shaders/difprim.fx";

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

	m_technique = m_effect->GetTechniqueByName( "Render" );

	D3D10_INPUT_ELEMENT_DESC layout[] = 
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D10_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",   0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D10_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = 2; 

	D3D10_PASS_DESC passDesc; 
	m_technique->GetPassByIndex( 0 )->GetDesc( &passDesc );
	hr = device->CreateInputLayout( layout, numElements, passDesc.pIAInputSignature, passDesc.IAInputSignatureSize, &m_inputLayout );

	if( FAILED( hr ) )
	{
		AGError() << "Couldn't create input layout";
		return;
	}

	device->IASetInputLayout( m_inputLayout );

	D3D10_DEPTH_STENCIL_DESC dsDesc; 

	dsDesc.DepthEnable = false; 
	dsDesc.DepthFunc = D3D10_COMPARISON_GREATER; 
	dsDesc.DepthWriteMask = D3D10_DEPTH_WRITE_MASK_ALL; 

	dsDesc.StencilEnable = true;
	dsDesc.StencilReadMask = 0xFF;
	dsDesc.StencilWriteMask = 0xFF;

	// Stencil operations if pixel is front-facing
	dsDesc.FrontFace.StencilFailOp = D3D10_STENCIL_OP_KEEP;
	dsDesc.FrontFace.StencilDepthFailOp = D3D10_STENCIL_OP_INCR;
	dsDesc.FrontFace.StencilPassOp = D3D10_STENCIL_OP_KEEP;
	dsDesc.FrontFace.StencilFunc = D3D10_COMPARISON_ALWAYS;

	// Stencil operations if pixel is back-facing
	dsDesc.BackFace.StencilFailOp = D3D10_STENCIL_OP_KEEP;
	dsDesc.BackFace.StencilDepthFailOp = D3D10_STENCIL_OP_DECR;
	dsDesc.BackFace.StencilPassOp = D3D10_STENCIL_OP_KEEP;
	dsDesc.BackFace.StencilFunc = D3D10_COMPARISON_ALWAYS;

	device->CreateDepthStencilState( &dsDesc, &m_depthState );

	m_isInitialized = true; 
}

void AGDXDebugDraw::drawLine( AGDXSurface* surface, D3DXVECTOR3 start, D3DXVECTOR3 end, D3DXVECTOR4 color )
{
	if( !m_isInitialized )
		return; 

	AGDXCamera* camera = surface->getCamera();
	ID3D10Device* device = surface->getDevice();

	float len = 0.25f; 

	D3DXVECTOR4 red  ( 0.798431372, 0.0f, 0.0f, 1.0f );
	D3DXVECTOR4 green( 0.0f, 0.6117647058, 0.0f, 1.0f );
	D3DXVECTOR4 blue ( 0.0f, 0.0f, 0.76470588233, 1.0f );

	AGColorVertex vertices[] = 
	{
		{ start, color },
		{ end,   color },
	};

	D3D10_BUFFER_DESC buffDesc; 

	buffDesc.Usage = D3D10_USAGE_DEFAULT; 
	buffDesc.ByteWidth = sizeof( vertices ); 
	buffDesc.CPUAccessFlags = 0;
	buffDesc.MiscFlags = 0;
	buffDesc.BindFlags = D3D10_BIND_VERTEX_BUFFER; 

	D3D10_SUBRESOURCE_DATA subresData; 
	subresData.pSysMem = vertices;

	HRESULT hr = device->CreateBuffer( &buffDesc, &subresData, &m_vertexBuffer );

	D3D10_TECHNIQUE_DESC desc; 
	m_technique->GetDesc( &desc );

	D3DXMATRIX world; 
	D3DXMatrixIdentity( &world );

	m_worldVar->SetMatrix( world );
	m_viewVar->SetMatrix( camera->getViewMatrix() );
	m_projectionVar->SetMatrix( camera->getProjMatrix() );

	device->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_LINESTRIP );
	device->IASetInputLayout( m_inputLayout );
	UINT stride = sizeof( AGColorVertex );
	UINT offset = 0; 
	device->IASetVertexBuffers( 0, 1, &m_vertexBuffer, &stride, &offset );
	device->OMSetDepthStencilState( m_depthState, 1 );

	for( int i = 0; i < desc.Passes; i++ )
	{
		m_technique->GetPassByIndex( i )->Apply( 0 );
		device->Draw( 2, 0 );
	}

	m_vertexBuffer->Release(); 
}

void AGDXDebugDraw::init()
{
	m_isInitialized = false; 
}

