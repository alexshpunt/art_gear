#include "AGConversion.h"

RECT AGConversion::toWinAPIRect(const AGRect& rect)
{
	RECT wRect;
	wRect.bottom = rect.getBottom();
	wRect.top = rect.getTop();
	wRect.left = rect.getLeft();
	wRect.right = rect.getRight();

	return wRect; 
}

AGRect AGConversion::toAGRect(const RECT& rect)
{
	return AGRect( rect.left, rect.top, rect.right, rect.bottom );
}

D3DXVECTOR3 AGConversion::toD3DXVec3D(const AGVec3& vec3)
{
	return D3DXVECTOR3( vec3.x, vec3.y, vec3.z );
}

AGVec3 AGConversion::toAGVec3D(const D3DXVECTOR3& vec3)
{
	return AGVec3( vec3.x, vec3.y, vec3.z );
}

D3DXCOLOR AGConversion::toD3DXColor(const AGColor& color)
{
	return D3DXCOLOR( color.getRedF(), color.getGreenF(), color.getBlueF(), color.getAlphaF() );
}

AGColor AGConversion::toAGColor(const D3DXCOLOR& color)
{
	return AGColor( color.r, color.g, color.b, color.a );
}

POINT AGConversion::toWinAPIPoint2D(const AGPoint2& point)
{
	POINT wPoint;
	wPoint.x = point.x; 
	wPoint.y = point.y; 

	return wPoint; 
}

AGPoint2 AGConversion::toAGPoint2D(const POINT& point)
{
	return AGPoint2( point.x, point.y );
}

