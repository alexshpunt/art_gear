#include "AGDXGizmo.h"

AGDXGizmo::AGDXGizmo( ID3D10Device* device ) : AGDXPrimitive( device )
{
	m_isActivated = m_isSelected = false; 
	m_worldPos = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
}

AGDXGizmo::~AGDXGizmo()
{

}

void AGDXGizmo::setWorldPos(D3DXVECTOR3 worldPos)
{
	m_worldPos = worldPos; 
}

void AGDXGizmo::setWorldPos(float x, float y, float z)
{
	m_worldPos = D3DXVECTOR3( x, y ,z );
}

D3DXVECTOR3 AGDXGizmo::getWorldPos() const
{
	return m_worldPos; 
}

void AGDXGizmo::translateWorldPos(D3DXVECTOR3 delta)
{
	m_worldPos += delta;
}

void AGDXGizmo::translateWorldPos(float x, float y, float z)
{
	m_worldPos += D3DXVECTOR3( x, y, z );
}

void AGDXGizmo::setSelected(bool value)
{
	m_isSelected = value;
	//m_isActivated = value ? false : m_isActivated; 
}

bool AGDXGizmo::isSelected() const
{
	return m_isSelected;
}

void AGDXGizmo::setActivated(bool value)
{
	m_isActivated = value;
	//m_isSelected = value ? false : m_isSelected; 
}

bool AGDXGizmo::isActivated() const
{
	return m_isActivated;
}

