#include "AGDXLine.h"

#include "Managers/AGLogger.h"
#include "Graphics/Interfaces/AGSurface.h"
#include "AGDXCamera.h"

AGDXLine::AGDXLine(ID3D10Device* device, float length, D3DXVECTOR4 color) : AGDXPrimitive( device )
{

	AGColorVertex vertices[] = 
	{
		{ D3DXVECTOR3( 0.0f, 0.0f, 0.0f ), color }, //0
		{ D3DXVECTOR3( length, 0.0f, 0.0f ), color }, //1
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
}

AGDXLine::~AGDXLine()
{

}

void AGDXLine::draw(AGDXSurface* surface)
{
	D3D10_TECHNIQUE_DESC desc; 
	m_technique->GetDesc( &desc );

	AGDXCamera* camera = surface->getCamera();
	ID3D10Device* device = surface->getDevice();

	m_worldVar->SetMatrix( getLocalMatrix() );
	m_viewVar->SetMatrix( camera->getViewMatrix() );
	m_projectionVar->SetMatrix( camera->getProjMatrix() );

	device->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_LINESTRIP );
	device->IASetInputLayout( m_inputLayout );
	UINT stride = sizeof( AGColorVertex );
	UINT offset = 0; 
	device->IASetVertexBuffers( 0, 1, &m_vertexBuffer, &stride, &offset );

	for( int i = 0; i < desc.Passes; i++ )
	{
		m_technique->GetPassByIndex( i )->Apply( 0 );
		device->Draw( 2, 0 );
	}
}

float AGDXLine::intersect(D3DXVECTOR3 rayOrigin, D3DXVECTOR3 rayDir)
{
	return -1.0f; 
}

