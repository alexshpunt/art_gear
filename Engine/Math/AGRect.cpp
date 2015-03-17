#include "AGRect.h"

AGRect::AGRect()
{
	setLeft( 0.0f );
	setRight( 0.0f );
	setTop( 0.0f );
	setBottom( 0.0f );
}

AGRect::AGRect(float left, float top, float right, float bottom)
{
	setLeft( left );
	setRight( right );
	setTop( top );
	setBottom( bottom );
}

/*AGRect::AGRect(float x, float y, float w, float h)
{
	setLeft( x );
	setRight( x + w );
	setTop( y );
	setBottom( y + h );
}*/

AGRect::AGRect(float x, float y, const AGSize& size)
{
	setLeft( x );
	setTop( y );
	setSize( size );
}

AGRect::AGRect(const AGPoint2& point, float w, float h)
{
	setPoint( point );
	setRight( point.x + w );
	setBottom( point.y + h );
}

AGRect::AGRect(const AGPoint2& point, const AGSize& size)
{
	setPoint( point );
	setSize( size );
}

AGRect::AGRect(const AGRect& copy)
{
	setRect( copy );
}

AGRect::~AGRect()
{

}

void AGRect::setLeft(float left)
{
	m_point.x = left;
}

float AGRect::getLeft() const
{
	return m_point.x; 
}

void AGRect::setTop(float top)
{
	m_point.y = top;
}

float AGRect::getTop() const
{
	return m_point.y; 
}

void AGRect::setRight(float right)
{
	setWidth( right - m_point.x );
}

float AGRect::getRight() const
{
	return m_point.x + m_size.getWidth();
}

void AGRect::setBottom(float bottom)
{
	setHeight( m_point.y + bottom );
}

float AGRect::getBottom() const
{
	return m_point.y + m_size.getHeight();
}

void AGRect::setPoint(const AGPoint2& point)
{
	m_point = point;
}

const AGPoint2& AGRect::getPoint() const
{
	return m_point; 
}

void AGRect::setWidth(float width)
{
	if( width >= 0.0f )
		m_size.setWidth( width );
}

float AGRect::getWidth() const
{
	return m_size.getWidth();
}

void AGRect::setHeight(float height)
{
	if( height >= 0.0f )
		m_size.setHeight( height );
}

float AGRect::getHeight() const
{
	return m_size.getHeight();
}

void AGRect::setSize(const AGSize& size)
{
	setWidth( size.getWidth() );
	setHeight( size.getHeight() );
}

const AGSize& AGRect::getSize() const
{
	return m_size; 
}

void AGRect::setRect(const AGRect& rect)
{
	m_point = rect.m_point;
	m_size = rect.m_size; 
}

bool AGRect::operator==(const AGRect& var)
{
	return m_point == var.m_point && m_size == var.m_size; 
}

AGRect& AGRect::operator=(const AGRect& var)
{
	setRect( var );
	return *this; 
}

AGRect AGRect::operator+(const AGRect& var)
{
	AGRect rect( *this );
	rect.m_point += var.m_point;
	rect.setSize( rect.m_size + var.m_size ); 
	return rect; 
}

AGRect AGRect::operator+(const AGSize& var)
{
	AGRect rect( *this );
	rect.setSize( rect.m_size + var );  
	return rect; 
}

AGRect AGRect::operator+(const AGPoint2& var)
{
	AGRect rect( *this );
	rect.m_point += var; 
	return rect; 
}

AGRect& AGRect::operator+=(const AGRect& var)
{
	m_point += var.m_point;
	setSize( m_size + var.m_size ); 
	return *this; 
}

AGRect& AGRect::operator+=(const AGSize& var)
{
	setSize( m_size + var ); 
	return *this; 
}

AGRect& AGRect::operator+=(const AGPoint2& var)
{
	m_point += var;
	return *this; 
}

AGRect AGRect::operator-(const AGRect& var)
{
	AGRect rect( *this );
	rect.m_point -= var.m_point;
	rect.setSize( rect.m_size - var.m_size ); 
	return rect; 
}

AGRect AGRect::operator-(const AGSize& var)
{
	AGRect rect( *this );
	rect.setSize( rect.m_size - var ); 
	return rect; 
}

AGRect AGRect::operator-(const AGPoint2& var)
{
	AGRect rect( *this );
	rect.m_point -= var; 
	return rect; 
}


AGRect& AGRect::operator-=(const AGRect& var)
{
	m_point -= var.m_point;
	setSize( m_size - var.m_size );
	return *this; 
}

AGRect& AGRect::operator-=(const AGSize& var)
{
	setSize( m_size - var );
	return *this; 
}

AGRect& AGRect::operator-=(const AGPoint2& var)
{
	m_point -= var;
	return *this; 
}

AGRect AGRect::operator*(float var)
{
	AGRect rect( *this );
	m_size *= var; 
	return rect;
}

AGRect& AGRect::operator*=(float var)
{
	m_size *= var;
	return *this; 
}

AGRect AGRect::operator/(float var)
{
	AGRect rect( *this );
	m_size /= var; 
	return rect;
}

AGRect& AGRect::operator/=(float var)
{
	m_size /= var;
	return *this; 
}





