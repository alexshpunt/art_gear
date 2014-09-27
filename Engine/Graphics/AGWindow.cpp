#include "AGWindow.h"

#include "Managers/AGEventHandler.h"

AGWindow::AGWindow()
{
	m_rect = AGRect( 0, 0, 800, 600 );
	m_title = L"ArtGear - Default Window";
	createWindow(); 
}

AGWindow::AGWindow(const wstring& title, float x, float y, float width, float height)
{
	m_title = title; 
	m_rect = AGRect( x, y, width, height );
	createWindow(); 
}

AGWindow::AGWindow(const wstring& title, const AGPoint& point, float width, float height)
{
	m_title = title;
	m_rect = AGRect( point, width, height );
	createWindow(); 
}

AGWindow::AGWindow(const wstring& title, float x, float y, const AGSize& size)
{
	m_title = title;
	m_rect = AGRect( x, y, size );
	createWindow(); 
}

AGWindow::AGWindow(const wstring& title, const AGPoint& point, const AGSize& size)
{
	m_title = title;
	m_rect = AGRect( point, size );
	createWindow(); 
}

AGWindow::AGWindow(const wstring& title, const AGRect& rect)
{
	m_title = title;
	m_rect = rect;
	createWindow(); 
}

AGWindow::~AGWindow()
{
	DestroyWindow( m_hwnd );
}

void AGWindow::show()
{
	ShowWindow( m_hwnd, SW_SHOWNORMAL );
}

void AGWindow::showMaximized()
{
	ShowWindow( m_hwnd, SW_SHOWMAXIMIZED );
}

void AGWindow::showMinimized()
{
	ShowWindow( m_hwnd, SW_SHOWMINIMIZED );
}

void AGWindow::maximize()
{
	ShowWindow( m_hwnd, SW_MAXIMIZE );
}

void AGWindow::minimize()
{
	ShowWindow( m_hwnd, SW_MINIMIZE );
}

void AGWindow::restore()
{
	ShowWindow( m_hwnd, SW_RESTORE );
}

void AGWindow::hide()
{
	ShowWindow( m_hwnd, SW_HIDE );
}

void AGWindow::close()
{
	CloseWindow( m_hwnd );
}

void AGWindow::setPos(const AGPoint& pos)
{
	m_rect.setPoint( pos );
	MoveWindow( m_hwnd, pos.getX(), pos.getY(), m_rect.getWidth(), m_rect.getHeight(), TRUE );
}

const AGPoint& AGWindow::getPos() const
{
	return m_rect.getPoint();
}

void AGWindow::setSize(const AGSize& size)
{
	m_rect.setSize( size );
	MoveWindow( m_hwnd, m_rect.getLeft(), m_rect.getTop(), size.getWidth(), size.getHeight(), TRUE );
}

const AGSize& AGWindow::getSize() const
{
	return m_rect.getSize();
}

void AGWindow::setRect(const AGRect& rect)
{
	m_rect = rect;
	MoveWindow( m_hwnd, m_rect.getLeft(), m_rect.getTop(), m_rect.getWidth(), m_rect.getHeight(), TRUE );
}

const AGRect& AGWindow::getRect() const
{
	return m_rect;
}

void AGWindow::setTitle(const wstring& title)
{
	m_title = title; 
	SetWindowTextW( m_hwnd, &title[0] );
}

const wstring& AGWindow::getTitle() const
{
	return m_title; 
}

void AGWindow::createWindow()
{
	WNDCLASSEX wndclass = {};
	ZeroMemory( &wndclass, sizeof( wndclass ) );
	wndclass.cbSize = sizeof( WNDCLASSEX );
	wndclass.hbrBackground = (HBRUSH)GetStockObject( WHITE_BRUSH );
	wndclass.lpfnWndProc = &AGWindowEventHandler; 
	wndclass.lpszClassName = L"AGWINDOW";
	wndclass.hInstance = GetModuleHandle( nullptr );
	wndclass.style = CS_HREDRAW | CS_VREDRAW; 
	wndclass.hCursor = LoadCursor( NULL, IDC_ARROW );
	wndclass.lpszMenuName = NULL; 

	RegisterClassEx( &wndclass );

	m_hwnd = CreateWindowW( L"AGWINDOW", &m_title[0], WS_OVERLAPPEDWINDOW, 
		m_rect.getLeft(), m_rect.getTop(), m_rect.getWidth(), m_rect.getHeight(), NULL, NULL, GetModuleHandle( NULL ), NULL ); 
}

HWND AGWindow::asHwnd() const
{
	return m_hwnd; 
}
