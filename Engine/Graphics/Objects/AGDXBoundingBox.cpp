#include "AGDXBoundingBox.h"

#include <string>
#include <math.h>

#include "Managers/AGLogger.h"
#include "Graphics/Interfaces/AGSurface.h"
#include "AGDXCamera.h"

using namespace std;

AGDXBoundingBox::AGDXBoundingBox( D3DXVECTOR3 v1, D3DXVECTOR3 v2, ID3D10Device* device ) : AGDXPrimitive( device )
{
	D3DXVECTOR4 clr( 1.0f, 1.0f, 1.0f, 1.0f );

	AGColorVertex vertices[] = 
	{
		{ D3DXVECTOR3( v2.x, v2.y, v2.z ), clr }, //0
		{ D3DXVECTOR3( v2.x, v1.y, v2.z ), clr }, //1
		{ D3DXVECTOR3( v1.x, v1.y, v2.z ), clr }, //2
		{ D3DXVECTOR3( v1.x, v2.y, v2.z ), clr }, //3

		{ D3DXVECTOR3( v2.x, v2.y, v1.z ), clr }, //4
		{ D3DXVECTOR3( v2.x, v1.y, v1.z ), clr }, //5
		{ D3DXVECTOR3( v1.x, v1.y, v1.z ), clr }, //6
		{ D3DXVECTOR3( v1.x, v2.y, v1.z ), clr }, //7
	};

	for( int i = 0; i < 8; i++ )
	{
		AGColorVertex clrVert = vertices[ i ]; 
		m_vertices[ i ] = clrVert.pos; 
	}

	D3D10_BUFFER_DESC buffDesc; 

	buffDesc.Usage = D3D10_USAGE_DEFAULT; 
	buffDesc.ByteWidth = sizeof( vertices ); 
	buffDesc.CPUAccessFlags = 0;
	buffDesc.MiscFlags = 0;
	buffDesc.BindFlags = D3D10_BIND_VERTEX_BUFFER; 

	D3D10_SUBRESOURCE_DATA subresData; 
	subresData.pSysMem = vertices;

	HRESULT hr = device->CreateBuffer( &buffDesc, &subresData, &m_vertexBuffer );

	if( FAILED( hr ) )
	{
		AGError() << "Couldn't create vertex buffer";
		return; 
	}

	int indices[] = 
	{
		0,1,
		0,3,

		1,2, 
		2,3,

		0,4, 
		1,5,

		5,4, 
		5,6,

		4,7, 
		6,7,

		6,2, 
		7,3,
	};

	buffDesc.ByteWidth = sizeof( indices );
	buffDesc.BindFlags = D3D10_BIND_INDEX_BUFFER; 
	subresData.pSysMem = indices;

	hr = device->CreateBuffer( &buffDesc, &subresData, &m_indexBuffer );

	if( FAILED( hr ) )
	{
		AGError() << "Couldn't create index buffer"; 
		return; 
	}

	//Приходится заполнять новый массив индексов для проверки пересечения луча 
	m_indices[ 0 ] = 0;
	m_indices[ 1 ] = 1;
	m_indices[ 2 ] = 2; 

	m_indices[ 3 ] = 3; 
	m_indices[ 4 ] = 0;
	m_indices[ 5 ] = 2; 

	m_indices[ 6 ] = 3;
	m_indices[ 7 ] = 2;
	m_indices[ 8 ] = 6; 

	m_indices[ 9 ]  = 7;
	m_indices[ 10 ] = 3;
	m_indices[ 11 ] = 6;

	m_indices[ 12 ] = 7;
	m_indices[ 13 ] = 6;
	m_indices[ 14 ] = 5; 

	m_indices[ 15 ] = 4;
	m_indices[ 16 ] = 6;
	m_indices[ 17 ] = 5; 

	m_indices[ 18 ] = 4;
	m_indices[ 19 ] = 5;
	m_indices[ 20 ] = 1; 

	m_indices[ 21 ] = 0;
	m_indices[ 22 ] = 5;
	m_indices[ 23 ] = 1; 

	m_indices[ 24 ] = 1;
	m_indices[ 25 ] = 5;
	m_indices[ 26 ] = 6;

	m_indices[ 27 ] = 2;
	m_indices[ 28 ] = 1;
	m_indices[ 29 ] = 6; 

	m_indices[ 30 ] = 4;
	m_indices[ 31 ] = 0;
	m_indices[ 32 ] = 3; 

	m_indices[ 33 ] = 7;
	m_indices[ 34 ] = 0;
	m_indices[ 35 ] = 3; 
}

AGDXBoundingBox::~AGDXBoundingBox()
{

}

void AGDXBoundingBox::draw( AGDXSurface* surface )
{
	D3D10_TECHNIQUE_DESC desc; 
	m_technique->GetDesc( &desc );

	AGDXCamera* camera = surface->getCamera();
	ID3D10Device* device = surface->getDevice();
	
	m_worldVar->SetMatrix( getWorld() );
	m_viewVar->SetMatrix( camera->getViewMatrix() );
	m_projectionVar->SetMatrix( camera->getProjMatrix() );

	device->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_LINESTRIP );
	device->IASetIndexBuffer( m_indexBuffer, DXGI_FORMAT_R32_UINT, 0 );
	device->IASetInputLayout( m_inputLayout );
	UINT stride = sizeof( AGColorVertex );
	UINT offset = 0; 
	device->IASetVertexBuffers( 0, 1, &m_vertexBuffer, &stride, &offset );

	for( int i = 0; i < desc.Passes; i++ )
	{
		m_technique->GetPassByIndex( i )->Apply( 0 );
		//device->DrawIndexed( 36, 0, 0 );
		for( int j = 0; j < 12; j++ )
		{
			device->DrawIndexed( 2, j*2, 0 );
		}
	}
}

float AGDXBoundingBox::intersect( D3DXVECTOR3 rayOrigin, D3DXVECTOR3 rayDir )
{
	float retDist = -1.0f; 
	for( int i = 0; i < 34; i++ )
	{
		D3DXVECTOR3 vertex1 = m_vertices[ m_indices[ i ] ];
		D3DXVECTOR3 vertex2 = m_vertices[ m_indices[ i + 1 ] ];
		D3DXVECTOR3 vertex3 = m_vertices[ m_indices[ i + 2 ] ];

		float dist, u, v; 

		bool res = D3DXIntersectTri( &vertex1, &vertex2, &vertex3, &rayOrigin, &rayDir, &u, &v, &dist );
		if( res )
		{
			if( retDist < 0 )
			{
				retDist = dist; 
			}
			else 
			{
				retDist = min( retDist, dist );	
			}
		}
	}
	return retDist; 
}

