#ifndef AG_VEC3_H
#define AG_VEC3_H

#include "Engine/Managers/AGLogger.h"

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
		friend AGVec3 operator*( const AGVec3& v1, float v2 );
		//AGVec3 operator*( float var );
		AGVec3& operator*=( float var );

		AGVec3 operator/( float var );
		AGVec3& operator/=( float var );

		friend AGLogger& operator<<( AGLogger& logger, const AGVec3& vec );

		operator float*() const; 
};

inline AGVec3 operator*( const AGVec3& v1, float v2 )
{
	return AGVec3( v1.x * v2, v1.y * v2, v1.z * v2 );
}

#endif 