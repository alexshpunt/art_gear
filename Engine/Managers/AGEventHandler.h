#ifndef AG_EVENTHANDLER_H
#define AG_EVENTHANDLER_H

#include <windows.h>

typedef void (*UpdateFunc)(); 

LRESULT CALLBACK AGWindowEventHandler( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam );
bool AGMainLoopHandler( UpdateFunc func ); 

#endif 