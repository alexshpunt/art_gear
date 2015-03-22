#ifndef AG_MATRIX4X4_H
#define AG_MATRIX4X4_H

class AGMatrixPrivate; 

#include "AGVec3.h"
#include "AGVec4.h"

class AGMatrix 
{
	public:
		AGMatrix();
		AGMatrix( float e );
		AGMatrix( float* data );
		AGMatrix( const AGMatrix& copy );
		
		void copyFrom( const AGMatrix& copy );

		void setData( float* data );
		float* getData() const; 

		float& getElem( int i, int j ); 
		float getElem( int i, int j ) const; 

		float getDeterminant(); 
		void inverse(); 
		AGMatrix getInversed(); 

		void setIdentity(); 
		bool isIdentity(); 

		void setPerspectiveLH( float angle, float aspectRatio, float nearPlane, float farPlane ); 
		void setOrthoLH( float viewWidth, float viewHeight, float nearPlane, float farPlane );
		void setLookAtLH( const AGVec3& eye, const AGVec3& center, const AGVec3& up ); 

		void setRotateX( float angle );
		void setRotateY( float angle );
		void setRotateZ( float angle );
		void setRotate( float angle, const AGVec3& axis );
		void setRotate( float x, float y, float z );
		void setTranslate( const AGVec3& transl );
		void setScale( const AGVec3& scale ); 

		void operator=( const AGMatrix& mtx );

		AGMatrix& operator+=( const AGMatrix& mtx );
		AGMatrix& operator-=( const AGMatrix& mtx ); 
		AGMatrix& operator*=( float var );
		AGMatrix& operator*=( const AGMatrix& mtx ); 
		AGMatrix& operator/=( float var );

		operator float*(); 

		friend AGMatrix operator*( const AGMatrix& m1, const AGMatrix& m2 );
		friend AGVec3 operator*( const AGVec3& v, const AGMatrix& m ); 
		friend AGVec4 operator*( const AGVec4& v, const AGMatrix& m );
		friend AGMatrix operator-( const AGMatrix& m1, const AGMatrix& m2 );
		friend AGMatrix operator+( const AGMatrix& m1, const AGMatrix& m2 );
		friend AGMatrix operator*( const AGMatrix& m, float v ); 
		friend AGMatrix operator/( const AGMatrix& m, float v );

		float& operator()( int i, int j ); 
		float  operator()( int i, int j ) const; 
	private:	
		AGMatrixPrivate* p; 
};

