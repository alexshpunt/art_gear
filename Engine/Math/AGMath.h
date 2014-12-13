#ifndef AG_MATH_H
#define AG_MATH_H

#include "AGMatrix4x4.h"
#include "AGPoint2.h"
#include "AGPoint3.h"
#include "AGQuat.h"
#include "AGRect.h"
#include "AGSize.h"
#include "AGVec2.h"
#include "AGVec3.h"

template <class T>
T absMax( T v1, T v2 )
{
	T absV1 = abs( v1 );
	T absV2 = abs( v2 );

	if( absV1 > absV2 )
		return v1; 
	return v2; 
}

template <class T>
T absMin( T v1, T v2 )
{
	T absV1 = abs( v1 );
	T absV2 = abs( v2 );

	if( absV1 < absV2 )
		return v1; 
	return v2; 
}

#define sign( var ) ( ( ( var ) > 0 ) ? ( 1 ) : ( -1 ) )

#endif 