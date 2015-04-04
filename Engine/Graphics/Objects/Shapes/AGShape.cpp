#include "AGShape.h"

#include <assert.h>

#include "Engine/Managers/AGResourceManager.h"

#include "Engine/Graphics/Interfaces/AGSurface.h"

AGShape::AGShape(const AGColor& color)
{
	m_color = color; 

	m_shader = AGResourceManager::getInstance().getShader( L"shape" );

	assert( m_shader );

	m_vertexBuffer = nullptr;
	m_indexBuffer = nullptr; 
}

AGShape::~AGShape()
{

}

void AGShape::setColor(const AGColor& color)
{
	m_color = color; 
}

const AGColor& AGShape::getColor() const
{
	return m_color; 
}

void AGShape::prepareDraw(AGSurface* surface)
{
	assert( surface );

	AGCamera* camera = surface->getCamera(); 
	ID3D10Device* device = surface->getDevice(); 

	assert( camera );
	assert( device );

	assert( m_shader ); 
	m_shader->applySurface( surface );
	m_shader->setWorldMatrix( getResultMatrix() );

	assert( m_vertexBuffer );
	m_vertexBuffer->apply( surface );

	if( m_indexBuffer )
	{
		m_indexBuffer->apply( surface );
	}

	AGInputLayout* inputLayout = AGGraphics::getInstance().getInputLayout( device );
	assert( inputLayout );

	device->IASetInputLayout( inputLayout->colorVertexInputLayout );

	device->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_LINELIST );
}