inline AGMatrix operator*( const AGMatrix& m1, const AGMatrix& m2 )
{
	float e00 = m1( 0, 0 ) * m2( 0, 0 ) + m1( 0, 1 ) * m2( 1, 0 ) + m1( 0, 2 ) * m2( 2, 0 ) + m1( 0, 3 ) * m2( 3, 0 ); 
	float e01 = m1( 0, 0 ) * m2( 0, 1 ) + m1( 0, 1 ) * m2( 1, 1 ) + m1( 0, 2 ) * m2( 2, 1 ) + m1( 0, 3 ) * m2( 3, 1 ); 
	float e02 = m1( 0, 0 ) * m2( 0, 2 ) + m1( 0, 1 ) * m2( 1, 2 ) + m1( 0, 2 ) * m2( 2, 2 ) + m1( 0, 3 ) * m2( 3, 2 ); 
	float e03 = m1( 0, 0 ) * m2( 0, 3 ) + m1( 0, 1 ) * m2( 1, 3 ) + m1( 0, 2 ) * m2( 2, 3 ) + m1( 0, 3 ) * m2( 3, 3 ); 

	float e10 = m1( 1, 0 ) * m2( 0, 0 ) + m1( 1, 1 ) * m2( 1, 0 ) + m1( 1, 2 ) * m2( 2, 0 ) + m1( 1, 3 ) * m2( 3, 0 ); 
	float e11 = m1( 1, 0 ) * m2( 0, 1 ) + m1( 1, 1 ) * m2( 1, 1 ) + m1( 1, 2 ) * m2( 2, 1 ) + m1( 1, 3 ) * m2( 3, 1 ); 
	float e12 = m1( 1, 0 ) * m2( 0, 2 ) + m1( 1, 1 ) * m2( 1, 2 ) + m1( 1, 2 ) * m2( 2, 2 ) + m1( 1, 3 ) * m2( 3, 2 ); 
	float e13 = m1( 1, 0 ) * m2( 0, 3 ) + m1( 1, 1 ) * m2( 1, 3 ) + m1( 1, 2 ) * m2( 2, 3 ) + m1( 1, 3 ) * m2( 3, 3 ); 

	float e20 = m1( 2, 0 ) * m2( 0, 0 ) + m1( 2, 1 ) * m2( 1, 0 ) + m1( 2, 2 ) * m2( 2, 0 ) + m1( 2, 3 ) * m2( 3, 0 ); 
	float e21 = m1( 2, 0 ) * m2( 0, 1 ) + m1( 2, 1 ) * m2( 1, 1 ) + m1( 2, 2 ) * m2( 2, 1 ) + m1( 2, 3 ) * m2( 3, 1 ); 
	float e22 = m1( 2, 0 ) * m2( 0, 2 ) + m1( 2, 1 ) * m2( 1, 2 ) + m1( 2, 2 ) * m2( 2, 2 ) + m1( 2, 3 ) * m2( 3, 2 ); 
	float e23 = m1( 2, 0 ) * m2( 0, 3 ) + m1( 2, 1 ) * m2( 1, 3 ) + m1( 2, 2 ) * m2( 2, 3 ) + m1( 2, 3 ) * m2( 3, 3 ); 

	float e30 = m1( 3, 0 ) * m2( 0, 0 ) + m1( 3, 1 ) * m2( 1, 0 ) + m1( 3, 2 ) * m2( 2, 0 ) + m1( 3, 3 ) * m2( 3, 0 ); 
	float e31 = m1( 3, 0 ) * m2( 0, 1 ) + m1( 3, 1 ) * m2( 1, 1 ) + m1( 3, 2 ) * m2( 2, 1 ) + m1( 3, 3 ) * m2( 3, 1 ); 
	float e32 = m1( 3, 0 ) * m2( 0, 2 ) + m1( 3, 1 ) * m2( 1, 2 ) + m1( 3, 2 ) * m2( 2, 2 ) + m1( 3, 3 ) * m2( 3, 2 ); 
	float e33 = m1( 3, 0 ) * m2( 0, 3 ) + m1( 3, 1 ) * m2( 1, 3 ) + m1( 3, 2 ) * m2( 2, 3 ) + m1( 3, 3 ) * m2( 3, 3 ); 

	float data[] =
	{
		e00, e01, e02, e03,
		e10, e11, e12, e13,
		e20, e21, e22, e23,
		e30, e31, e32, e33
	};

	return AGMatrix( data );  
}

inline AGMatrix operator*( float v, const AGMatrix& m )
{
	float data[] = 
	{
		m( 0, 0 ) * v, m( 0, 1 ) * v, m( 0, 2 ) * v, m( 0, 3 ) * v,
		m( 1, 0 ) * v, m( 1, 1 ) * v, m( 1, 2 ) * v, m( 1, 3 ) * v,
		m( 2, 0 ) * v, m( 2, 1 ) * v, m( 2, 2 ) * v, m( 2, 3 ) * v,
		m( 3, 0 ) * v, m( 3, 1 ) * v, m( 3, 2 ) * v, m( 3, 3 ) * v,
	};							       

	return AGMatrix( data );
}

inline AGMatrix operator*( const AGMatrix& m, float v )
{
	float data[] = 
	{
		m( 0, 0 ) * v, m( 0, 1 ) * v, m( 0, 2 ) * v, m( 0, 3 ) * v,
		m( 1, 0 ) * v, m( 1, 1 ) * v, m( 1, 2 ) * v, m( 1, 3 ) * v,
		m( 2, 0 ) * v, m( 2, 1 ) * v, m( 2, 2 ) * v, m( 2, 3 ) * v,
		m( 3, 0 ) * v, m( 3, 1 ) * v, m( 3, 2 ) * v, m( 3, 3 ) * v,
	};							       

	return AGMatrix( data );
}

