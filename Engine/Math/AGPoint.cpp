#include "AGPoint.h"

AGPoint::AGPoint()
{
	setX( 0 );
	setY( 0 );
}

AGPoint::AGPoint(float x, float y)
{
	setX( x );
	setY( y );
}

AGPoint::AGPoint(const AGPoint& copy)
{
	setX( copy.m_x );
	setY( copy.m_y );
}

AGPoint::~AGPoint()
{

}

void AGPoint::setX(float x)
{
	m_x = x; 
}

float AGPoint::getX() const
{
	return m_x;
}

void AGPoint::setY(float y)
{
	m_y = y; 
}

float AGPoint::getY() const
{
	return m_y; 
}

bool AGPoint::operator==(const AGPoint& var)
{
	return m_x == var.m_x && m_y == var.m_y; 
}

AGPoint& AGPoint::operator=(const AGPoint& var)
{
	setX( var.m_x );
	setY( var.m_y );
	return *this; 
}

AGPoint AGPoint::operator+(const AGPoint& var)
{
	AGPoint point( *this );
	point.setX( point.m_x + var.m_x );
	point.setY( point.m_y + var.m_y );
	return point; 
}

AGPoint& AGPoint::operator+=(const AGPoint& var)
{
	setX( m_x + var.m_x );
	setY( m_y + var.m_y );
	return *this; 
}

AGPoint AGPoint::operator-(const AGPoint& var)
{
	AGPoint point( *this );
	point.setX( point.m_x - var.m_x );
	point.setY( point.m_y - var.m_y );
	return point; 
}

AGPoint& AGPoint::operator-=(const AGPoint& var)
{
	setX( m_x - var.m_x );
	setY( m_y - var.m_y );
	return *this; 
}

AGPoint AGPoint::operator*(float var)
{
	AGPoint point( *this );
	point.m_x *= var;
	point.m_y *= var;
	return point; 
}

AGPoint& AGPoint::operator*=(float var)
{
	m_x *= var;
	m_y *= var;
	return *this; 
}

AGPoint AGPoint::operator/(float var)
{
	AGPoint point( *this );
	point.m_x /= var;
	point.m_y /= var;
	return point; 
}

AGPoint& AGPoint::operator/=(float var)
{
	m_x /= var;
	m_y /= var;
	return *this; 
}
