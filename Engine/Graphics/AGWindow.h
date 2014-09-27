#ifndef AG_WINDOW_H
#define AG_WINDOW_H

#include <string>
#include <windows.h>

#include "Math/AGMath.h"

using namespace std;

class AGWindow
{
	public:
		AGWindow();
		AGWindow( const wstring& title, float x, float y, float width, float height );
		AGWindow( const wstring& title, const AGPoint& point, float width, float height );
		AGWindow( const wstring& title, float x, float y, const AGSize& size );
		AGWindow( const wstring& title, const AGPoint& point, const AGSize& size );
		AGWindow( const wstring& title, const AGRect& rect );
		~AGWindow();

		void show();
		void showMaximized();
		void showMinimized(); 
		void maximize();
		void minimize();
		void restore();
		void hide(); 
		void close(); 

		void setPos( const AGPoint& pos );
		const AGPoint& getPos() const;

		void setSize( const AGSize& size );
		const AGSize& getSize() const;
		
		void setRect( const AGRect& rect );
		const AGRect& getRect() const; 

		void setTitle( const wstring& title );
		const wstring& getTitle() const; 

		HWND asHwnd() const; 
	private:
		void createWindow(); 

		HWND m_hwnd;
		AGRect m_rect; 
		wstring m_title; 
};

#endif 