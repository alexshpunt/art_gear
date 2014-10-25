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
		AGWindow( HWND hwnd );
		AGWindow( const wstring& title, float x, float y, float width, float height );
		AGWindow( const wstring& title, const AGPoint2& point, float width, float height );
		AGWindow( const wstring& title, float x, float y, const AGSize& size );
		AGWindow( const wstring& title, const AGPoint2& point, const AGSize& size );
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

		void setPos( const AGPoint2& pos );
		void setPos( float x, float y );
		const AGPoint2& getPos() const;

		void setSize( const AGSize& size );
		void setSize( float w, float h );
		const AGSize& getSize() const;
		float getWidth() const;
		float getHeight() const; 

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