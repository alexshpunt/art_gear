#include "AGColor.h"

#include "AGMath.h"

enum Colors{ R, G, B, A };

float clrToFloat( int clr )
{
	return clr / 255.0f; 
}

int clrToInt( float clr )
{
	return clr * 255.0f; 
}

AGColor::AGColor()
{
	m_r = m_g = m_b = m_a = 0.0f; 
}

AGColor::AGColor(const AGColor& color)
{	
	m_r = color.m_r;
	m_g = color.m_g;
	m_b = color.m_b;
	m_a = color.m_a; 
}

///////////////////////////////////////////////////////////////////////////
///Int constructers 
///////////////////////////////////////////////////////////////////////////

AGColor::AGColor(int color)
{
	m_r = AGMath::clamp( clrToFloat( color ), 0.0f, 1.0f );
	m_g = AGMath::clamp( clrToFloat( color ), 0.0f, 1.0f );
	m_b = AGMath::clamp( clrToFloat( color ), 0.0f, 1.0f );
	m_a = 1.0f; 
}

AGColor::AGColor(int r, int g, int b)
{
	m_r = AGMath::clamp( clrToFloat( r ), 0.0f, 1.0f );
	m_g = AGMath::clamp( clrToFloat( g ), 0.0f, 1.0f );
	m_b = AGMath::clamp( clrToFloat( b ), 0.0f, 1.0f );
	m_a = 1.0f; 
}

AGColor::AGColor(int r, int g, int b, int a)
{
	m_r = AGMath::clamp( clrToFloat( r ), 0.0f, 1.0f );
	m_g = AGMath::clamp( clrToFloat( g ), 0.0f, 1.0f );
	m_b = AGMath::clamp( clrToFloat( b ), 0.0f, 1.0f );
	m_a = AGMath::clamp( clrToFloat( a ), 0.0f, 1.0f ); 

}

///////////////////////////////////////////////////////////////////////////
///Float constructers
///////////////////////////////////////////////////////////////////////////

AGColor::AGColor(float color)
{
	m_r = AGMath::clamp( color, 0.0f, 1.0f );
	m_g = AGMath::clamp( color, 0.0f, 1.0f );
	m_b = AGMath::clamp( color, 0.0f, 1.0f ); 
	m_a = 1.0f; 
}

AGColor::AGColor(float r, float g, float b )
{
	m_r = AGMath::clamp( r, 0.0f, 1.0f );
	m_g = AGMath::clamp( g, 0.0f, 1.0f );
	m_b = AGMath::clamp( b, 0.0f, 1.0f ); 
	m_a = 1.0f;  
}

AGColor::AGColor(float r, float g, float b, float a)
{
	m_r = AGMath::clamp( r, 0.0f, 1.0f );
	m_g = AGMath::clamp( g, 0.0f, 1.0f );
	m_b = AGMath::clamp( b, 0.0f, 1.0f ); 
	m_a = AGMath::clamp( a, 0.0f, 1.0f );  
}

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

AGColor::~AGColor()
{

}

///////////////////////////////////////////////////////////////////////////
///Color set
///////////////////////////////////////////////////////////////////////////

void AGColor::setRed(int r)
{
	m_r = AGMath::clamp( clrToFloat( r ), 0.0f, 1.0f );
}

void AGColor::setRed(float r)
{
	m_r = AGMath::clamp( r, 0.0f, 1.0f );
}

void AGColor::setGreen(int g)
{
	m_r = AGMath::clamp( clrToFloat( g ), 0.0f, 1.0f );
}

void AGColor::setGreen(float g)
{
	m_r = AGMath::clamp( g, 0.0f, 1.0f );
}

void AGColor::setBlue(int b)
{
	m_r = AGMath::clamp( clrToFloat( b ), 0.0f, 1.0f );
}

void AGColor::setBlue(float b)
{
	m_r = AGMath::clamp( b, 0.0f, 1.0f );
}

void AGColor::setAlpha(int a)
{
	m_r = AGMath::clamp( clrToFloat( a ), 0.0f, 1.0f );
}

void AGColor::setAlpha(float a)
{
	m_r = AGMath::clamp( a, 0.0f, 1.0f );
}

void AGColor::setColor(int r, int g, int b)
{
	m_r = AGMath::clamp( clrToFloat( r ), 0.0f, 1.0f ); 
	m_g = AGMath::clamp( clrToFloat( g ), 0.0f, 1.0f ); 
	m_b = AGMath::clamp( clrToFloat( b ), 0.0f, 1.0f ); 
	m_a = 1.0f;
}

void AGColor::setColor(int r, int b, int g, int a)
{
	m_r = AGMath::clamp( clrToFloat( r ), 0.0f, 1.0f ); 
	m_g = AGMath::clamp( clrToFloat( g ), 0.0f, 1.0f ); 
	m_b = AGMath::clamp( clrToFloat( b ), 0.0f, 1.0f ); 
	m_a = AGMath::clamp( clrToFloat( a ), 0.0f, 1.0f );
}

void AGColor::setColor(float r, float g, float b)
{
	m_r = AGMath::clamp( r, 0.0f, 1.0f ); 
	m_g = AGMath::clamp( g, 0.0f, 1.0f ); 
	m_b = AGMath::clamp( b, 0.0f, 1.0f ); 
	m_a = 1.0f;
}

void AGColor::setColor(float r, float b, float g, float a)
{
	m_r = AGMath::clamp( r, 0.0f, 1.0f ); 
	m_g = AGMath::clamp( g, 0.0f, 1.0f ); 
	m_b = AGMath::clamp( b, 0.0f, 1.0f ); 
	m_a = AGMath::clamp( a, 0.0f, 1.0f );
}

///////////////////////////////////////////////////////////////////////////
///Color get
///////////////////////////////////////////////////////////////////////////

float AGColor::getRedF() const
{
	return m_r; 
}

float AGColor::getGreenF() const
{
	return m_g; 
}

float AGColor::getBlueF() const
{
	return m_b;
}

float AGColor::getAlphaF() const
{
	return m_a;
}

int AGColor::getRed() const
{
	return clrToInt( m_r );
}

int AGColor::getGreen() const
{
	return clrToInt( m_g );
}

int AGColor::getBlue() const
{
	return clrToInt( m_b );
}

int AGColor::getAlpha() const
{
	return clrToInt( m_a );;
}

AGColor& AGColor::operator=(AGColor color)
{
	m_r = color.m_r;
	m_g = color.m_g;
	m_b = color.m_b;
	m_a = color.m_a; 
	return *this; 
}

AGColor::operator float*() const
{
	return (float*)this; 
}