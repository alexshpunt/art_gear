#include "AGBoundingBox.h"

#include <string>
#include <math.h>

#include "Managers/AGLogger.h"
#include "Graphics/Interfaces/AGSurface.h"
#include "AGCamera.h"

#include <Engine/Graphics/AGGraphics.h>

using namespace std;

AGBoundingBox::AGBoundingBox( AGVec3 v1, AGVec3 v2 )
{
	D3DXVECTOR4 clr( 1.0f, 1.0f, 1.0f, 1.0f );

	AGPrimitiveVertex vertices[] = 
	{
		{ AGVec3( v2.x, v2.y, v2.z ), clr }, //0
		{ AGVec3( v2.x, v1.y, v2.z ), clr }, //1
		{ AGVec3( v1.x, v1.y, v2.z ), clr }, //2
		{ AGVec3( v1.x, v2.y, v2.z ), clr }, //3

		{ AGVec3( v2.x, v2.y, v1.z ), clr }, //4
		{ AGVec3( v2.x, v1.y, v1.z ), clr }, //5
		{ AGVec3( v1.x, v1.y, v1.z ), clr }, //6
		{ AGVec3( v1.x, v2.y, v1.z ), clr }, //7
	};

	for( int i = 0; i < 8; i++ )
	{
		AGPrimitiveVertex clrVert = vertices[ i ]; 
		m_vertices[ i ] = clrVert.pos; 
	}

	vector< AGPrimitiveVertex > vertexVector( vertices, vertices + 8 );
	
	m_vertexBuffer = new AGBuffer< AGPrimitiveVertex >( vertexVector, AGBufferType::Vertex );

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

	vector< int > indexVector( indices, indices + 24 );

	m_indexBuffer = new AGBuffer< int >( indexVector, AGBufferType::Index );

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

AGBoundingBox::~AGBoundingBox()
{

}

void AGBoundingBox::draw( AGSurface* surface )
{
	ID3D10Device* device = surface->getDevice(); 

	m_shader->applySurface( surface );
	m_shader->setWorldMatrix( getLocalMatrix() ); 	

	device->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_LINELIST );

	ID3D10Buffer* indexBuffer = m_indexBuffer->applyTo( device ); 
	ID3D10Buffer* vertexBuffer = m_vertexBuffer->applyTo( device ); 

	device->IASetIndexBuffer( indexBuffer, DXGI_FORMAT_R32_UINT, 0 );

	AGInputLayout* layout = AGGraphics::getInstance().getInputLayout( device );

	device->IASetInputLayout( layout->colorVertexInputLayout );
	UINT stride = sizeof( AGPrimitiveVertex );

	UINT offset = 0; 
	device->IASetVertexBuffers( 0, 1, &vertexBuffer, &stride, &offset );

	while( m_shader->applyNextPass() )
	{
		for( int j = 0; j < 12; j++ )
		{
			device->DrawIndexed( 2, j*2, 0 );	
		}
	}

}

float AGBoundingBox::intersect( AGVec3 rayOrigin, AGVec3 rayDir )
{
	float retDist = -1.0f; 
	for( int i = 0; i < 34; i++ )
	{
		AGVec3 vertex1 = m_vertices[ m_indices[ i ] ];
		AGVec3 vertex2 = m_vertices[ m_indices[ i + 1 ] ];
		AGVec3 vertex3 = m_vertices[ m_indices[ i + 2 ] ];

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

