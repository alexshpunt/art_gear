#include "AGEDaylightShape.h"

#include <Engine/Managers/AGResourceManager.h>
#include "Engine/Utils/AGConversion.h"

AGEDaylightShape::AGEDaylightShape( float radius, float height, const AGColor& color )
{
	m_shader = AGResourceManager::getInstance().getShader( L"shape" );
	m_vertexBuffer = nullptr; 
	setSize( radius, height );
	setColor( color );
	setup(); 
}

AGEDaylightShape::~AGEDaylightShape()
{
}

void AGEDaylightShape::draw(AGSurface* surface)
{
	AGCamera* camera = surface->getCamera(); 
	ID3D10Device* device = surface->getDevice(); 

	m_shader->applySurface( surface );

	m_shader->setWorldMatrix( getResultMatrix() );

	ID3D10Buffer* vbo = m_vertexBuffer->applyTo( device );

	if( vbo )
	{
		UINT stride = sizeof( AGPrimitiveVertex );
		UINT offset = 0; 
		device->IASetVertexBuffers( 0, 1, &vbo, &stride, &offset );
	}
	else 
	{
		return; 
	}

	while( m_shader->applyNextPass() )
	{
		device->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_LINELIST );
		for( int i = 0; i < m_vertices.size() - 2; i++ )
		{
			device->Draw( 2, i );
		}
	}
}

void AGEDaylightShape::setRadius(float radius)
{
	m_size.setWidth( radius ); 
}

float AGEDaylightShape::getRadius() const
{
	return m_size.getWidth(); 
}

void AGEDaylightShape::setHeight(float height)
{
	m_size.setHeight( height );
}

float AGEDaylightShape::getHeight() const
{
	return m_size.getHeight(); 
}

void AGEDaylightShape::setSize(float radius, float height)
{
	m_size = AGSize( radius, height );
}

void AGEDaylightShape::setSize(const AGSize& size)
{
	m_size = size; 
}

const AGSize& AGEDaylightShape::getSize() const
{
	return m_size; 
}

void AGEDaylightShape::setColor( float r, float g, float b, float a )
{
	m_color = AGColor( r, g, b, a );
}

void AGEDaylightShape::setColor( int r, int g, int b, int a )
{
	m_color = AGColor( r, g, b, a );
}

void AGEDaylightShape::setColor(const AGColor& color)
{
	m_color = color; 
}

const AGColor& AGEDaylightShape::getColor() const
{
	return m_color; 
}

void AGEDaylightShape::setup()
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

	if( m_vertices.size() > 0 )
		m_vertices.clear(); 

	float step = AGMath::Pi / 6.0f; 
	vector< AGVec2 > points; 
	for( float angle = 0; angle < AGMath::PiX2; angle += step )
	{
		points.push_back( AGVec2( m_size.getWidth() * cos( angle ), m_size.getWidth() * sin( angle ) ) ); 
	}

	int pointsSize = points.size();

	AGVec2 centerPoint( 0.0f, 0.0f );

	AGPrimitiveVertex tVert; 

	int divider = 2;

	for( int i = 0; i < points.size(); i++ )
	{
		tVert.pos.x = points[ i ].x; 
		tVert.pos.y = 0; 
		tVert.pos.z = points[ i ].y; 
		tVert.color = D3DXVECTOR4( m_color.getRedF(), m_color.getGreenF(), m_color.getBlueF(), m_color.getAlphaF() ); 
		m_vertices.push_back( tVert );

		if( i % divider == 0 )
		{
			tVert.pos.y = m_size.getHeight();
			m_vertices.push_back( tVert );
			tVert.pos.y = 0;
			m_vertices.push_back( tVert );
		}
	}

	m_vertices.push_back( m_vertices[ pointsSize ] );

	m_vertexBuffer = new AGBuffer< AGPrimitiveVertex >( m_vertices, AGBufferType::Vertex );
}