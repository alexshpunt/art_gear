#include "AGEWindow.h"

#include <QDebug>
#include <QResizeEvent>

#include <vector>
#include <math.h>
#include <windows.h>

#include "Managers/AGInputManager.h"
#include "Managers/AGGraphicsSettings.h"
#include "Managers/AGEStateManager.h"
#include "Graphics/AGGraphics.h"
#include "Graphics/Objects/AGCamera.h"
#include "Graphics/Objects/AGMesh.h"
#include "Managers/AGLogger.h"

using namespace std;

#ifndef HID_USAGE_PAGE_GENERIC
#define HID_USAGE_PAGE_GENERIC         ((USHORT) 0x01)
#endif
#ifndef HID_USAGE_GENERIC_MOUSE
#define HID_USAGE_GENERIC_MOUSE        ((USHORT) 0x02)
#endif

AGEWindow::AGEWindow() : AGSurface()
{
	setMinimumSize( 100, 100 );
	resize( 800, 600 );
	setAttribute( Qt::WA_PaintOnScreen );
	setAttribute( Qt::WA_NativeWindow );

	setup( 800, 600, (HWND)winId() );

	AGGraphicsSettings::getInstance().setScreenWidth( 800 );
	AGGraphicsSettings::getInstance().setScreenHeight( 600 );

	RAWINPUTDEVICE Rid[1];
	Rid[0].usUsagePage = HID_USAGE_PAGE_GENERIC; 
	Rid[0].usUsage = HID_USAGE_GENERIC_MOUSE; 
	Rid[0].dwFlags = RIDEV_INPUTSINK;   
	Rid[0].hwndTarget = (HWND)winId();
	RegisterRawInputDevices(Rid, 1, sizeof(Rid[0] ) );
}

AGEWindow::~AGEWindow()
{

}

void AGEWindow::resizeEvent(QResizeEvent* event)
{
	resizeSurface( event->size().width(), event->size().height() );
}

QPaintEngine* AGEWindow::paintEngine() const
{
	return nullptr;
}

bool AGEWindow::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
	MSG* msg = (MSG*)message; 
	int key = ( int )msg->wParam; 

	UINT dwSize = 40;
	static BYTE lpb[40];
	RAWINPUT* raw = (RAWINPUT*)lpb;

	switch( msg->message )
	{
		case WM_LBUTTONDOWN:
			AGInput().setButtonPressed( "LMB", true );
			AGGraphics::getInstance().mouseClickEvent( AGMouseButton::LMB );
		break;
		case WM_LBUTTONUP: 
			AGInput().setButtonPressed( "LMB", false );
		break;
		case WM_LBUTTONDBLCLK:
	
		break;
		case WM_RBUTTONDOWN:
			AGInput().setButtonPressed( "RMB", true );
			AGGraphics::getInstance().mouseClickEvent( AGMouseButton::RMB );
		break;
		case WM_RBUTTONUP:
			AGInput().setButtonPressed( "RMB", false );
		break;
		case WM_RBUTTONDBLCLK:

		break;
		case WM_MBUTTONDOWN:
			AGInput().setButtonPressed( "MMB", true );
			AGGraphics::getInstance().mouseClickEvent( AGMouseButton::MMB );
		break;
		case WM_MBUTTONUP:
			AGInput().setButtonPressed( "MMB", false );
		break;
		case WM_MBUTTONDBLCLK:

		break; 
		case WM_INPUT:
			GetRawInputData((HRAWINPUT)msg->lParam, RID_INPUT, 
				lpb, &dwSize, sizeof(RAWINPUTHEADER));


			if (raw->header.dwType == RIM_TYPEMOUSE) 
			{
				int xPosRelative = raw->data.mouse.lLastX;
				int yPosRelative = raw->data.mouse.lLastY;

				AGInput().setMouseDeltaPos( AGPoint2( xPosRelative, yPosRelative ) );

			} 

			AGGraphics::getInstance().mouseMoveEvent();
		break;
		case WM_MOUSEMOVE:
			AGPoint2 mousePos;
			POINT point; 
			GetCursorPos( &point );
			ScreenToClient( (HWND)winId(), &point );
			mousePos.x = point.x;
			mousePos.y = point.y; 


			/*if( AGEStateManager::getInstance().isRotating() )
			{
				AGInput().setMousePos( mousePos, true );
				if( mousePos.x < 10 )
				{
					mousePos.x = m_size.getWidth() - 10;
				}
				else if( mousePos.x > m_size.getWidth() - 10 )
				{
					mousePos.x = 10; 
				}
				if( mousePos.y < 10 )
				{
					mousePos.y = m_size.getHeight() - 10; 
				}
				else if( mousePos.y > m_size.getHeight() - 10 )
				{
					mousePos.y = 10; 
				}
				point.x = mousePos.x;
				point.y = mousePos.y;
				ClientToScreen( (HWND)winId(), &point );
				SetCursorPos( point.x, point.y );
				AGInput().setMousePos( mousePos );
			}*/
			 
			{
				AGInput().setMousePos( mousePos );
			}
			//AGGraphics::getInstance().mouseMoveEvent(); 
		break;
	}
	return false; 
}

void AGEWindow::update()
{

}






