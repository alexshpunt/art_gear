#include "AGStateManager.h"

void AGStateManager::init()
{
	m_isRotating = false; 
}

void AGStateManager::setRotating(bool value)
{
	m_isRotating = value;
}

bool AGStateManager::isRotating() const
{
	return m_isRotating; 
}
