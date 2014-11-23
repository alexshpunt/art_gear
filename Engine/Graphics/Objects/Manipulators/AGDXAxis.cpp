#include "AGDXAxis.h"

#include "Managers/AGLogger.h"
#include "Objects/AGObject.h"
#include "Math/AGMath.h"
#include "Graphics/Interfaces/AGSurface.h"
#include "Graphics/Objects/AGDXCamera.h"
#include "Graphics/Interfaces/AGDXMovable.h"

AGDXAxises::AGDXAxises(ID3D10Device* device) : AGDXPrimitive( device )
{
	D3DXVECTOR4 red  ( 0.798431372, 0.0f, 0.0f, 1.0f );
	D3DXVECTOR4 green( 0.0f, 0.6117647058, 0.0f, 1.0f );
	D3DXVECTOR4 blue ( 0.0f, 0.0f, 0.76470588233, 1.0f );
	
	float len = 0.25f; 

	AGColorVertex vertices[] = 
	{
		{ D3DXVECTOR3( 0.0f, 0.0f, 0.0f ), red },
		{ D3DXVECTOR3( len, 0.0f, 0.0f ), red },
		{ D3DXVECTOR3( 0.0f, 0.0f, 0.0f ), green },
		{ D3DXVECTOR3( 0.0f, len, 0.0f ), green },
		{ D3DXVECTOR3( 0.0f, 0.0f, 0.0f ), blue },
		{ D3DXVECTOR3( 0.0f, 0.0f, len ), blue },
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

	m_object = nullptr; 

	D3DX10_FONT_DESC fontDesc;

	fontDesc.CharSet = OUT_DEFAULT_PRECIS;
	wcscpy_s( fontDesc.FaceName, 32, L"Consolas" );
	fontDesc.Height = 16;
	fontDesc.Width = 0;
	fontDesc.Weight = 0;
	fontDesc.MipLevels = 1;
	fontDesc.Italic = false;
	fontDesc.Quality = DEFAULT_QUALITY; 
	fontDesc.PitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;


	D3DX10CreateFontIndirect( device, &fontDesc, &m_font );
}

AGDXAxises::~AGDXAxises()
{

}

void AGDXAxises::setObject(AGObject* object)
{
	m_object = object;
}

AGObject* AGDXAxises::getObject() const
{
	return m_object; 
}

void AGDXAxises::draw( AGDXSurface* surface )
{
	if( !m_object )
		return; 

	D3D10_TECHNIQUE_DESC desc; 
	m_technique->GetDesc( &desc );

	AGDXCamera* camera = surface->getCamera();
	ID3D10Device* device = surface->getDevice();

	D3DXVECTOR3 camEye = camera->getEye(); 
	AGVec3 objPos = m_object->getPos(); 
	AGVec3 objPivot = m_object->getPivot();
	objPos += objPivot; 
	D3DXVECTOR3 at( objPos.x, objPos.y, objPos.z ); 
	D3DXVECTOR3 camAt = camera->getAt(); 
	D3DXVECTOR3 dir = camEye - at; 
	D3DXVec3Normalize( &dir, &dir );
	dir = camEye - dir * 1.5f; 
	setPos( dir );

	AGVec3 angles = m_object->getRotation();

	setAngle( angles.x, angles.y, angles.z );

	D3DXMATRIX viewMat = camera->getViewMatrix();
	D3DXMATRIX projMat = camera->getProjMatrix();

	m_worldVar->SetMatrix( getWorld() );
	m_viewVar->SetMatrix( viewMat );
	m_projectionVar->SetMatrix( projMat );

	device->IASetInputLayout( m_inputLayout );
	UINT stride = sizeof( AGColorVertex );
	UINT offset = 0; 
	device->IASetVertexBuffers( 0, 1, &m_vertexBuffer, &stride, &offset );

	device->OMSetDepthStencilState( m_depthState, 1 );

	for( int i = 0; i < desc.Passes; i++ )
	{
		m_technique->GetPassByIndex( i )->Apply( 0 );
		device->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_LINELIST );
		device->Draw( 2, 0 );
		device->Draw( 2, 2 );
		device->Draw( 2, 4 );
	}

	float halfWidth = surface->getWidth() / 2.0f;
	float halfHeight = surface->getHeight() / 2.0f; 

	/*for( int i = 0; i < 3; i++ )
	{
		D3DXCOLOR fontColor( 0.798431372 * ( i == 0), 0.6117647058 * ( i == 1), 0.76470588233 * ( i == 2), 1.0f );

		switch( i )
		{
		case 0:
			dir = D3DXVECTOR3( 0.25f, 0.05f, 0.0f ); 
			break;
		case 1:
			dir = D3DXVECTOR3( 0.0f, 0.30f, 0.0f ); 
			break;
		case 2:
			dir = D3DXVECTOR3( 0.0f, 0.05f, 0.25f ); 
			break;
		}

		D3DXMATRIX world = getWorld();

		D3DXVec3TransformCoord( &dir, &dir, &world );
		D3DXVec3TransformCoord( &dir, &dir, &viewMat );
		D3DXVec3TransformCoord( &dir, &dir, &projMat );

		float textX = dir.x * halfWidth + halfWidth;
		float textY = -dir.y * halfHeight + halfHeight; 

		RECT rect = { textX, textY, 0, 0 }; 

		wchar_t* str = i == 0 ? L"X" : i == 1 ? L"Y" : L"Z";

		m_font->DrawTextW( 0, str, -1, &rect, DT_NOCLIP, fontColor );		
	}*/
	device->OMSetBlendState(NULL, 0, 0xffffffff);
}

float AGDXAxises::intersect(D3DXVECTOR3 rayOrigin, D3DXVECTOR3 rayDir)
{
	return -1.0f; 
}

D3DXVECTOR3 AGDXAxises::getAxis()
{
	return D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
}

