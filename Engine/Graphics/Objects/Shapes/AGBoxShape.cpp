#include "AGBoxShape.h"

#include <assert.h>

#include "Engine/Math/AGMath.h"

class AGBoxShapePrivate
{
	public:
		AGBoxShapePrivate()
		{
			length = width = height = EPSILON_FOR_FLOAT; 
		}
		float length; 
		float width;
		float height; 

		int indices[ 36 ];
		AGVec3 vertices[ 8 ];
};

AGBoxShape::AGBoxShape( float side, const AGColor& color ) : AGShape( color )
{
	p = new AGBoxShapePrivate; 

	setSide( side );
	setupShape(); 
}

AGBoxShape::AGBoxShape( float lenght, float width, float height, const AGColor& color ) : AGShape( color )
{
	p = new AGBoxShapePrivate; 

	setLength( lenght );
	setWidth( width );
	setHeight( height );
	setupShape(); 
}

AGBoxShape::~AGBoxShape()
{
	delete p; 
}

void AGBoxShape::draw(AGSurface* surface)
{
	prepareDraw( surface );

	while( m_shader->applyNextPass() )
	{
		for( int j = 0; j < 12; j++ )
		{	
			surface->drawIndexed( 2, j * 2, 0 );
		}
	}
}

void AGBoxShape::setSide(float side)
{
	assert( side > EPSILON_FOR_FLOAT );

	p->length = side;
	p->width  = side; 
	p->height = side;
}

void AGBoxShape::setWidth(float width)
{
	assert( width > EPSILON_FOR_FLOAT );

	p->width = width; 
}

float AGBoxShape::getWidth() const
{
	return p->width; 
}

void AGBoxShape::setHeight(float height)
{
	assert( height > EPSILON_FOR_FLOAT );

	p->height = height; 
}

float AGBoxShape::getHeight() const
{
	return p->height; 
}

void AGBoxShape::setLength(float length)
{
	assert( length > EPSILON_FOR_FLOAT );

	p->length = length;
}

float AGBoxShape::getLength() const
{
	return p->length;
}


void AGBoxShape::setupShape()
{
	if( m_vertexBuffer )
		delete m_vertexBuffer;
	if( m_indexBuffer )
		delete m_indexBuffer; 

	AGVec3 v2( p->width / 2.0f, p->height / 2.0f, p->length / 2.0f );
	AGVec3 v1( -p->width / 2.0f, -p->height / 2.0f, -p->length / 2.0f );

	AGPrimitiveVertex vertices[] = 
	{
		{ AGVec3( v2.x, v2.y, v2.z ), m_color }, //0
		{ AGVec3( v2.x, v1.y, v2.z ), m_color }, //1
		{ AGVec3( v1.x, v1.y, v2.z ), m_color }, //2
		{ AGVec3( v1.x, v2.y, v2.z ), m_color }, //3
	
		{ AGVec3( v2.x, v2.y, v1.z ), m_color }, //4
		{ AGVec3( v2.x, v1.y, v1.z ), m_color }, //5
		{ AGVec3( v1.x, v1.y, v1.z ), m_color }, //6
		{ AGVec3( v1.x, v2.y, v1.z ), m_color }, //7
	};

	for( int i = 0; i < 8; i++ )
	{
		p->vertices[ i ] = vertices[ i ].pos; 
	}

	m_vertexBuffer = new AGBuffer< AGPrimitiveVertex >( vector< AGPrimitiveVertex >( vertices, vertices + 8 ), AGBufferType::Vertex );

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

	p->indices[ 0 ] = 0;
	p->indices[ 1 ] = 1;
	p->indices[ 2 ] = 2; 

	p->indices[ 3 ] = 3; 
	p->indices[ 4 ] = 0;
	p->indices[ 5 ] = 2; 

	p->indices[ 6 ] = 3;
	p->indices[ 7 ] = 2;
	p->indices[ 8 ] = 6; 

	p->indices[ 9 ]  = 7;
	p->indices[ 10 ] = 3;
	p->indices[ 11 ] = 6;

	p->indices[ 12 ] = 7;
	p->indices[ 13 ] = 6;
	p->indices[ 14 ] = 5; 

	p->indices[ 15 ] = 4;
	p->indices[ 16 ] = 6;
	p->indices[ 17 ] = 5; 

	p->indices[ 18 ] = 4;
	p->indices[ 19 ] = 5;
	p->indices[ 20 ] = 1; 

	p->indices[ 21 ] = 0;
	p->indices[ 22 ] = 5;
	p->indices[ 23 ] = 1; 

	p->indices[ 24 ] = 1;
	p->indices[ 25 ] = 5;
	p->indices[ 26 ] = 6;

	p->indices[ 27 ] = 2;
	p->indices[ 28 ] = 1;
	p->indices[ 29 ] = 6; 

	p->indices[ 30 ] = 4;
	p->indices[ 31 ] = 0;
	p->indices[ 32 ] = 3; 

	p->indices[ 33 ] = 7;
	p->indices[ 34 ] = 0;
	p->indices[ 35 ] = 3; 
}

float AGBoxShape::intersect( const AGVec3& rayOrigin, const AGVec3& rayDir )
{
	float retDist = -1.0f; 
	for( int i = 0; i < 34; i++ )
	{
		AGVec3 vertex1 = p->vertices[ p->indices[ i ] ];
		AGVec3 vertex2 = p->vertices[ p->indices[ i + 1 ] ];
		AGVec3 vertex3 = p->vertices[ p->indices[ i + 2 ] ];

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




