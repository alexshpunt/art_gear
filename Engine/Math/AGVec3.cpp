#include "AGVec3.h"

#include <d3d10.h>
#include <d3dx10.h>

#include <math.h>

#include "AGMath.h"

AGVec3::AGVec3()
{
	x = y = z = 0.0f; 
}

AGVec3::AGVec3(float value)
{
	x = y = z = value; 
}


AGVec3::AGVec3( float inX, float inY, float inZ )
{
	x = inX;
	y = inY;
	z = inZ; 
}

AGVec3::AGVec3(const AGVec3& copy)
{
	x = copy.x;
	y = copy.y;
	z = copy.z; 
}

AGVec3::AGVec3(const AGVec2& vec2)
{
	x = vec2.x;
	y = vec2.y;
	z = 0.0f; 
}

void AGVec3::normilize()
{
	float len = getLength();
	if( len > 0.0f )
	{
		x /= len;
		y /= len;
		z /= len; 	
	}
}

AGVec3 AGVec3::normilized()
{
	AGVec3 vec( *this ); 
	vec.normilize();
	return vec; 
}

float AGVec3::getLength() const
{
	return sqrt( x*x + y*y + z*z ); 
}

float AGVec3::getSqrLength() const
{
	return x*x + y*y + z*z; 
}

AGVec3 AGVec3::Up()
{
	return AGVec3( 0.0f, 1.0f, 0.0f );
}

AGVec3 AGVec3::Right()
{
	return AGVec3( 1.0f, 0.0f, 0.0f );
}

AGVec3 AGVec3::Forward()
{
	return AGVec3( 0.0f, 0.0f, 1.0f );
}

AGVec3 AGVec3::Zero()
{
	return AGVec3( 0.0f );
}

bool AGVec3::operator==(const AGVec3& var)
{
	return x == var.x && y == var.y && z == var.z;
}

AGVec3& AGVec3::operator=(const AGVec3& var)
{
	x = var.x;
	y = var.y;
	z = var.z;
	return *this; 
}

AGVec3 AGVec3::operator+() const
{
	return AGVec3( x, y, z );
}

AGVec3 operator+( const AGVec3& v1, const AGVec3& v2 )
{
	return AGVec3( v1.x + v2.x, v1.y + v2.y, v1.z + v2.z );
}

AGVec3& AGVec3::operator+=(const AGVec3& var)
{
	x += var.x;
	y += var.y;
	z += var.z;
	return *this; 
}

AGVec3 AGVec3::operator-() const
{
	return AGVec3( -x, -y, -z );
}

AGVec3 operator-( const AGVec3& v1, const AGVec3& v2 )
{
	return AGVec3( v1.x - v2.x, v1.y - v2.y, v1.z - v2.z );
}

AGVec3 AGVec3::operator-(const AGVec3& var)
{
	AGVec3 vec3( *this );
	vec3.x -= var.x;
	vec3.y -= var.y;
	vec3.z -= var.z; 
	return vec3; 
}

AGVec3& AGVec3::operator-=(const AGVec3& var)
{
	x -= var.x;
	y -= var.y;
	z -= var.z;
	return *this; 
}

AGVec3 AGVec3::operator*(float var)
{
	AGVec3 vec3( *this );
	vec3.x *= var;
	vec3.y *= var;
	vec3.z *= var; 
	return vec3; 
}

AGVec3& AGVec3::operator*=(float var)
{
	x *= var;
	y *= var;
	z *= var; 
	return *this; 
}

AGVec3& AGVec3::operator*=(const AGMatrix& m)
{
	AGVec3 v( *this );

	*this = v * m; 

	return *this;
}

AGVec3 AGVec3::operator/(float var)
{
	AGVec3 vec3( *this );
	vec3.x /= var;
	vec3.y /= var;
	vec3.z /= var; 
	return vec3; 
}

AGVec3& AGVec3::operator/=(float var)
{
	x /= var;
	y /= var;
	z /= var; 
	return *this; 
}

float AGVec3::dot(const AGVec3& v1, const AGVec3& v2)
{
	return (v1.x*v2.x + v1.y*v2.y + v1.z*v2.z );
}

AGVec3 AGVec3::cross(const AGVec3& v1, const AGVec3& v2)
{
	AGVec3 vec3;
	/*
	 |  i   j   k  |
	 | v1x v1y v1z |
	 | v2x v2y v2z |
	*/
	vec3.x = v1.y*v2.z - v1.z*v2.y; 
	vec3.y = v1.z*v2.x - v1.x*v2.z; 
	vec3.z = v1.x*v2.y - v1.y*v2.x;
	return vec3; 
}

AGVec3::operator float*() const
{
	return (float*)this; 
}

AGVec3 AGVec3::operator-()
{
	return AGVec3( -x, -y, -z );
}

AGVec3 AGVec3::unproject( const AGVec3& vec, const AGRect& viewport, const AGMatrix& world, const AGMatrix& view, const AGMatrix& proj )
{
	AGMatrix invMat = ( world * view * proj  ).inversed(); 

	AGVec3 tmp;
	tmp.x = 2.0f * ( vec.x - viewport.getLeft() ) / viewport.getWidth() - 1.0f; 
	tmp.y = 2.0f * ( vec.y - viewport.getTop() ) / viewport.getHeight() - 1.0f;
	tmp.z = 2.0f * vec.z - 1.0f; 

	tmp.y = -tmp.y; 

	tmp *= invMat; 

	return tmp; 
}

AGLogger& operator<<( AGLogger& logger, const AGVec3& vec )
{
	AGDebug() << "AGVec3( " << vec.x << ", " << vec.y << ", " << vec.z << " )"; 
	return AGLogger::getInstance(); 
}


