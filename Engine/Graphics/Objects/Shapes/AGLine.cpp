#include "AGLine.h"

AGLine::AGLine( const AGVec3& startPoint, const AGVec3& endPoint, const AGColor& color ) : AGShape( color )
{
	setLine( startPoint, endPoint, color );
}

AGLine::~AGLine()
{

}

void AGLine::setLine( const AGVec3& startPoint, const AGVec3& endPoint, const AGColor& color )
{
	if( m_vertexBuffer )
		delete m_vertexBuffer; 

	vector< AGColorVertex > vertices; 

	AGColorVertex vertex; 
	vertex.color = color;

	vertex.pos = startPoint; 
	vertices.push_back( vertex );
	
	vertex.pos = endPoint; 
	vertices.push_back( vertex );
	
	m_vertexBuffer = new AGBuffer< AGColorVertex >( vertices, AGBufferType::Vertex );

}

void AGLine::draw( AGSurface* surface )
{
	prepareDraw( surface );

	while( m_shader->applyNextPass() )
	{
		surface->draw( 2, 0 );
	}
}

void AGLine::setupShape()
{

}

