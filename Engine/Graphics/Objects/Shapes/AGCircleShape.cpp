#include "AGCircleShape.h"

#include "Engine/Utils/AGErrorHandling.h"

class AGCircleShapePrivate
{
	public:
		AGCircleShapePrivate()
		{
			radius = height = 0.0;

			indicesCount = 0; 
		}
		float radius;
		float height; 

		int indicesCount; 
		std::vector< AGColorVertex > vertices;
		std::vector< int > indices; 
};

AGCircleShape::AGCircleShape( float radius, const AGColor& color ) : AGShape( color )
{
	p = new AGCircleShapePrivate; 
	setRadius( radius );
	setupShape(); 
}

AGCircleShape::~AGCircleShape()
{
	delete p; 
}

void AGCircleShape::draw(AGSurface* surface)
{
	prepareDraw( surface );

	while( m_shader->applyNextPass() )
	{	
		for( int i = 0; i < p->vertices.size() - 1; i++ )
		{
			surface->draw( 2, i );
		}
	}
}

void AGCircleShape::setRadius(float radius)
{
	softAssert( radius > EPSILON_FOR_FLOAT );
	
	p->radius = radius; 
}

float AGCircleShape::getRadius() const
{
	return p->radius; 
}

void AGCircleShape::setupShape()
{
	if( m_vertexBuffer )
	{
		delete m_vertexBuffer; 
		m_vertexBuffer = nullptr; 
	}
	if( m_indexBuffer )
	{
		delete m_indexBuffer;
		m_indexBuffer = nullptr; 
	}

	if( p->vertices.size() > 0 )
		p->vertices.clear(); 

	float step = AGMath::Pi / 6.0f; 
	vector< AGVec2 > points; 
	AGMath::generateCircle2D( p->radius, step, points );

	AGVec2 centerPoint( 0.0f, 0.0f );

	AGColorVertex tVert; 

	for( int i = 0; i < points.size(); i++ )
	{
		tVert.pos.x = points[ i ].x; 
		tVert.pos.y = 0; 
		tVert.pos.z = points[ i ].y; 
		tVert.color = m_color; 
		p->vertices.push_back( tVert );
	}
	p->vertices.push_back( p->vertices[ 0 ] );

	m_vertexBuffer = new AGBuffer< AGColorVertex >( p->vertices, AGBufferType::Vertex );
}

