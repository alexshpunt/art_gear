#include "AGConsoleManager.h"

#include <windows.h>

#include "Managers/AGEStateManager.h"
#include "Managers/AGLogger.h"

void AGConsoleManager::init()
{
	m_inputLine = "";
}

void AGConsoleManager::execCommand()
{
	if( m_inputLine.size() == 0 )
		return; 
	pushString( m_inputLine );
	m_commands.push( m_inputLine );

	int pos = m_inputLine.find( ' ' ); 
	string prop = m_inputLine.substr( 0, pos );
	string args = m_inputLine.substr( pos+1 ); 

	if( prop == "cam_fov" )
	{
		int fov = 0;
		for( int i = 0; i < args.size(); i++ )
		{
			fov *= 10; 
			fov += args[i] - '0'; 
		}
		AGEStateManager::getInstance().setCameraFov( fov ); 
	}

	m_inputLine.clear(); 
	m_commandsToPop = m_commands; 
}

void AGConsoleManager::execCommand(const string& command)
{
	pushString( command );
	m_commands.push( command );
	m_commandsToPop = m_commands;
}

void AGConsoleManager::pushString(const string& string)
{
	if( m_strings.size() > 64 )
	{
		m_strings.pop_front(); 
	}
	m_strings.push_front( string );
}

const list< string >& AGConsoleManager::getStrings() const
{
	return m_strings; 
}

const string AGConsoleManager::popCommand()
{
	string command = m_commandsToPop.top(); 
	m_commandsToPop.pop(); 
	return command; 
}

void AGConsoleManager::pushChar(char inputChar)
{
	switch( inputChar )
	{
		case VK_BACK:
			popChar();
			return;
		break; 
		case VK_RETURN:
			execCommand();
			return; 
		break; 
	}
	m_inputLine.push_back( inputChar );
}

void AGConsoleManager::popChar()
{
	if( m_inputLine.size() > 0 )
		m_inputLine.pop_back(); 
}

std::string AGConsoleManager::getInputLine() const
{
	return m_inputLine; 
}
