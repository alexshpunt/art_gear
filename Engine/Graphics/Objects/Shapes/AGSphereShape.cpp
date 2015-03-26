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
	m_p = new AGSphereShapePrivate; 
	setRadius( radius );

	setupShape(); 
}

AGSphereShape::~AGSphereShape()
{
	delete m_p; 
}

void AGSphereShape::setRadius(float radius)
{
	m_p->radius = AGMath::checkIfLower( radius, 0.001f );
}

float AGSphereShape::getRadius() const
{
	return m_p->radius; 
}

void AGSphereShape::draw(AGSurface* surface)
{
	prepareDraw( surface );

	while( m_shader->applyNextPass() )
	{
		for( int i = 0; i < m_p->circleVerticesCount - 2; i++ )
		{
			surface->draw( 2, i );
			surface->draw( 2, m_p->circleVerticesCount + i );
			surface->draw( 2, 2*m_p->circleVerticesCount + i );
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
	std::vector< AGPrimitiveVertex > vertices; 
	AGMath::generateCircle2D( m_p->radius, AGMath::Pi / 12.0f , points );

	AGPrimitiveVertex vertex; 
	vertex.color = m_p->color;

	//XY Plane
	for( AGVec2 point : points )
	{
		vertex.pos = AGVec3( point );
		vertices.push_back( vertex ); 
	}

	//XZ Plane
	for( AGVec2 point : points )
	{
		vertex.pos = AGVec3( point );
		vertices.push_back( vertex ); 
	}

	//YZ Plane
	for( AGVec2 point : points )
	{
		vertex.pos = AGVec3( point );
		vertices.push_back( vertex ); 
	}

	m_p->verticesCount = vertices.size(); 
	m_p->circleVerticesCount = points.size(); 

	m_vertexBuffer = new AGBuffer< AGPrimitiveVertex >( vertices, Vertex );
}

