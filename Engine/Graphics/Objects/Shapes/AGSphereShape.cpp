#include "AGSphereShape.h"

#include "Engine/Graphics/Objects/AGBuffer.h"

#include "Engine/Math/AGMath.h"

#include "Engine/Utils/AGConversion.h"

#include "Engine/Managers/AGResourceManager.h"

class AGSphereShapePrivate 
{
	public:
		AGSphereShapePrivate()
		{
			radius = 0.0f;
			circleVerticesCount = 0;
			verticesCount = 0; 
		}
		~AGSphereShapePrivate()
		{
		}

		float radius;
		unsigned int circleVerticesCount; 
		unsigned int verticesCount; 
		AGColor color; 
};

AGSphereShape::AGSphereShape( float radius, const AGColor& color ) : AGShape( color )
{
	p = new AGSphereShapePrivate; 
	setRadius( radius );

	setupShape(); 
}

AGSphereShape::~AGSphereShape()
{
	delete p; 
}

void AGSphereShape::setRadius(float radius)
{
	p->radius = AGMath::checkIfLower( radius, 0.001f );
}

float AGSphereShape::getRadius() const
{
	return p->radius; 
}

void AGSphereShape::draw(AGSurface* surface)
{
	prepareDraw( surface );

	while( m_shader->applyNextPass() )
	{
		for( int i = 0; i < p->circleVerticesCount - 2; i++ )
		{
			surface->draw( 2, i );
			surface->draw( 2, p->circleVerticesCount + i );
			surface->draw( 2, 2*p->circleVerticesCount + i );
		}
	}
}

void AGSphereShape::setupShape()
{
	if( m_vertexBuffer )
	{
		delete m_vertexBuffer; 
		m_vertexBuffer = nullptr; 
	}

	std::vector< AGVec2 > points; 
	std::vector< AGColorVertex > vertices; 
	AGMath::generateCircle2D( p->radius, AGMath::Pi / 12.0f , points );

	AGColorVertex vertex; 
	vertex.color = m_color;

	//XY Plane
	for( AGVec2 point : points )
	{
		vertex.pos = AGVec3( point.x, point.y, 0.0f );
		vertices.push_back( vertex ); 
	}

	//XZ Plane
	for( AGVec2 point : points )
	{
		vertex.pos = AGVec3( point.x, 0.0f, point.y );
		vertices.push_back( vertex ); 
	}

	//YZ Plane
	for( AGVec2 point : points )
	{
		vertex.pos = AGVec3( 0.0f, point.x, point.y );
		vertices.push_back( vertex ); 
	}

	p->verticesCount = vertices.size(); 
	p->circleVerticesCount = points.size(); 

	m_vertexBuffer = new AGBuffer< AGColorVertex >( vertices, Vertex );
}

