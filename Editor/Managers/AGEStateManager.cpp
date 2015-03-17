#include "AGEStateManager.h"

#include <windows.h>

void AGEStateManager::init()
{
	m_isRotating = false; 
	m_isConsoleMode = false; 
	m_isShowingAxis = false;
	m_isCameraFovChanged = false;
	m_isPlayMode = true; 
	m_isShowingMouseArrow = true; 
	m_cameraFov = 70; 
	m_coordSystem = Local; 
	m_toolBarState = Axis;
}

void AGEStateManager::setRotating(bool value)
{
	m_isRotating = value;
	setShowingMouseArrow( !value );
}

bool AGEStateManager::isRotating() const
{
	return m_isRotating; 
}

void AGEStateManager::setCoordystem(CoordSystem system)
{
	m_coordSystem = system; 
}

AGEStateManager::CoordSystem AGEStateManager::getCoordSystem() const
{
	return m_coordSystem;
}

void AGEStateManager::setToolBarState(ToolBarState state)
{
	m_toolBarState = state; 
}

AGEStateManager::ToolBarState AGEStateManager::getToolBarState() const
{
	return m_toolBarState; 
}

void AGEStateManager::setShowingAxis(bool value)
{
	m_isShowingAxis = value; 
}

bool AGEStateManager::isShowingAxis() const
{
	return m_isShowingAxis; 
}

void AGEStateManager::setConsoleMode(bool value)
{
	m_isConsoleMode = value; 
}

bool AGEStateManager::isConsoleMode() const
{
	return m_isConsoleMode; 
}

void AGEStateManager::setCameraFov(int fov)
{
	m_cameraFov = fov;
	m_isCameraFovChanged = true; 
}

int AGEStateManager::getCameraFov()
{
	m_isCameraFovChanged = false;
	return m_cameraFov; 
}

bool AGEStateManager::isCameraFovChanged() const
{
	return m_isCameraFovChanged; 
}

void AGEStateManager::setShowingMouseArrow(bool value)
{
	if( m_isShowingMouseArrow == value )
		return; 
	ShowCursor( value );
	m_isShowingMouseArrow = value; 
}

bool AGEStateManager::isShowingMouseArrow() const
{
	return m_isShowingMouseArrow; 
}

void AGEStateManager::setPlayMode(bool value)
{
	m_isPlayMode = value; 
}

bool AGEStateManager::isPlayMode() const
{
	return m_isPlayMode; 
}
