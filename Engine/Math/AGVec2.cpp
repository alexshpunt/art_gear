#include "AGVec2.h"

#include <math.h>

AGVec2::AGVec2()
{
	x = y = 0.0f;
}

AGVec2::AGVec2( float inX, float inY )
{
	x = inX;
	y = inY; 
}

AGVec2::AGVec2(const AGVec2& copy)
{
	x = copy.x;
	y = copy.y; 
}

AGVec2::~AGVec2()
{

}

void AGVec2::normalize()
{
	float len = getLength();
	x /= len;
	y /= len; 
}

float AGVec2::getLength()
{
	return sqrt( x*x + y*y );
}

float AGVec2::getSqrLength()
{
	return x*x + y*y;
}

AGVec2 AGVec2::getUp()
{
	return AGVec2( 0.0f, 1.0f );
}

AGVec2 AGVec2::getRight()
{
	return AGVec2( 1.0f, 0.0f );
}

bool AGVec2::operator==(const AGVec2& var)
{
	 return x == var.x && y == var.y; 
}

AGVec2& AGVec2::operator=(const AGVec2& var)
{
	x = var.x;
	y = var.y;
	return *this; 
}

AGVec2 AGVec2::operator+(const AGVec2& var)
{
	AGVec2 vec2( *this );
	vec2.x += var.x;
	vec2.y += var.y; 
	return vec2; 
}

AGVec2& AGVec2::operator+=(const AGVec2& var)
{
	x += var.x;
	y += var.y;
	return *this;
}

AGVec2 AGVec2::operator-(const AGVec2& var)
{
	AGVec2 vec2( *this );
	vec2.x -= var.x;
	vec2.y -= var.y; 
	return vec2;
}

AGVec2& AGVec2::operator-=(const AGVec2& var)
{
	x -= var.x;
	y -= var.y;
	return *this;
}

float AGVec2::operator*(const AGVec2& var)
{
	return x*var.x + y*var.y;
}

AGVec2 AGVec2::operator*(float var)
{
	AGVec2 vec2( *this );
	vec2.x *= var; 
	vec2.y *= var; 
	return vec2; 
}

AGVec2& AGVec2::operator*=(float var)
{
	x *= var;
	y *= var;
	return *this; 
}

AGVec2 AGVec2::operator/(float var)
{
	AGVec2 vec2( *this );
	vec2.x /= var; 
	vec2.y /= var; 
	return vec2;
}

AGVec2& AGVec2::operator/=(float var)
{
	x /= var;
	y /= var;
	return *this; 
}


