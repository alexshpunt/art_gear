#include "AGVec3.h"

#include <math.h>

AGVec3::AGVec3()
{
	x = y = z = 0.0f; 
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

void AGVec3::normilize()
{
	float len = getLength();
	x /= len;
	y /= len;
	z /= len; 
}

float AGVec3::getLength() const
{
	return sqrt( x*x + y*y + z*z ); 
}

float AGVec3::getSqrLength() const
{
	return x*x + y*y + z*z; 
}

AGVec3 AGVec3::getUp()
{
	return AGVec3( 0.0f, 1.0f, 0.0f );
}

AGVec3 AGVec3::getRight()
{
	return AGVec3( 1.0f, 0.0f, 0.0f );
}

AGVec3 AGVec3::getForward()
{
	return AGVec3( 0.0f, 0.0f, 1.0f );
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

AGVec3 AGVec3::operator+(const AGVec3& var)
{
	AGVec3 vec3( *this );
	vec3.x += var.x;
	vec3.y += var.y;
	vec3.z += var.z; 
	return vec3; 
}

AGVec3& AGVec3::operator+=(const AGVec3& var)
{
	x += var.x;
	y += var.y;
	z += var.z;
	return *this; 
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

AGVec3 AGVec3::operator*(const AGVec3& var)
{
	AGVec3 vec3( *this );
	vec3.x = vec3.y*var.z - var.y*vec3.z; 
	vec3.y = vec3.x*var.z - var.x*vec3.z; 
	vec3.z = vec3.x*var.y - var.x*vec3.y;
	return vec3; 
}

AGVec3 AGVec3::operator*(float var)
{
	AGVec3 vec3( *this );
	vec3.x *= var;
	vec3.y *= var;
	vec3.z *= var; 
	return vec3; 
}

AGVec3 AGVec3::operator*=(const AGVec3& var)
{
	x = y*var.z - var.y*z; 
	y = x*var.z - var.x*z; 
	z = x*var.y - var.x*y;
	return *this; 
}

AGVec3& AGVec3::operator*=(float var)
{
	x *= var;
	y *= var;
	z *= var; 
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

