#ifndef AG_POINT3_H
#define AG_POINT3_H

class AGPoint3 
{
	public:
		AGPoint3();
		AGPoint3( float x, float y, float z );
		AGPoint3( const AGPoint3& copy );
		~AGPoint3();

		float x;
		float y;
		float z;

		bool operator==( const AGPoint3& var );
		AGPoint3& operator=( const AGPoint3& var );

		AGPoint3 operator+( const AGPoint3& var );
		AGPoint3& operator+=( const AGPoint3& var );

		AGPoint3 operator-( const AGPoint3& var );
		AGPoint3& operator-=( const AGPoint3& var );

		AGPoint3 operator*( float var );
		AGPoint3& operator*=( float var );
		
		AGPoint3 operator/( float var );
		AGPoint3& operator/=( float var );
};

#endif 