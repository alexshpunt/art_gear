#include "AGStateManager.h"

void AGStateManager::init()
{
	m_isRotating = false; 
	m_coordSystem = Local; 
	m_toolBarState = Axis;
}

void AGStateManager::setRotating(bool value)
{
	m_isRotating = value;
}

bool AGStateManager::isRotating() const
{
	return m_isRotating; 
}

void AGStateManager::setCoordystem(CoordSystem system)
{
	m_coordSystem = system; 
}

AGStateManager::CoordSystem AGStateManager::getCoordSystem() const
{
	return m_coordSystem;
}

void AGStateManager::setToolBarState(ToolBarState state)
{
	m_toolBarState = state; 
}

AGStateManager::ToolBarState AGStateManager::getToolBarState() const
{
	return m_toolBarState; 
}
