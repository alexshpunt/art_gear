#include "AGGizmo.h"

#include <Engine/Graphics/Objects/AGCamera.h>

#include <Editor/Managers/AGEStateManager.h>

AGGizmo::AGGizmo()
{
	m_isSelected = false; 
	m_distance = 1.0f;
	m_beginPos = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );

	m_vbo = nullptr;
	m_ibo = nullptr; 
}

AGGizmo::~AGGizmo()
{

}

void AGGizmo::setBeginPos(D3DXVECTOR3 beginPos)
{
	m_beginPos = beginPos; 
}

void AGGizmo::setBeginPos(float x, float y, float z)
{
	m_beginPos = D3DXVECTOR3( x, y ,z );
}

D3DXVECTOR3 AGGizmo::getBeginPos() const
{
	return m_beginPos; 
}

void AGGizmo::translateBeginPos(D3DXVECTOR3 delta)
{
	m_beginPos += delta;
}

void AGGizmo::translateBeginPos(float x, float y, float z)
{
	m_beginPos += D3DXVECTOR3( x, y, z );
}

void AGGizmo::setSelected(bool value)
{
	m_isSelected = value;
}

bool AGGizmo::isSelected() const
{
	return m_isSelected;
}

void AGGizmo::setDistance(float distance)
{
	m_distance = distance;
}

float AGGizmo::getDistance() const
{
	return m_distance; 
}

void AGGizmo::updatePos(AGCamera* camera)
{
	D3DXVECTOR3 camEye = camera->getPos(); 
	D3DXVECTOR3 dir = camEye - m_beginPos; 
	D3DXVec3Normalize( &dir, &dir );
	dir = camEye - dir * 1.5f; 
	D3DXVECTOR3 pos = dir; 

	setLocalPos( pos.x, pos.y, pos.z );
}

void AGGizmo::setupBuffers( AGSurface* surface )
{
	AGEStateManager::CoordSystem system = AGEStateManager::getInstance().getCoordSystem(); 

	m_shader->setWorldMatrix( system == AGEStateManager::Local ? getResultMatrix() : getLocalMatrix() );

	AGInputLayout* inputLayout = AGGraphics::getInstance().getInputLayout( surface->getDevice() );

	if( !inputLayout )
	{
		AGError() << "Cant get input layout for device " << AGCurFileFunctionLineSnippet; 
		return; 
	}

	surface->getDevice()->IASetInputLayout( inputLayout->colorVertexInputLayout );

	if( m_vertexBuffer )
	{
		m_vbo = m_vertexBuffer->applyTo( surface->getDevice() );
	}
	
	if( m_indexBuffer )
	{
		m_ibo = m_indexBuffer->applyTo( surface->getDevice() );	
	}
	
	if( !m_vbo )
	{
		AGError() << "Cant apply vertex buffer to device " << AGCurFileFunctionLineSnippet; 
		return; 
	}

	if( m_ibo )
	{
		surface->getDevice()->IASetIndexBuffer( m_ibo, DXGI_FORMAT_R32_UINT, 0 );
	}

	UINT stride = sizeof( AGPrimitiveVertex );
	UINT offset = 0; 
	surface->getDevice()->IASetVertexBuffers( 0, 1, &m_vbo, &stride, &offset );

	m_shader->applySurface( surface );
}

void AGGizmo::releaseBuffers()
{
	/*if( m_vbo )
		m_vbo->Release(); 
	if( m_ibo )
		m_ibo->Release(); */
}

