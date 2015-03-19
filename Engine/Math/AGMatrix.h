#ifndef AG_MATRIX4X4_H
#define AG_MATRIX4X4_H

class AGMatrixPrivate; 

class AGVec3; 
class AGVec4;

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

		void operator=( const AGMatrix& mtx );

		AGMatrix  operator+ ( const AGMatrix& mtx );
		AGMatrix& operator+=( const AGMatrix& mtx );

		AGMatrix  operator- ( const AGMatrix& mtx );
		AGMatrix& operator-=( const AGMatrix& mtx ); 

		AGMatrix  operator* ( float var ); 
		AGMatrix& operator*=( float var );

		friend AGMatrix operator*( const AGMatrix& m1, const AGMatrix& m2 );
		friend AGMatrix operator-( const AGMatrix& m1, const AGMatrix& m2 );
		friend AGMatrix operator+( const AGMatrix& m1, const AGMatrix& m2 );
		friend AGMatrix operator*( const AGMatrix& m, float factor ); 
		friend AGMatrix operator/( const AGMatrix& m, float divider );
		friend AGMatrix operator*( const AGMatrix& m, const AGVec3& v ); 
		friend AGMatrix operator*( const AGMatrix& m, const AGVec4& v );

		AGMatrix  operator* ( const AGMatrix& mtx );
		AGMatrix& operator*=( const AGMatrix& mtx ); 

		AGMatrix  operator/ ( float var );
		AGMatrix& operator/=( float var );

		float& operator()( int i, int j ); 
		float  operator()( int i, int j ) const; 
	private:	
		AGMatrixPrivate* p; 
};

#endif 