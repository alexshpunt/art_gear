#ifndef AG_MATRIX4X4_H
#define AG_MATRIX4X4_H

class AGMatrixPrivate; 

class AGMatrix 
{
	public:
		AGMatrix();
		AGMatrix( float e );
		AGMatrix( float* data );
		AGMatrix( const AGMatrix& copy );
		
		void setData( float* data );
		float* getData() const; 

		float& getElem( int i, int j ); 
		float getElem( int i, int j ) const; 

		float getDeterminant(); 
		void inverse(); 
		AGMatrix getInversed(); 

		void setIdentity(); 
		bool isIdentity(); 

		void setProjectionLH( float angle, float aspectRatio, float nearPlane, float farPlane ); 

		void operator=( const AGMatrix& mtx );

		AGMatrix  operator+ ( const AGMatrix& mtx );
		AGMatrix& operator+=( const AGMatrix& mtx );

		AGMatrix  operator- ( const AGMatrix& mtx );
		AGMatrix& operator-=( const AGMatrix& mtx ); 

		AGMatrix  operator* ( float var ); 
		AGMatrix& operator*=( float var );

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