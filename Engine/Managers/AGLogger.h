#ifndef AG_LOGGER_H
#define AG_LOGGER_H

#include <windows.h>
#include <string>

#include "Patterns/Singleton.h"
#include "Math/AGMath.h"

#define AGDebug() AGLogger::getInstance().skipLineIfNeeded().setLevel( AGLogger::Debug ) 
#define AGSucces() AGLogger::getInstance().skipLineIfNeeded().setLevel( AGLogger::Succes ) 
#define AGWarning() AGLogger::getInstance().skipLineIfNeeded().setLevel( AGLogger::Warning ) 
#define AGError() AGLogger::getInstance().skipLineIfNeeded().setLevel( AGLogger::Error ) 

using namespace std;

class AGLogger 
{
	DECLARE_SINGLETON( AGLogger )
	public:
		enum Modes { Console = 1, File = 2, Terminal = 4 };
		enum Levels { Debug, Warning, Error, Succes };

		void initialize(); 

		void setMode( int mode );
		int getMode() const; 

		AGLogger& setLevel( Levels level );
		Levels getLevel() const; 

		AGLogger& skipLineIfNeeded(); 

		AGLogger& operator<<( int var );
		AGLogger& operator<<( float var ); 
		AGLogger& operator<<( double var );
		AGLogger& operator<<( char var );
		AGLogger& operator<<( bool var );
		AGLogger& operator<<( char* var );
		AGLogger& operator<<( const string& var );
		AGLogger& operator<<( wchar_t var );
		AGLogger& operator<<( wchar_t* var );
		AGLogger& operator<<( const wstring& var );
		AGLogger& operator<<( const AGSize& var );
		AGLogger& operator<<( const AGPoint& var );
		AGLogger& operator<<( const AGRect& var );

	private:
		HANDLE m_stdHandle; 
		bool m_skipLine; 
		int m_mode; 
		Levels m_level; 
};

#endif