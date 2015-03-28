#ifndef AG_WINAPI_H
#define AG_WINAPI_H

//////////////////////////////////////////////////////////////////////////////////
///This file contains functions witch is used to convert 3rd parties 
///structs to ArtGear structs vice versa 
/////////////////////////////////////////////////////////////////////////////////

#include <windows.h>

#include <d3dx10.h>
#include <d3d10.h>

#include "Engine/Math/AGMath.h"

/* List: 
	- RECT <-> AGRect
	- AGVec3 <-> AGVec3 
	- D3DXCOLOR <-> AGColor
	- POINT <-> AGPoint2
*/

namespace AGConversion
{
	RECT toWinAPIRect( const AGRect& rect );
	AGRect toAGRect( const RECT& rect );
	
	AGVec3 toD3DXVec3D( const AGVec3& vec3 ); 
	AGVec3 toAGVec3D( const AGVec3& vec3 );

	D3DXCOLOR toD3DXColor( const AGColor& color );
	AGColor toAGColor( const D3DXCOLOR& color );

	POINT toWinAPIPoint2D( const AGPoint2& point ); 
	AGPoint2 toAGPoint2D( const POINT& point ); 
};

#endif // !AG_WINAPI_H
