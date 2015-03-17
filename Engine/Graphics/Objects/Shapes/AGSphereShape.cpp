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
			vbo = nullptr; 
		}
		~AGSphereShapePrivate()
		{
			delete vbo; 
		}

		float radius;
		unsigned int circleVerticesCount; 
		unsigned int verticesCount; 
		AGBuffer< AGPrimitiveVertex >* vbo;
		AGColor color; 
};

AGSphereShape::AGSphereShape( float radius, const AGColor& color )
{
	m_shader = AGResourceManager::getInstance().getShader( L"shape" );
	m_p = new AGSphereShapePrivate; 
	setRadius( radius );
	setColor( color );
	setup(); 
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
	AGCamera* camera = surface->getCamera(); 
	ID3D10Device* device = surface->getDevice(); 

	m_shader->applySurface( surface );

	m_shader->setWorldMatrix( getResultMatrix() );

	m_p->vbo->apply( surface );

	while( m_shader->applyNextPass() )
	{
		
		device->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_LINELIST );

		for( int i = 0; i < m_p->circleVerticesCount - 2; i++ )
		{
			device->Draw( 2, i );
			device->Draw( 2, m_p->circleVerticesCount + i );
			device->Draw( 2, 2*m_p->circleVerticesCount + i );
		}
	}
}

void AGSphereShape::setup()
{
	if( m_p->vbo )
	{
		delete m_p->vbo; 
		m_p->vbo = nullptr; 
	}

	std::vector< AGVec2 > points; 
	std::vector< AGPrimitiveVertex > vertices; 
	AGMath::generateCircle2D( m_p->radius, AGMath::Pi / 12.0f , points );

	AGPrimitiveVertex vertex; 
	vertex.color = D3DXVECTOR4( m_p->color.getRedF(), m_p->color.getGreenF(), m_p->color.getBlueF(), m_p->color.getAlphaF() );

	//XY Plane
	for( AGVec2 point : points )
	{
		vertex.pos = D3DXVECTOR3( point.x, point.y, 0.0f ); 
		vertices.push_back( vertex ); 
	}

	//XZ Plane
	for( AGVec2 point : points )
	{
		vertex.pos = D3DXVECTOR3( point.x, 0.0f, point.y ); 
		vertices.push_back( vertex ); 
	}

	//YZ Plane
	for( AGVec2 point : points )
	{
		vertex.pos = D3DXVECTOR3( 0.0f, point.x, point.y ); 
		vertices.push_back( vertex ); 
	}

	m_p->verticesCount = vertices.size(); 
	m_p->circleVerticesCount = points.size(); 

	m_p->vbo = new AGBuffer< AGPrimitiveVertex >( vertices, Vertex );
}

void AGSphereShape::setColor(const AGColor& color)
{
	m_p->color = color; 
}

const AGColor& AGSphereShape::getColor() const
{
	return m_p->color; 
}

