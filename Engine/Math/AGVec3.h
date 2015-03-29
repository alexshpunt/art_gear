#ifndef AG_VEC3_H
#define AG_VEC3_H

class AGMatrix; 
class AGRect; 
class AGVec2; 

class AGVec3 
{
	public:
		AGVec3();
		AGVec3( float value );
		AGVec3( float x, float y, float z );
		AGVec3( const AGVec2& vec2 );
		AGVec3( const AGVec3& copy );

		float x;
		float y;
		float z; 

		void normilize(); 
		AGVec3 normilized(); 
		float getLength() const;
		float getSqrLength() const;

		static float dot( const AGVec3& v1, const AGVec3& v2 );
		static AGVec3 cross( const AGVec3& v1, const AGVec3& v2 );
		static AGVec3 unproject( const AGVec3& vec, const AGRect& viewport, const AGMatrix& world, const AGMatrix& view, const AGMatrix& proj ); 

		static AGVec3 Up();
		static AGVec3 Right();
		static AGVec3 Forward(); 
		static AGVec3 Zero(); 

		bool operator==( const AGVec3& var );
		AGVec3& operator=( const AGVec3& var );

		AGVec3 operator+() const;
		friend AGVec3 operator+( const AGVec3& v1, const AGVec3& v2 );
		AGVec3& operator+=( const AGVec3& var );

		AGVec3 operator-() const;
		friend AGVec3 operator-( const AGVec3& v1, const AGVec3& v2 );
		AGVec3 operator-( const AGVec3& var );
		AGVec3 operator-(); 
		AGVec3& operator-=( const AGVec3& var );

		AGVec3& operator*=( const AGMatrix& m ); 
		AGVec3 operator*( float var );
		AGVec3& operator*=( float var );

		AGVec3 operator/( float var );
		AGVec3& operator/=( float var );


		operator float*() const; 
};

#endif 