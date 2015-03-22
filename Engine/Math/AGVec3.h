#ifndef AG_VEC3_H
#define AG_VEC3_H

class AGVec3 
{
	public:
		AGVec3();
		AGVec3( float x, float y, float z );
		AGVec3( const AGVec3& copy );

		float x;
		float y;
		float z; 

		void normilize(); 
		float getLength() const;
		float getSqrLength() const;

		static float dot( const AGVec3& v1, const AGVec3& v2 );
		static AGVec3 cross( const AGVec3& v1, const AGVec3& v2 );

		static AGVec3 getUp();
		static AGVec3 getRight();
		static AGVec3 getForward(); 

		bool operator==( const AGVec3& var );
		AGVec3& operator=( const AGVec3& var );

		AGVec3 operator+( const AGVec3& var );
		AGVec3& operator+=( const AGVec3& var );

		friend AGVec3 operator-( const AGVec3& v1, const AGVec3& v2 );
		AGVec3 operator-( const AGVec3& var );
		AGVec3& operator-=( const AGVec3& var );

		AGVec3 operator*( float var );
		AGVec3& operator*=( float var );

		AGVec3 operator/( float var );
		AGVec3& operator/=( float var );

		operator float*() const; 
};

#endif 