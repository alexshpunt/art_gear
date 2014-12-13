#ifndef AG_LOGGER_H
#define AG_LOGGER_H

#include <windows.h>
#include <string>

#include "Patterns/Singleton.h"
#include "Math/AGMath.h"

#define AGDebug() AGLogger::getInstance().getLoggerAtLevel( AGLogger::Debug ) 
#define AGSucces() AGLogger::getInstance().getLoggerAtLevel( AGLogger::Succes ) 
#define AGWarning() AGLogger::getInstance().getLoggerAtLevel( AGLogger::Warning ) 
#define AGError() AGLogger::getInstance().getLoggerAtLevel( AGLogger::Error ) 

using namespace std;

class AGLogger 
{
	DECLARE_SINGLETON_INIT( AGLogger )
	public:
		enum Modes { Console = 1, File = 2, Terminal = 4 };
		enum Levels { Debug, Warning, Error, Succes };

		void setMode( int mode );
		int getMode() const; 

		AGLogger& getLoggerAtLevel( Levels level );

		AGLogger& operator<<( int var );
		AGLogger& operator<<( float var ); 
		AGLogger& operator<<( double var );
		AGLogger& operator<<( char var );
		AGLogger& operator<<( bool var );
		AGLogger& operator<<( char* var );
		AGLogger& operator<<( const char* var );
		AGLogger& operator<<( const string& var );
		AGLogger& operator<<( wchar_t var );
		AGLogger& operator<<( wchar_t* var );
		AGLogger& operator<<( const wstring& var );
		AGLogger& operator<<( const AGSize& var );
		AGLogger& operator<<( const AGPoint2& var );
		AGLogger& operator<<( const AGRect& var );

	private:
		void init(); 

		HANDLE m_stdHandle; 
		bool m_skipLine; 
		int m_mode; 
		Levels m_level; 
};

#endif