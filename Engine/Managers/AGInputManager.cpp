#include "AGInputManager.h"

#include <windows.h>
#include <Managers/AGLogger.h>

void AGInputManager::update()
{
	m_mouseDeltaPos = AGPoint2( 0.0f, 0.0f );
	m_wheelDelta = 0.0f; 
}

void AGInputManager::setKeyPressed(int key, bool flag)
{
	m_keyPressed[ key ] = flag;
	m_keyDown[ key ] = flag;
	m_keyUp[ key ] = !flag;
}

bool AGInputManager::isKeyPressed(int key)
{
	if( m_keyPressed.find( key ) != m_keyPressed.end() )
		return m_keyPressed.at( key );
	return false; 
}

bool AGInputManager::isKeyDown(int key)
{
	if( m_keyDown.find( key ) == m_keyDown.end() )
	{
		bool value = m_keyDown.at( key );
		m_keyDown[ key ] = false;
		return value; 
	}
	return false; 
}

bool AGInputManager::isKeyUp(int key)
{
	if( m_keyUp.find( key ) != m_keyUp.end() )
	{
		bool value = m_keyUp.at( key );
		m_keyUp[ key ] = false;
		return value; 
	}
	return false; 
}

bool AGInputManager::isKeyPressed( string key )
{
	if( key == "Alt" )
		return ( GetKeyState( VK_LMENU ) < 0 );
	if( key == "Shift" )
		return ( GetKeyState( VK_LSHIFT ) < 0 );
	return isKeyPressed( fromNameToCode( key ) );
}

bool AGInputManager::isKeyDown( string key )
{
	if( key == "Alt" )
		return ( GetKeyState( VK_LMENU ) < 0 );
	return isKeyDown( fromNameToCode( key ) );
}

bool AGInputManager::isKeyUp( string key )
{
	if( key == "Alt" )
		return ( GetKeyState( VK_LMENU ) > 0 );
	return isKeyUp( fromNameToCode( key ) );
}

void AGInputManager::setButtonPressed( const string& button, bool flag )
{
	m_buttonsMapPressed[ button ] = flag; 
	m_buttonsMapDown[ button ] = flag;
	m_buttonsMapUp[ button ] = !flag;
}

bool AGInputManager::isButtonPressed(const string& button)
{
	if( m_buttonsMapPressed.find( button ) != m_buttonsMapPressed.end() )
		return m_buttonsMapPressed.at( button );
	return false; 
}

bool AGInputManager::isButtonDown(const string& button)
{
	if( m_buttonsMapDown.find( button ) != m_buttonsMapDown.end() )
	{
		bool value = m_buttonsMapDown.at( button );
		m_buttonsMapDown[ button ] = false;
		return value; 
	}
	return false; 
}

bool AGInputManager::isButtonUp(const string& button)
{
	if( m_buttonsMapUp.find( button ) != m_buttonsMapUp.end() )
	{
		bool value = m_buttonsMapUp.at( button );
		m_buttonsMapUp[ button ] = false;
		return value; 
	}
	return false; 
}

int AGInputManager::fromNameToCode( string key )
{
	if( key == "Space" )
		key = (char)32; 
	else if( key == "Shift" )
		key = (char)VK_SHIFT;
	else if( key == "Ctrl" )
		key = (char)162;
	else if( key == "Alt" )
		key = (char)VK_MENU; 
	else if( key == "Enter" )
		key = (char)13;

	return (int)&key[0]; 
}

void AGInputManager::setMousePos( AGPoint2 pos, bool lockDelta )
{
	if( !m_lockDelta )
	{
		m_mouseDeltaPos = pos - m_mousePos;
		m_lockDelta = false;
	}
	m_mousePos = pos; 
	m_lockDelta = lockDelta;
}

const AGPoint2& AGInputManager::getMousePos() const
{
	return m_mousePos;
}

AGPoint2 AGInputManager::getMouseDeltaPos()
{
	return m_mouseDeltaPos;
}

void AGInputManager::init()
{
	m_wheelDelta = 0.0f; 
	m_lockDelta = false;
}

void AGInputManager::setWheelDelta(float wheelDelta)
{
	m_wheelDelta = wheelDelta / 120.0f; 
}

float AGInputManager::getWheelDelta()
{	
	return m_wheelDelta; 
}


