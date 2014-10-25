#include "AGDX10Gizmos.h"

AGDX10PosGizmo::AGDX10PosGizmo(ID3D10Device* device) : AGDX10Primitive( device )
{
	D3DXMatrixIdentity( &m_world );

	D3DXVECTOR4 color( 1.0f, 1.0f, 1.0f, 1.0f );

	AGColorVertex vertices[] = 
	{
		{ D3DXVECTOR3( 0, 0, 0 ), color }, 
		{ D3DXVECTOR3( 1, 0, 0 ), color }, 
		{ D3DXVECTOR3( 0.809017, 0, 0.587785 ), color }, 
		{ D3DXVECTOR3( 0.309017, 0, 0.951057 ), color }, 
		{ D3DXVECTOR3( -0.309017, 0, 0.951056 ), color }, 
		{ D3DXVECTOR3( -0.809017, 0, 0.587785 ), color }, 
		{ D3DXVECTOR3( -1, 0, -8.74228e-008 ), color }, 
		{ D3DXVECTOR3( -0.809017, 0, -0.587785 ), color }, 
		{ D3DXVECTOR3( -0.309017, 0, -0.951056 ), color }, 
		{ D3DXVECTOR3( 0.309017, 0, -0.951056 ), color }, 
		{ D3DXVECTOR3( 0.809017, 0, -0.587785 ), color }, 
		{ D3DXVECTOR3( 0, 2, 0 ), color }, 
	}

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
}

AGDX10PosGizmo::~AGDX10PosGizmo()
{

}

void AGDX10PosGizmo::draw(ID3D10Device* device, AGDX10Camera* camera)
{

}

float AGDX10PosGizmo::intersect(D3DXVECTOR3 rayOrigin, D3DXVECTOR3 rayDir)
{
	return 1.0f; 
}

