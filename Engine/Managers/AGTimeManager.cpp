#include "AGTimeManager.h"

void AGTimeManager::setDeltaTime(double dt)
{
	m_dt = dt; 
}

double AGTimeManager::getDeltaTime() const
{
	return m_dt; 
}

void AGTimeManager::init()
{
	m_dt = 0.0;
}

