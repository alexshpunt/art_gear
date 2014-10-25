#include "AGPoint3.h"

AGPoint3::AGPoint3()
{
	x = y = z = 0; 
}

AGPoint3::AGPoint3(float inX, float inY, float inZ )
{
	x = inX;
	y = inY;
	z = inZ; 
}

AGPoint3::AGPoint3(const AGPoint3& copy)
{
	x = copy.x;
	y = copy.y;
	z = copy.z; 
}

AGPoint3::~AGPoint3()
{

}

bool AGPoint3::operator==(const AGPoint3& var)
{
	return x == var.x && y == var.y && z == var.z; 
}

AGPoint3& AGPoint3::operator=(const AGPoint3& var)
{
	x = var.x;
	y = var.y; 
	z = var.z; 
	return *this; 
}

AGPoint3 AGPoint3::operator+(const AGPoint3& var)
{
	AGPoint3 point( *this );
	point.x += var.x;
	point.y += var.y;
	point.z += var.z; 
	return point; 
}

AGPoint3& AGPoint3::operator+=(const AGPoint3& var)
{
	x += var.x;
	y += var.y;
	z += var.z; 
	return *this; 
}

AGPoint3 AGPoint3::operator-(const AGPoint3& var)
{
	AGPoint3 point( *this );
	point.x -= var.x;
	point.y -= var.y;
	point.z -= var.z; 
	return point; 
}

AGPoint3& AGPoint3::operator-=(const AGPoint3& var)
{
	x -= var.x;
	y -= var.y;
	z -= var.z; 
	return *this; 
}

AGPoint3 AGPoint3::operator*(float var)
{
	AGPoint3 point( *this );
	point.x *= var;
	point.y *= var;
	point.z *= var; 
	return point; 
}

AGPoint3& AGPoint3::operator*=(float var)
{
	x *= var;
	y *= var;
	z *= var; 
	return *this; 
}

AGPoint3 AGPoint3::operator/(float var)
{
	AGPoint3 point( *this );
	point.x /= var;
	point.y /= var;
	point.z /= var; 
	return point; 
}

AGPoint3& AGPoint3::operator/=(float var)
{
	x /= var;
	y /= var;
	z /= var; 
	return *this; 
}
