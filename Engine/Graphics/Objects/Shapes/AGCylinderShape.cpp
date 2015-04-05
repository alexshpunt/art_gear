#include "AGCylinderShape.h"

class AGCylinderShapePrivate 
{
	public:
		AGColor color; 
		AGSize size; 

		int indexCount; 
		vector< AGColorVertex > vertices;
		vector< int > indices; 

		int circleVerticesCount; 
};

AGCylinderShape::AGCylinderShape( float radius, float height, const AGColor& color ) : AGShape( color )
{
	p = new AGCylinderShapePrivate;

	setSize( radius, height );
	setupShape(); 
}

AGCylinderShape::~AGCylinderShape()
{
	delete p; 
}

void AGCylinderShape::draw(AGSurface* surface)
{
	prepareDraw( surface );

	while( m_shader->applyNextPass() )
	{
		/*
		 FirstCircle( from 0 to circleVerticesCount ) and then Other vertices wich include height lines and SecondCircle
		*/
		for( int i = 0; i < p->circleVerticesCount - 2; i++ )
		{
			surface->draw( 2, i ); 
		}
		for( int i = p->circleVerticesCount; i < p->vertices.size() - 2; i++ )
		{
			surface->draw( 2, i ); 
		}
	}
}

void AGCylinderShape::setRadius(float radius)
{
	p->size.setWidth( radius ); 
}

float AGCylinderShape::getRadius() const
{
	return p->size.getWidth(); 
}

void AGCylinderShape::setHeight(float height)
{
	p->size.setHeight( height );
}

float AGCylinderShape::getHeight() const
{
	return p->size.getHeight(); 
}

void AGCylinderShape::setSize(float radius, float height)
{
	p->size = AGSize( radius, height );
}

void AGCylinderShape::setSize(const AGSize& size)
{
	p->size = size; 
}

const AGSize& AGCylinderShape::getSize() const
{
	return p->size; 
}

void AGCylinderShape::setupShape()
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
	AGMath::generateCircle2D( p->size.getWidth(), step, points );

	int pointsSize = points.size();

	AGVec2 centerPoint( 0.0f, 0.0f );

	AGColorVertex tVert; 

	for( int i = 0; i < points.size(); i++ )
	{
		tVert.pos.x = points[ i ].x; 
		tVert.pos.y = 0; 
		tVert.pos.z = points[ i ].y; 
		tVert.color = m_color; 
		p->vertices.push_back( tVert );

		tVert.pos.y = p->size.getHeight(); 
	}

	int divider = 2;

	p->circleVerticesCount = pointsSize; 

	for( int i = 0; i < points.size(); i++ )
	{
		tVert.pos.x = points[ i ].x; 
		tVert.pos.y = p->size.getHeight(); 
		tVert.pos.z = points[ i ].y; 
		tVert.color = m_color; 
		p->vertices.push_back( tVert );

		if( i % divider == 0 )
		{
			tVert.pos.y = 0;
			p->vertices.push_back( tVert );
			tVert.pos.y = p->size.getHeight();
			p->vertices.push_back( tVert );
		}
	}

	m_vertexBuffer = new AGBuffer< AGColorVertex >( p->vertices, AGBufferType::Vertex );
}

