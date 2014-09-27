#include "AGEventHandler.h"

LRESULT CALLBACK AGWindowEventHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch( msg )
	{
		case WM_DESTROY:
			PostQuitMessage( 0 );
			break; 
		break;
		default:
			return DefWindowProc( hwnd, msg, wParam, lParam ); 
		break;
	}
}

bool AGMainLoopHandler(UpdateFunc func)
{
	MSG msg = {}; 

	if( PeekMessage( &msg, 0, 0, 0, PM_REMOVE ) )
	{
		TranslateMessage( &msg );
		DispatchMessage( &msg );
	}
	{
		func(); 
	}

	return msg.message == WM_QUIT; 
}

