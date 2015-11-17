#include "AGSize.h"

AGSize::AGSize()
{
	setWidth( 0 );
	setHeight( 0 );
}

AGSize::AGSize(int w, int h)
{
	setWidth( w );
	setHeight( h );
}

AGSize::AGSize(const AGSize& copy)
{
	setSize( copy );
}

AGSize::~AGSize()
{

}

void AGSize::setSize(int w, int h)
{
	setWidth( w );
	setHeight( h );
}

void AGSize::setSize(const AGSize& size)
{
	setWidth( size.m_width );
	setHeight( size.m_height );
}

void AGSize::setWidth(int w)
{
	if( w >= 0 )
		m_width = w;
}

int AGSize::getWidth() const
{
	return m_width; 
}

void AGSize::setHeight(int h)
{
	if( h >= 0 )
		m_height = h; 
}

int AGSize::getHeight() const
{
	return m_height; 
}

bool AGSize::operator==(const AGSize& var)
{
	return m_height == var.m_height && m_width == var.m_width; 
}

AGSize& AGSize::operator=(const AGSize& var)
{
	setSize( var );
	return *this; 
}

AGSize AGSize::operator+(const AGSize& var)
{
	AGSize size( *this );
	size.setWidth( size.m_width + var.m_width );
	size.setHeight( size.m_height + var.m_height );
	return size; 
}

AGSize& AGSize::operator+=(const AGSize& var)
{
	setWidth( m_width + var.m_width );
	setHeight( m_height + var.m_height );
	return *this; 
}

AGSize AGSize::operator-(const AGSize& var)
{
	AGSize size( *this );
	size.setWidth( size.m_width - var.m_width );
	size.setHeight( size.m_height - var.m_height );
	return size; 
}

AGSize& AGSize::operator-=(const AGSize& var)
{
	setWidth( m_width - var.m_width );
	setHeight( m_height - var.m_height );
	return *this; 
}

AGSize AGSize::operator*(int var)
{
	AGSize size( *this );
	size.setWidth( size.m_width * var );
	size.setHeight( size.m_height * var );
	return size; 
}

AGSize AGSize::operator*=(int var)
{
	setWidth( m_width * var );
	setHeight( m_height * var );
	return *this; 
}

AGSize AGSize::operator/(int var)
{
	AGSize size( *this );
	size.setWidth( size.m_width / var );
	size.setHeight( size.m_height / var );
	return size; 
}

AGSize AGSize::operator/=(int var)
{
	setWidth( m_width / var );
	setHeight( m_height / var );
	return *this; 
}

