#include "AGEWindow.h"

#include <QDebug>
#include <QResizeEvent>

#include <vector>
#include <math.h>
#include <windows.h>

#include "Managers/AGInputManager.h"
#include "Managers/AGGraphicsSettings.h"
#include "Graphics/AGGraphics.h"
#include "Graphics/Objects/AGDXBoundingBox.h"
#include "Graphics/Objects/AGDXCamera.h"
#include "Graphics/Objects/AGDXMesh.h"
#include "Managers/AGLogger.h"

using namespace std;

AGEWindow::AGEWindow() : AGDXSurface( 800, 600, (HWND)winId() )
{
	setMinimumSize( 800, 600 );
	resize( 800, 600 );
	setAttribute( Qt::WA_PaintOnScreen );
	setAttribute( Qt::WA_NativeWindow );
	

	AGGraphicsSettings::getInstance().setScreenWidth( 800 );
	AGGraphicsSettings::getInstance().setScreenHeight( 600 );
}

AGEWindow::~AGEWindow()
{

}

void AGEWindow::resizeEvent(QResizeEvent* event)
{
	resizeSurface( event->size().width(), event->size().height() );
}

void AGEWindow::paintEvent(QPaintEvent* event)
{
	if( !m_device ) 
		return; 
}

QPaintEngine* AGEWindow::paintEngine() const
{
	return nullptr;
}

bool AGEWindow::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
	MSG* msg = (MSG*)message; 
	int key = ( int )msg->wParam; 
	switch( msg->message )
	{
		case WM_LBUTTONDOWN:
			AGInput().setButtonPressed( "LMB", true );
			AGGraphics::getInstance().mouseClickEvent( "LMB" );
		break;
		case WM_LBUTTONUP: 
			AGInput().setButtonPressed( "LMB", false );
		break;
		case WM_LBUTTONDBLCLK:

		break;
		case WM_RBUTTONDOWN:
			AGInput().setButtonPressed( "RMB", true );
			AGGraphics::getInstance().mouseClickEvent( "RMB" );
		break;
		case WM_RBUTTONUP:
			AGInput().setButtonPressed( "RMB", false );
		break;
		case WM_RBUTTONDBLCLK:

		break;
		case WM_MBUTTONDOWN:
			AGInput().setButtonPressed( "MMB", true );
			AGGraphics::getInstance().mouseClickEvent( "MMB" );
		break;
		case WM_MBUTTONUP:
			AGInput().setButtonPressed( "MMB", false );
		break;
		case WM_MBUTTONDBLCLK:

		break; 
		case WM_MOUSEMOVE:
			AGPoint2 mousePos;
			POINT point; 
			GetCursorPos( &point );
			ScreenToClient( (HWND)winId(), &point );
			mousePos.x = point.x;
			mousePos.y = point.y; 
			AGInput().setMousePos( mousePos );
			AGGraphics::getInstance().mouseMoveEvent(); 
		break;
	}
	return false; 
}







