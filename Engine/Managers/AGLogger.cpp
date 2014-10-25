#include "AGLogger.h"

#include <windows.h>
#include <iostream>

void AGLogger::initialize()
{
	m_mode = 0; 
	m_skipLine = false; 
}

void AGLogger::setMode(int mode)
{
	m_mode = mode; 

	if( mode | Terminal )
	{
		AllocConsole();
		m_stdHandle = GetStdHandle( STD_OUTPUT_HANDLE );
		SetConsoleTitle( L"ArtGear - Console" );
	}
	else 
	{
		FreeConsole(); 
		m_stdHandle = nullptr; 
	}
}

int AGLogger::getMode() const
{
	return m_mode; 
}

AGLogger& AGLogger::skipLineIfNeeded()
{
	if( m_skipLine )
		*this << '\n';
	return *this; 
}

AGLogger& AGLogger::operator<<(int var)
{
	m_skipLine = true;
	 
	if( m_mode | Terminal )
		cout << var; 

	return *this; 
}

AGLogger& AGLogger::operator<<(float var)
{
	m_skipLine = true;

	if( m_mode | Terminal )
		cout << var; 
	return *this; 
}

AGLogger& AGLogger::operator<<(double var)
{
	m_skipLine = true;

	if( m_mode | Terminal )
		cout << var; 
	return *this; 
}

AGLogger& AGLogger::operator<<(char var)
{
	m_skipLine = true;

	if( m_mode | Terminal )
		cout << var; 
	return *this; 
}

AGLogger& AGLogger::operator<<(bool var)
{
	m_skipLine = true;

	if( m_mode | Terminal )
		cout << ( var ? "true" : "false" ); 
	return *this; 
}

AGLogger& AGLogger::operator<<(char* var)
{
	m_skipLine = true;

	if( m_mode | Terminal )
		cout << var; 
	return *this; 
}

AGLogger& AGLogger::operator<<(const string& var)
{
	m_skipLine = true;

	if( m_mode | Terminal )
		cout << var; 
	return *this; 
}

AGLogger& AGLogger::operator<<(wchar_t var)
{
	m_skipLine = true;

	if( m_mode | Terminal )
		wcout << var; 
	return *this; 
}

AGLogger& AGLogger::operator<<(wchar_t* var)
{
	m_skipLine = true;

	if( m_mode | Terminal )
		wcout << var; 
	return *this; 
}

AGLogger& AGLogger::operator<<(const wstring& var)
{
	m_skipLine = true;

	if( m_mode | Terminal )
		wcout << var; 
	return *this; 
}

AGLogger& AGLogger::operator<<(const AGSize& var)
{
	m_skipLine = true;
	cout << "AGSize( width : " << var.getWidth() << " ; height : " << var.getHeight() << " ) ";
	return *this; 
}

AGLogger& AGLogger::operator<<(const AGPoint2& var)
{
	m_skipLine = true;
	cout << "AGPoint( x : " << var.x << " ; y : " << var.y << " ) ";
	return *this; 
}

AGLogger& AGLogger::operator<<(const AGRect& var)
{
	m_skipLine = true;
	cout << "AGRect( left : " << var.getLeft() << " ; top : " << var.getTop() <<
		 " ; right : " << var.getRight() << " ; bottom : " << var.getBottom() << " ) ";
	return *this; 
}

AGLogger& AGLogger::setLevel(Levels level)
{
	m_level = level; 
	if( m_stdHandle )
	{
		if( m_level == Debug )
		{
			SetConsoleTextAttribute( m_stdHandle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | BACKGROUND_BLUE );
		}
		else if( m_level == Warning )
		{
			SetConsoleTextAttribute( m_stdHandle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | BACKGROUND_BLUE );
		} 
		else if( m_level == Error )
		{
			SetConsoleTextAttribute( m_stdHandle, FOREGROUND_RED | BACKGROUND_RED | BACKGROUND_INTENSITY );
		}
		else if( m_level == Succes )
		{
			SetConsoleTextAttribute( m_stdHandle, FOREGROUND_INTENSITY | FOREGROUND_GREEN );
		}
	}
	return *this;
}

AGLogger::Levels AGLogger::getLevel() const
{
	return m_level; 
}