inline AGVec3 operator*( const AGVec3& v, const AGMatrix& m )
{
	float w = 1.0f; 

	float x = v.x * m( 0, 0 ) + v.y * m( 1, 0 ) + v.z * m( 2, 0 ) + w * m( 3, 0 ); 
	float y = v.x * m( 0, 1 ) + v.y * m( 1, 1 ) + v.z * m( 2, 1 ) + w * m( 3, 1 );
	float z = v.x * m( 0, 2 ) + v.y * m( 1, 2 ) + v.z * m( 2, 2 ) + w * m( 3, 2 );
	w = v.x * m( 0, 3 ) + v.y * m( 1, 3 ) + v.z * m( 2, 3 ) + w * m( 3, 3 ); 

	return AGVec3( x / w, y / w, z / w );
}

inline AGVec4 operator*( const AGVec4& v, const AGMatrix& m )
{
	float x = v.x * m( 0, 0 ) + v.y * m( 1, 0 ) + v.z * m( 2, 0 ) + v.w * m( 3, 0 ); 
	float y = v.x * m( 0, 1 ) + v.y * m( 1, 1 ) + v.z * m( 2, 1 ) + v.w * m( 3, 1 );
	float z = v.x * m( 0, 2 ) + v.y * m( 1, 2 ) + v.z * m( 2, 2 ) + v.w * m( 3, 2 );
	float w = v.x * m( 0, 3 ) + v.y * m( 1, 3 ) + v.z * m( 2, 3 ) + v.w * m( 3, 3 ); 

	return AGVec4( x / w, y / w, z / w, 1.0f ); 
}

inline AGMatrix operator-( const AGMatrix& m1, const AGMatrix& m2 )
{
	float data[] = 
	{
		m1( 0, 0 ) - m2( 0, 0 ), m1( 0, 1 ) - m2( 0, 1 ), m1( 0, 2 ) - m2( 0, 2 ), m1( 0, 3 ) - m2( 0, 3 ),
		m1( 1, 0 ) - m2( 1, 0 ), m1( 1, 1 ) - m2( 1, 1 ), m1( 1, 2 ) - m2( 1, 2 ), m1( 1, 3 ) - m2( 1, 3 ),
		m1( 2, 0 ) - m2( 2, 0 ), m1( 2, 1 ) - m2( 2, 1 ), m1( 2, 2 ) - m2( 2, 2 ), m1( 2, 3 ) - m2( 2, 3 ),
		m1( 3, 0 ) - m2( 3, 0 ), m1( 3, 1 ) - m2( 3, 1 ), m1( 3, 2 ) - m2( 3, 2 ), m1( 3, 3 ) - m2( 3, 3 ),
	};

	return AGMatrix( data ); 
}

inline AGMatrix operator+( const AGMatrix& m1, const AGMatrix& m2 )
{
	float data[] = 
	{
		m1( 0, 0 ) + m2( 0, 0 ), m1( 0, 1 ) + m2( 0, 1 ), m1( 0, 2 ) + m2( 0, 2 ), m1( 0, 3 ) + m2( 0, 3 ),
		m1( 1, 0 ) + m2( 1, 0 ), m1( 1, 1 ) + m2( 1, 1 ), m1( 1, 2 ) + m2( 1, 2 ), m1( 1, 3 ) + m2( 1, 3 ),
		m1( 2, 0 ) + m2( 2, 0 ), m1( 2, 1 ) + m2( 2, 1 ), m1( 2, 2 ) + m2( 2, 2 ), m1( 2, 3 ) + m2( 2, 3 ),
		m1( 3, 0 ) + m2( 3, 0 ), m1( 3, 1 ) + m2( 3, 1 ), m1( 3, 2 ) + m2( 3, 2 ), m1( 3, 3 ) + m2( 3, 3 ),
	};

	return data;
	return AGMatrix( data ); 
}

inline AGMatrix operator/( const AGMatrix& m, float v )
{
	float data[] = 
	{
		m( 0, 0 ) / v, m( 0, 1 ) / v, m( 0, 2 ) / v, m( 0, 3 ) / v,
		m( 1, 0 ) / v, m( 1, 1 ) / v, m( 1, 2 ) / v, m( 1, 3 ) / v,
		m( 2, 0 ) / v, m( 2, 1 ) / v, m( 2, 2 ) / v, m( 2, 3 ) / v,
		m( 3, 0 ) / v, m( 3, 1 ) / v, m( 3, 2 ) / v, m( 3, 3 ) / v,
	};

	return AGMatrix( data );
}

#endif 