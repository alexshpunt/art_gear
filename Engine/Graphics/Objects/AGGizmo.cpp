#include "AGGizmo.h"

#include "Engine/Math/AGMath.h"

#include "Engine/Graphics/Objects/AGCamera.h"

#include "Editor/Managers/AGEStateManager.h"

AGGizmo::AGGizmo()
{
	m_isSelected = false; 
	m_distance = 1.0f;
	m_beginPos = AGVec3( 0.0f, 0.0f, 0.0f );

	m_vbo = nullptr;
	m_ibo = nullptr; 
}

AGGizmo::~AGGizmo()
{

}

void AGGizmo::setBeginPos(AGVec3 beginPos)
{
	m_beginPos = beginPos; 
}

void AGGizmo::setBeginPos(float x, float y, float z)
{
	m_beginPos = AGVec3( x, y ,z );
}

AGVec3 AGGizmo::getBeginPos() const
{
	return m_beginPos; 
}

void AGGizmo::translateBeginPos(AGVec3 delta)
{
	m_beginPos += delta;
}

void AGGizmo::translateBeginPos(float x, float y, float z)
{
	m_beginPos += AGVec3( x, y, z );
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
	AGVec3 camEye = camera->getPos(); 
	AGVec3 dir = ( camEye - m_beginPos ).normilized(); 
	dir = camEye - dir * 1.5f; 

	setLocalPos( dir );
}

void AGGizmo::setupBuffers( AGSurface* surface )
{
	AGEStateManager::CoordSystem system = AGEStateManager::getInstance().getCoordSystem(); 

	m_shader->setWorldMatrix( system == AGEStateManager::Local ? getResultMatrix() : getLocalMatrix() );

	AGInputLayout* inputLayout = AGGraphics::getInstance().getInputLayout( surface->getDevice() );

	assert( inputLayout ); 

	surface->getDevice()->IASetInputLayout( inputLayout->colorVertexInputLayout );

	if( m_vertexBuffer )
	{
		m_vertexBuffer->apply( surface );
	}
	if( m_indexBuffer )
	{
		m_indexBuffer->apply( surface );
	}

	m_shader->apply( surface );
}

