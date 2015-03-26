#include "AGConeShape.h"

#include <assert.h>

class AGConeShapePrivate
{
	public:
		AGConeShapePrivate()
		{
			radius = height = 0.0;

			indicesCount = 0; 
		}
		float radius;
		float height; 

		int indicesCount; 
		std::vector< AGPrimitiveVertex > vertices;
		std::vector< int > indices; 
};

AGConeShape::AGConeShape( float radius = 1.0f, float height = 1.0f, const AGColor& color = AGColor( 1.0f ) ) : AGShape( color )
{
	p = new AGConeShapePrivate; 

	setRadius( radius );
	setHeight( height );
	setupShape(); 
}

AGConeShape::~AGConeShape()
{
	delete p; 
}

void AGConeShape::draw(AGSurface* surface)
{
	prepareDraw( surface );

	while( m_shader->applyNextPass() )
	{	
		for( int i = 0; i < p->vertices.size() - 2; i++ )
		{
			surface->draw( 2, i );
		}
	}
}

void AGConeShape::setRadius(float radius)
{
	assert( radius > EPSILON_FOR_FLOAT );
	
	p->radius = radius; 
}

float AGConeShape::getRadius() const
{
	return p->radius; 
}

void AGConeShape::setHeight(float height)
{
	assert( height > EPSILON_FOR_FLOAT );

	p->height = height; 
}

float AGConeShape::getHeight() const
{
	return p->height; 
}


void AGConeShape::setupShape()
{
	if( m_vertexBuffer )
	{
		delete m_vertexBuffer; 
		m_vertexBuffer = nullptr; 
	}

	if( p->vertices.size() > 0 )
		p->vertices.clear(); 

	float step = AGMath::Pi / 6.0f; 

	vector< AGVec2 > points; 
	AGMath::generateCircle2D( p->radius, step, points );

	AGVec2 centerPoint( 0.0f, 0.0f );

	AGPrimitiveVertex tVert; 

	for( int i = 0; i < points.size(); i++ )
	{
		tVert.pos.x = points[ i ].x; 
		tVert.pos.y = 0; 
		tVert.pos.z = points[ i ].y; 
		tVert.color = m_color; 
		p->vertices.push_back( tVert );
	}

	p->vertices.push_back( p->vertices[ 0 ] );

	int divider = 4; 
	int quarter = p->vertices.size() / divider; 

	tVert.pos = AGVec3( 0.0f, p->height, 0.0f );
	tVert.color = m_color;

	for( int i = 0; i <= divider; i++ )
	{
		p->vertices.push_back( tVert );
		p->vertices.push_back( p->vertices[ quarter * i ] );	
	}

	m_vertexBuffer = new AGBuffer< AGPrimitiveVertex >( p->vertices, AGBufferType::Vertex );
}

