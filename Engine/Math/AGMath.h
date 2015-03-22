#ifndef AG_MATH_H
#define AG_MATH_H

#include <vector>

#include "AGMatrix.h"
#include "AGPoint2.h"
#include "AGPoint3.h"
#include "AGQuat.h"
#include "AGRect.h"
#include "AGSize.h"
#include "AGVec2.h"
#include "AGVec3.h"
#include "AGColor.h"

namespace AGMath 
{
	///////////////////////////////////////////////////////////////////////////
	///“ригонометрические константы
	///////////////////////////////////////////////////////////////////////////
	const float Pi = 3.1415926535897932384626433832795f;
	//Pi multiply 2 
	const float PiX2 = Pi * 2; 
	const float Pi2 = Pi / 2.0f; 
	const float Pi3 = Pi / 3.0f;
	const float Pi4 = Pi / 4.0f;
	///////////////////////////////////////////////////////////////////////////
	//»спользуетс€ дл€ €вного указани€ способа определени€ угла
	///////////////////////////////////////////////////////////////////////////

	struct Degrees;
	struct Radians; 

	struct Degrees
	{
		explicit Degrees( float angle ) : value( angle ){}
		
		Radians toRadians()
		{
			return Radians( ( value * Pi) / 180.0f  );
		}

		operator float()
		{
			return value; 
		}
		
		float value; 
	};

	struct Radians
	{
		explicit Radians( float radian ) : value( radian ){}

		Degrees toDegrees()
		{
			return Degrees( ( 180.0f * value ) / Pi );
		}

		operator float()
		{
			return value; 
		}
		
		float value; 
	};

	template <class T>
	T toRadians( T var )
	{
		return ( var * Pi) / 180.0f; 
	}

	template <class T>
	T toDegrees( T var )
	{
		return ( 180.0f * value ) / Pi ; 
	}

	template< class T >
	T clamp( const T& var, const T& min, const T& max )
	{
		if( var > max )
			return max; 
		else if( var < min )
			return min;
		return var; 
	}

	template< class T > 
	T checkIfLower( const T& var, const T& min )
	{
		if( var < min )
			return min;
		else 
			return var; 
	}

	template< class T > 
	T checkIfGreater( const T& var, const T& max )
	{
		if( var > max )
			return max;
		else
			return var; 
	}

	bool isEqual( double a, double b );
	bool isEqual( float a, float b ); 

	void generateCircle2D( float radius, float step, std::vector< AGVec2 >& points );

	template < class T > 
	inline void swap( T& v1, T& v2 )
	{
		T& tmp = v1; 
		v1 = v2;
		v2 = tmp; 
	}
}

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