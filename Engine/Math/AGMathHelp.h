#ifndef AG_MATHHELP_H
#define AG_MATHHELP_H

#include <vector>

#define EPSILON_FOR_DOUBLE 0.0000001
#define EPSILON_FOR_FLOAT 0.0001f

class AGVec2; 

namespace AGMath 
{
	///////////////////////////////////////////////////////////////////////////
	///������������������ ���������
	///////////////////////////////////////////////////////////////////////////

	const float Pi = 3.1415926535897932384626433832795f;
	//Pi multiply 2 
	const float PiX2 = Pi * 2; 
	const float Pi2 = Pi / 2.0f; 
	const float Pi3 = Pi / 3.0f;
	const float Pi4 = Pi / 4.0f;

	///////////////////////////////////////////////////////////////////////////
	///������� �������������� �����
	///////////////////////////////////////////////////////////////////////////

	inline float toRadians( float var )
	{
		return ( var * Pi) / 180.0f; 
	}

	inline float toDegrees( float var )
	{
		return ( 180.0f * var ) / Pi ; 
	}

	///////////////////////////////////////////////////////////////////////////
	///������� ��������� 
	///////////////////////////////////////////////////////////////////////////

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

	///////////////////////////////////////////////////////////////////////////
	///������
	///////////////////////////////////////////////////////////////////////////

	void generateCircle2D( float radius, float step, std::vector< AGVec2 >& points );

	template < class T > 
	inline void swap( T& v1, T& v2 )
	{
		T& tmp = v1; 
		v1 = v2;
		v2 = tmp; 
	}
}

///////////////////////////////////////////////////////////////////////////
//������������ ��� ������ �������� ������� ����������� ����
///////////////////////////////////////////////////////////////////////////

struct AGDegrees;
struct AGRadians; 

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

struct AGDegrees
{
	explicit AGDegrees( float degrees ) : value( degrees ){}
	AGDegrees( const AGDegrees& degrees ) : value( degrees.value ){} 

	AGRadians toRadians();
	operator float() const
	{
		return value; 
	}

	AGDegrees& operator=( const AGDegrees& degrees ){ value = degrees.value; return *this; }
	bool operator==( const AGDegrees& d ) { return AGMath::isEqual( value, d.value ); }
	bool operator==( float var ) { return AGMath::isEqual( value, var ); }

	friend AGDegrees operator+( const AGDegrees& r1, const AGDegrees& r2 );
	AGDegrees& operator+=( const AGDegrees& d )
	{
		value += d.value;
		return *this; 
	}

	friend AGDegrees operator-( const AGDegrees& r1, const AGDegrees& r2 );
	AGDegrees& operator-=( const AGDegrees& d )
	{
		value -= d.value;
		return *this; 
	}

	float value; 
};

inline AGDegrees operator+( const AGDegrees& r1, const AGDegrees& r2 )
{
	return AGDegrees( r1.value + r2.value );
}

inline AGDegrees operator-( const AGDegrees& r1, const AGDegrees& r2 )
{
	return AGDegrees( r1.value - r2.value );
}

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

struct AGRadians
{
	explicit AGRadians( float radian ) : value( radian ){}
	AGRadians( const AGRadians& radians ) : value( radians.value ){}

	AGDegrees toDegrees();

	operator float() const
	{
		return value; 
	}

	AGRadians& operator=( const AGRadians& radians ){ value = radians.value; return *this; }
	bool operator==( const AGRadians& r ) { return AGMath::isEqual( value, r.value ); }
	bool operator==( float var ) { return AGMath::isEqual( value, var ); }

	friend AGRadians operator+( const AGRadians& r1, const AGRadians& r2 );
	AGRadians& operator+=( const AGRadians& r )
	{
		value += r.value;
		return *this; 
	}

	friend AGRadians operator-( const AGRadians& r1, const AGRadians& r2 );
	AGRadians& operator-=( const AGRadians& r )
	{
		value -= r.value;
		return *this; 
	}

	float value; 
};

inline AGRadians operator+( const AGRadians& r1, const AGRadians& r2 )
{
	return AGRadians( r1.value + r2.value );
}

inline AGRadians operator-( const AGRadians& r1, const AGRadians& r2 )
{
	return AGRadians( r1.value - r2.value );
}

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

struct AGEulerAngles 
{
	explicit AGEulerAngles( AGRadians inX = AGRadians( 0.0f ) , AGRadians inY = AGRadians( 0.0f ), AGRadians inZ = AGRadians( 0.0f ) ) : x( inX ), y( inY ), z( inZ ){}
	explicit AGEulerAngles( AGDegrees inX, AGDegrees inY, AGDegrees inZ ) : x( inX.toRadians() ), y( inY.toRadians() ), z( inZ.toRadians() ){}
	AGEulerAngles( const AGEulerAngles& copy ) : x( copy.x ), y( copy.y ), z( copy.z ){}

	AGEulerAngles& operator=( const AGEulerAngles& copy )
	{
		AGEulerAngles a( copy );
		*this = a; 
		return *this; 
	}
	bool operator==( const AGEulerAngles& a )
	{
		return AGMath::isEqual( x, a.x ) && AGMath::isEqual( y, a.y ) && AGMath::isEqual( z, a.z );
	}

	friend AGEulerAngles operator+( const AGEulerAngles& a1, const AGEulerAngles& a2 );
	AGEulerAngles& operator+=( const AGEulerAngles& a )
	{
		x += a.x; 
		y += a.y;
		z += a.z;

		return *this; 
	}

	friend AGEulerAngles operator-( const AGEulerAngles& a1, const AGEulerAngles& a2 );
	AGEulerAngles& operator-=( const AGEulerAngles& a );

	AGRadians x, y, z; 
};

AGEulerAngles operator+( const AGEulerAngles& a1, const AGEulerAngles& a2 )
{
	return AGEulerAngles( a1.x + a2.x, a1.y + a2.y, a1.z + a2.z );
}

AGEulerAngles operator-( const AGEulerAngles& a1, const AGEulerAngles& a2 )
{
	return AGEulerAngles( a1.x - a2.x, a1.y - a2.y, a1.z - a2.z );
}

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

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