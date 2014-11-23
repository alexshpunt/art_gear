#include "AGGraphicsSettings.h"

void AGGraphicsSettings::init()
{
	m_screenWidth = 0;
	m_screenHeight = 0; 

	m_system = DX; 
}

void AGGraphicsSettings::setScreenWidth( int width )
{
	if( width > 0 )
	{
		m_screenWidth = width;
	}
}

int AGGraphicsSettings::getScreenWidth() const
{
	return m_screenWidth; 
}

void AGGraphicsSettings::setScreenHeight( int height )
{
	if( height > 0 )
	{
		m_screenHeight = height;
	}
}

int AGGraphicsSettings::getScreenHeight() const
{
	return m_screenHeight; 
}

float AGGraphicsSettings::getAspectRatio()
{
	if( m_screenHeight == 0 )
	{
		return 1.0f; 
	}
	return (float)m_screenWidth / (float)m_screenHeight; 
}

AGSize AGGraphicsSettings::getSize()
{
	return AGSize( m_screenWidth, m_screenHeight );
}

void AGGraphicsSettings::setGraphicsSystem(GraphicsSystem graphicsSystem)
{
	m_system = graphicsSystem; 
}

AGGraphicsSettings::GraphicsSystem AGGraphicsSettings::getGraphicsSystem() const
{
	return m_system; 
}

