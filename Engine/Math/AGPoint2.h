#ifndef AG_POINT2_H
#define AG_POINT2_H

class AGPoint2 
{
	public:
		AGPoint2();
		AGPoint2( float x, float y );
		AGPoint2( const AGPoint2& copy );
		~AGPoint2();

		float x;
		float y;

		bool operator==( const AGPoint2& var );
		AGPoint2& operator=( const AGPoint2& var );

		AGPoint2 operator+( const AGPoint2& var );
		AGPoint2& operator+=( const AGPoint2& var );

		AGPoint2 operator-( const AGPoint2& var );
		AGPoint2& operator-=( const AGPoint2& var );

		AGPoint2 operator*( float var );
		AGPoint2& operator*=( float var );
		
		AGPoint2 operator/( float var );
		AGPoint2& operator/=( float var );
};

#endif 