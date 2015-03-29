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
		AGColorPrivate()
		{
			rf = gf = bf = af = 0.0f;
			ri = gi = bi = ai = 0; 
		}
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
			ai = a * 255; 
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
	p = new AGColorPrivate; 
	p->setInt( 255, 255, 255, 255 );
}

AGColor::AGColor(const AGColor& color)
{
	p = new AGColorPrivate; 
	if( color.p )
		p->setInt( color.p->ri, color.p->gi, color.p->bi, color.p->ai );
}

///////////////////////////////////////////////////////////////////////////
///Int constructers 
///////////////////////////////////////////////////////////////////////////

AGColor::AGColor(int color)
{
	p = new AGColorPrivate; 
	p->setInt( color, color, color, 255 ); 
}

AGColor::AGColor(int r, int g, int b)
{
	p = new AGColorPrivate; 
	p->setInt( r, g, b, 255 );
}

AGColor::AGColor(int r, int g, int b, int a)
{
	p = new AGColorPrivate; 
	p->setInt( r, g, b, a );
}

///////////////////////////////////////////////////////////////////////////
///Float constructers
///////////////////////////////////////////////////////////////////////////

AGColor::AGColor(float color)
{
	p = new AGColorPrivate; 
	p->setFloat( color, color, color, 1.0f );
}

AGColor::AGColor(float r, float g, float b )
{
	p = new AGColorPrivate; 
	p->setFloat( r, g, b, 1.0f );
}

AGColor::AGColor(float r, float g, float b, float a)
{
	p = new AGColorPrivate; 
	p->setFloat( r, g, b, a );
}

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

AGColor::~AGColor()
{
	delete p;
}

///////////////////////////////////////////////////////////////////////////
///Color set
///////////////////////////////////////////////////////////////////////////

void AGColor::setRed(int r)
{
	p->setRI( r );
}

void AGColor::setRed(float r)
{
	p->setRF( r );
}

void AGColor::setGreen(int g)
{
	p->setGI( g );
}

void AGColor::setGreen(float g)
{
	p->setGF( g );
}

void AGColor::setBlue(int b)
{
	p->setBI( b );
}

void AGColor::setBlue(float b)
{
	p->setBF( b );
}

void AGColor::setAlpha(int a)
{
	p->setAI( a );
}

void AGColor::setAlpha(float a)
{
	p->setAF( a );
}

void AGColor::setColor(int r, int g, int b)
{
	p->setInt( r, g, b, 255 );
}

void AGColor::setColor(int r, int b, int g, int a)
{
	p->setInt( r, g, b, a );
}

void AGColor::setColor(float r, float g, float b)
{
	p->setFloat( r, g, b, 1.0f );
}

void AGColor::setColor(float r, float b, float g, float a)
{
	p->setFloat( r, g, b, a );
}

///////////////////////////////////////////////////////////////////////////
///Color get
///////////////////////////////////////////////////////////////////////////

float AGColor::getRedF() const
{
	return p->rf; 
}

float AGColor::getGreenF() const
{
	return p->gf; 
}

float AGColor::getBlueF() const
{
	return p->bf; 
}

float AGColor::getAlphaF() const
{
	return p->af; 
}

int AGColor::getRed() const
{
	return p->ri; 
}

int AGColor::getGreen() const
{
	return p->gi;
}

int AGColor::getBlue() const
{
	return p->bi;
}

int AGColor::getAlpha() const
{
	return p->ai;
}

AGColor& AGColor::operator=(AGColor color)
{
	p = new AGColorPrivate; 
	p->setInt( color.p->ri, color.p->gi, color.p->bi, color.p->ai );
	return *this; 
}

/*AGColor::operator float*() const
{
	float color[] = { p->rf, p->gf, p->bf, p->af };
	return color; 
}*/