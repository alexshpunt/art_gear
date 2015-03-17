#include "AGConeShape.h"

#include <Engine/Managers/AGResourceManager.h>
#include <Engine/Math/AGMath.h>

AGConeShape::AGConeShape(D3DXVECTOR4 color, float radius, float height)
{
	m_shader = AGResourceManager::getInstance().getShader( L"shape" );

	setColor( color );
	setRadius( radius );
	setHeight( height );
	setupShape(); 
}

AGConeShape::~AGConeShape()
{

}

void AGConeShape::draw(AGSurface* surface)
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

void AGConeShape::setRadius(float radius)
{
	if( radius > 0.001f )
		m_radius = radius; 
	else 
		m_radius = 0.001f; 
}

float AGConeShape::getRadius() const
{
	return m_radius; 
}

void AGConeShape::setHeight(float height)
{
	if( height > 0.001f ) 
		m_height = height;
	else 
		m_height = 0.001f; 
}

float AGConeShape::getHeight() const
{
	return m_height; 
}

void AGConeShape::setColor(D3DXVECTOR4 color)
{
	m_color = color; 
}

D3DXVECTOR4 AGConeShape::getColor() const
{
	return m_color; 
}

void AGConeShape::setupShape()
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
		points.push_back( AGVec2( m_radius * cos( angle ), m_radius * sin( angle ) ) ); 
	}

	AGVec2 centerPoint( 0.0f, 0.0f );

	AGPrimitiveVertex tVert; 

	for( int i = 0; i < points.size(); i++ )
	{
		tVert.pos.x = points[ i ].x; 
		tVert.pos.y = 0; 
		tVert.pos.z = points[ i ].y; 
		tVert.color = m_color; 
		m_vertices.push_back( tVert );
	}

	m_vertices.push_back( m_vertices[ 0 ] );

	int divider = 4; 
	int quarter = m_vertices.size() / divider; 

	tVert.pos = D3DXVECTOR3( 0.0f, m_height, 0.0f );
	tVert.color = m_color;

	for( int i = 0; i <= divider; i++ )
	{
		m_vertices.push_back( tVert );
		m_vertices.push_back( m_vertices[ quarter * i ] );	
	}

	m_vertexBuffer = new AGBuffer< AGPrimitiveVertex >( m_vertices, AGBufferType::Vertex );
}

