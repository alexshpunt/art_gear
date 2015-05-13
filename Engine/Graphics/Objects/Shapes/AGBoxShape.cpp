#include "AGBoxShape.h"

#include "Engine/Utils/AGErrorHandling.h"

#include "Engine/Math/AGMath.h"

class AGBoxShapePrivate
{
public:
	AGBoxShapePrivate()
	{
		length = width = height = EPSILON_FOR_FLOAT; 
		initByVertices = false; 
	}
	float length; 
	float width;
	float height; 

	AGVec3 v1, v2; 
	bool initByVertices; 
};

AGBoxShape::AGBoxShape(const AGVec3& v1, const AGVec3& v2, const AGColor& color)
{
	p = new AGBoxShapePrivate; 

	p->v1 = v1;
	p->v2 = v2; 
	p->initByVertices = true; 
	setLength( abs( v2.z - v1.z ) );
	setWidth( abs( v2.x - v1.x ) );
	setHeight( abs( v2.y - v1.y ) );
	setupShape(); 
}

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
	softAssert( side > EPSILON_FOR_FLOAT ); 

	p->length = side;
	p->width  = side; 
	p->height = side;
}

void AGBoxShape::setWidth(float width)
{
	softAssert( width > EPSILON_FOR_FLOAT );

	p->width = width; 
}

float AGBoxShape::getWidth() const
{
	return p->width; 
}

void AGBoxShape::setHeight(float height)
{
	softAssert( height > EPSILON_FOR_FLOAT );

	p->height = height; 
}

float AGBoxShape::getHeight() const
{
	return p->height; 
}

void AGBoxShape::setLength(float length)
{
	softAssert( length > EPSILON_FOR_FLOAT );

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

	AGVec3 v1;
	AGVec3 v2;

	if( p->initByVertices )
	{
		v1 = p->v1;
		v2 = p->v2;
	}
	else 
	{
		v2 = AGVec3( p->width / 2.0f, p->height / 2.0f, p->length / 2.0f );
		v1 = AGVec3( -p->width / 2.0f, -p->height / 2.0f, -p->length / 2.0f );
	}

	AGColorVertex vertices[] = 
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
		m_vertices.push_back( vertices[ i ].pos ); 
	}

	m_vertexBuffer = new AGBuffer< AGColorVertex >( vector< AGColorVertex >( vertices, vertices + 8 ), AGBufferType::Vertex );

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

	m_indices.resize( 36 );

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

float AGBoxShape::intersect( const AGVec3& rayOrigin, const AGVec3& rayDir )
{
	float retDist = -1.0f; 
	for( int i = 0; i < 34; i++ )
	{
		AGVec3 v1 = m_vertices[ m_indices[ i ] ];
		AGVec3 v2 = m_vertices[ m_indices[ i + 1 ] ];
		AGVec3 v3 = m_vertices[ m_indices[ i + 2 ] ];

		AGMath::IntersectResult res = AGMath::intersectTriangle( rayOrigin, rayDir, AGMath::Triangle( v1, v2, v3 ) ); 

		if( res.hit )
		{
			if( retDist < 0 )
			{
				retDist = res.distance; 
			}
			else 
			{
				retDist = min( retDist, res.distance ); 
			}
		}
	}
	return retDist; 
}




