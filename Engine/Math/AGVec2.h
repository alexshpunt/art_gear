#ifndef AG_VECTOR2_H
#define AG_VECTOR2_H

class AGVec2
{
	public:
		AGVec2();
		AGVec2( float x, float y );
		AGVec2( const AGVec2& copy );
		~AGVec2(); 

		float x;
		float y; 

		void normalize();

		float getLength(); 
		float getSqrLength();

		static AGVec2 getUp();
		static AGVec2 getRight(); 

		bool operator==( const AGVec2& var );
		AGVec2& operator=( const AGVec2& var );

		AGVec2 operator+( const AGVec2& var );
		AGVec2& operator+=( const AGVec2& var );

		AGVec2 operator-( const AGVec2& var );
		AGVec2& operator-=( const AGVec2& var );

		float operator*( const AGVec2& var );
		AGVec2 operator*( float var );
		AGVec2& operator*=( float var );

		AGVec2 operator/( float var );
		AGVec2& operator/=( float var );
};

#endif 