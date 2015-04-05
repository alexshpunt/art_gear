#include "AGPoint2.h"

AGPoint2::AGPoint2()
{
	x = y = 0; 
}

AGPoint2::AGPoint2(float inX, float inY )
{
	x = inX;
	y = inY;
}

AGPoint2::AGPoint2(const AGPoint2& copy)
{
	x = copy.x;
	y = copy.y;
}

AGPoint2::~AGPoint2()
{

}

bool AGPoint2::operator==(const AGPoint2& var)
{
	return x == var.x && y == var.y; 
}

AGPoint2& AGPoint2::operator=(const AGPoint2& var)
{
	x = var.x;
	y = var.y; 
	return *this; 
}

AGPoint2 AGPoint2::operator+(const AGPoint2& var)
{
	AGPoint2 point( *this );
	point.x += var.x;
	point.y += var.y;
	return point; 
}

AGPoint2& AGPoint2::operator+=(const AGPoint2& var)
{
	x += var.x;
	y += var.y;
	return *this; 
}

AGPoint2 AGPoint2::operator-(const AGPoint2& var)
{
	AGPoint2 point( *this );
	point.x -= var.x;
	point.y -= var.y;
	return point; 
}

AGPoint2& AGPoint2::operator-=(const AGPoint2& var)
{
	x -= var.x;
	y -= var.y;
	return *this; 
}

AGPoint2 AGPoint2::operator*(float var)
{
	AGPoint2 point( *this );
	point.x *= var;
	point.y *= var;
	return point; 
}

AGPoint2& AGPoint2::operator*=(float var)
{
	x *= var;
	y *= var;
	return *this; 
}

AGPoint2 AGPoint2::operator/(float var)
{
	AGPoint2 point( *this );
	point.x /= var;
	point.y /= var;
	return point; 
}

AGPoint2& AGPoint2::operator/=(float var)
{
	x /= var;
	y /= var;
	return *this; 
}


