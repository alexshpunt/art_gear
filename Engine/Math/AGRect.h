#ifndef AG_RECT_H
#define AG_RECT_H

#include "AGSize.h"
#include "AGPoint2.h"

class AGRect 
{
	public:
		AGRect(); 
		AGRect( float left, float top, float right, float bottom );
		//AGRect( float x, float y, float w, float h );
		AGRect( float x, float y, const AGSize& size ); 
		AGRect( const AGPoint2& point, float w, float h );
		AGRect( const AGPoint2& point, const AGSize& size );
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

		void setPoint( const AGPoint2& point );
		const AGPoint2& getPoint() const; 

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
		AGRect operator+( const AGPoint2& var );
		
		AGRect& operator+=( const AGSize& var );
		AGRect& operator+=( const AGRect& var );
		AGRect& operator+=( const AGPoint2& var );

		AGRect operator-( const AGRect& var );
		AGRect operator-( const AGSize& var );
		AGRect operator-( const AGPoint2& var );
		AGRect& operator-=( const AGRect& var );
		AGRect& operator-=( const AGSize& var );
		AGRect& operator-=( const AGPoint2& var );

		AGRect operator*( float var );
		AGRect& operator*=( float var );
		
		AGRect operator/( float var );
		AGRect& operator/=( float var );
	private:
		AGPoint2 m_point;
		AGSize m_size; 
};

#endif 