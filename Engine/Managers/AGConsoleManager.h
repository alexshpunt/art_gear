#ifndef AG_CONSOLEMANAGER_H
#define AG_CONSOLEMANAGER_H

#include <list>
#include <stack>
#include <string>

#include "Patterns/Singleton.h"

using namespace std;

#define AGConsoleInstance AGConsoleManager::getInstance()

class AGConsoleManager
{
	DECLARE_SINGLETON_INIT( AGConsoleManager )
	public:
		void execCommand(); 
		void execCommand( const string& command ); 
		void pushString( const string& string ); 
		const list< string >& getStrings() const; 

		const string popCommand(); 

		void pushChar( char inputChar );
		void popChar(); 
		string getInputLine() const; 

	private: 
		void init(); 

		string m_inputLine; 
		stack< string > m_commands; 
		stack< string > m_commandsToPop; 
		list< string > m_strings; 
};

#endif 