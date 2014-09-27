#ifndef AG_RECT_H
#define AG_RECT_H

#include "AGSize.h"
#include "AGPoint.h"

class AGRect 
{
	public:
		AGRect(); 
		AGRect( float x, float y, float w, float h );
		AGRect( float x, float y, const AGSize& size ); 
		AGRect( const AGPoint& point, float w, float h );
		AGRect( const AGPoint& point, const AGSize& size );
		AGRect( const AGRect& copy );
		~AGRect();

		void setLeft( float left );
		float getLeft() const; 

		void setTop( float top );
		float getTop() const; 

		void setRight( float right );
		float getRight() const; 

		void setBottom( float bottom );
		float getBottom() const; 

		void setPoint( const AGPoint& point );
		const AGPoint& getPoint() const; 

		void setWidth( float width );
		float getWidth() const;

		void setHeight( float height );
		float getHeight() const; 

		void setSize( const AGSize& size );
		const AGSize& getSize() const; 

		void setRect( const AGRect& rect );

		bool operator==( const AGRect& var );
		AGRect& operator=( const AGRect& var );

		AGRect operator+( const AGSize& var );
		AGRect operator+( const AGRect& var );
		AGRect operator+( const AGPoint& var );
		
		AGRect& operator+=( const AGSize& var );
		AGRect& operator+=( const AGRect& var );
		AGRect& operator+=( const AGPoint& var );

		AGRect operator-( const AGRect& var );
		AGRect operator-( const AGSize& var );
		AGRect operator-( const AGPoint& var );
		AGRect& operator-=( const AGRect& var );
		AGRect& operator-=( const AGSize& var );
		AGRect& operator-=( const AGPoint& var );

		AGRect operator*( float var );
		AGRect& operator*=( float var );
		
		AGRect operator/( float var );
		AGRect& operator/=( float var );
	private:
		AGPoint m_point;
		AGSize m_size; 
};

#endif 