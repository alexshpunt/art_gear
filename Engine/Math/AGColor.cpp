#include "AGColor.h"

#include "AGMath.h"

///////////////////////////////////////////////////////////////////////////
///Class that helps to transform INT color representation to normalized 
///FLOAT representation, and also store data of 2 types( int and float )
///////////////////////////////////////////////////////////////////////////
class AGColorPrivate 
{
	///////////////////////////////////////////////////////////////////////////
	///*i - integer value ; *f - floatValue
	///////////////////////////////////////////////////////////////////////////
	public:
		void setRF( float r )
		{
			rf = r; 
			ri = r * 255; 
		}
		
		void setGF( float g )
		{
			gf = g;
			gi = g * 255;
		}

		void setBF( float b )
		{
			bf = b;
			bi = b * 255; 
		}

		void setAF( float a )
		{
			af = a;
			af = a * 255; 
		}

		void setFloat( float r, float g, float b, float a )
		{
			setRF( r );
			setGF( g );
			setBF( b );
			setAF( a ); 
		}

		void setRI( int r )
		{
			ri = r;
			rf = r / 255.0f; 
		}

		void setGI( int g )
		{
			gi = g;
			gf = g / 255.0f; 
		}

		void setBI( int b )
		{
			bi = b;
			bf = b / 255.0f; 
		}

		void setAI( int a )
		{
			ai = a;
			af = a / 255.0f; 
		}

		void setInt( int r, int g, int b, int a )
		{
			setRI( r );
			setGI( g );
			setBI( b );
			setAI( a );
		}

		int ri, gi, bi, ai;
		float rf, gf, bf, af; 
};

AGColor::AGColor()
{
	m_p = new AGColorPrivate; 
	m_p->setInt( 255, 255, 255, 255 );
}

AGColor::AGColor(const AGColor& color)
{
	m_p = new AGColorPrivate; 
	m_p->setInt( color.m_p->ri, color.m_p->gi, color.m_p->bi, color.m_p->ai );
}

///////////////////////////////////////////////////////////////////////////
///Int constructers 
///////////////////////////////////////////////////////////////////////////

AGColor::AGColor(int color)
{
	m_p = new AGColorPrivate; 
	m_p->setInt( color, color, color, 255 ); 
}

AGColor::AGColor(int r, int g, int b)
{
	m_p = new AGColorPrivate; 
	m_p->setInt( r, g, b, 255 );
}

AGColor::AGColor(int r, int g, int b, int a)
{
	m_p = new AGColorPrivate; 
	m_p->setInt( r, g, b, a );
}

///////////////////////////////////////////////////////////////////////////
///Float constructers
///////////////////////////////////////////////////////////////////////////

AGColor::AGColor(float color)
{
	m_p = new AGColorPrivate; 
	m_p->setFloat( color, color, color, 1.0f );
}

AGColor::AGColor(float r, float g, float b )
{
	m_p = new AGColorPrivate; 
	m_p->setFloat( r, g, b, 1.0f );
}

AGColor::AGColor(float r, float g, float b, float a)
{
	m_p = new AGColorPrivate; 
	m_p->setFloat( r, g, b, a );
}

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

AGColor::~AGColor()
{
	delete m_p;
}

///////////////////////////////////////////////////////////////////////////
///Color set
///////////////////////////////////////////////////////////////////////////

void AGColor::setRed(int r)
{
	m_p->setRI( r );
}

void AGColor::setRed(float r)
{
	m_p->setRF( r );
}

void AGColor::setGreen(int g)
{
	m_p->setGI( g );
}

void AGColor::setGreen(float g)
{
	m_p->setGF( g );
}

void AGColor::setBlue(int b)
{
	m_p->setBI( b );
}

void AGColor::setBlue(float b)
{
	m_p->setBF( b );
}

void AGColor::setAlpha(int a)
{
	m_p->setAI( a );
}

void AGColor::setAlpha(float a)
{
	m_p->setAF( a );
}

void AGColor::setColor(int r, int g, int b)
{
	m_p->setInt( r, g, b, 255 );
}

void AGColor::setColor(int r, int b, int g, int a)
{
	m_p->setInt( r, g, b, a );
}

void AGColor::setColor(float r, float g, float b)
{
	m_p->setFloat( r, g, b, 1.0f );
}

void AGColor::setColor(float r, float b, float g, float a)
{
	m_p->setFloat( r, g, b, a );
}

///////////////////////////////////////////////////////////////////////////
///Color get
///////////////////////////////////////////////////////////////////////////

float AGColor::getRedF() const
{
	return m_p->rf; 
}

float AGColor::getGreenF() const
{
	return m_p->gf; 
}

float AGColor::getBlueF() const
{
	return m_p->bf; 
}

float AGColor::getAlphaF() const
{
	return m_p->af; 
}

int AGColor::getRed() const
{
	return m_p->ri; 
}

int AGColor::getGreen() const
{
	return m_p->gi;
}

int AGColor::getBlue() const
{
	return m_p->bi;
}

int AGColor::getAlpha() const
{
	return m_p->ai;
}

AGColor& AGColor::operator=(AGColor color)
{
	m_p->setInt( color.m_p->ri, color.m_p->gi, color.m_p->bi, color.m_p->ai );
	return *this; 
}


