#include "AGMatrix.h"

#include "AGMath.h"

#include <math.h>
#include <memory.h>

inline float* sumMatrices( const AGMatrix& m1, const AGMatrix& m2 )
{
	float data[] = 
	{
		m1( 0, 0 ) + m2( 0, 0 ), m1( 0, 1 ) + m2( 0, 1 ), m1( 0, 2 ) + m2( 0, 2 ), m1( 0, 3 ) + m2( 0, 3 ),
		m1( 1, 0 ) + m2( 1, 0 ), m1( 1, 1 ) + m2( 1, 1 ), m1( 1, 2 ) + m2( 1, 2 ), m1( 1, 3 ) + m2( 1, 3 ),
		m1( 2, 0 ) + m2( 2, 0 ), m1( 2, 1 ) + m2( 2, 1 ), m1( 2, 2 ) + m2( 2, 2 ), m1( 2, 3 ) + m2( 2, 3 ),
		m1( 3, 0 ) + m2( 3, 0 ), m1( 3, 1 ) + m2( 3, 1 ), m1( 3, 2 ) + m2( 3, 2 ), m1( 3, 3 ) + m2( 3, 3 ),
	};

	return data; 
}

inline float* subMatrices( const AGMatrix& m1, const AGMatrix& m2 )
{
	float data[] = 
	{
		m1( 0, 0 ) - m2( 0, 0 ), m1( 0, 1 ) - m2( 0, 1 ), m1( 0, 2 ) - m2( 0, 2 ), m1( 0, 3 ) - m2( 0, 3 ),
		m1( 1, 0 ) - m2( 1, 0 ), m1( 1, 1 ) - m2( 1, 1 ), m1( 1, 2 ) - m2( 1, 2 ), m1( 1, 3 ) - m2( 1, 3 ),
		m1( 2, 0 ) - m2( 2, 0 ), m1( 2, 1 ) - m2( 2, 1 ), m1( 2, 2 ) - m2( 2, 2 ), m1( 2, 3 ) - m2( 2, 3 ),
		m1( 3, 0 ) - m2( 3, 0 ), m1( 3, 1 ) - m2( 3, 1 ), m1( 3, 2 ) - m2( 3, 2 ), m1( 3, 3 ) - m2( 3, 3 ),
	};

	return data; 
}

inline float* mulMatrix( const AGMatrix& m, float v )
{
	float data[] = 
	{
		m( 0, 0 ) * v, m( 0, 1 ) * v, m( 0, 2 ) * v, m( 0, 3 ) * v,
		m( 1, 0 ) * v, m( 1, 1 ) * v, m( 1, 2 ) * v, m( 1, 3 ) * v,
		m( 2, 0 ) * v, m( 2, 1 ) * v, m( 2, 2 ) * v, m( 2, 3 ) * v,
		m( 3, 0 ) * v, m( 3, 1 ) * v, m( 3, 2 ) * v, m( 3, 3 ) * v,
	};

	return data;
}

inline float* mulMatrices( const AGMatrix& m1, const AGMatrix& m2 )
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

	return data; 
}

inline float* divMatrix( const AGMatrix& m, float v )
{
	float data[] = 
	{
		m( 0, 0 ) / v, m( 0, 1 ) / v, m( 0, 2 ) / v, m( 0, 3 ) / v,
		m( 1, 0 ) / v, m( 1, 1 ) / v, m( 1, 2 ) / v, m( 1, 3 ) / v,
		m( 2, 0 ) / v, m( 2, 1 ) / v, m( 2, 2 ) / v, m( 2, 3 ) / v,
		m( 3, 0 ) / v, m( 3, 1 ) / v, m( 3, 2 ) / v, m( 3, 3 ) / v,
	};

	return data;
}

struct IndexPair 
{
	IndexPair( int inI, int inJ ) : i( inI ), j( inJ ) {}  
	int i;
	int j; 
};

class AGMatrixPrivate
{
	public:
		enum AGMatrixDataType{ Identity, Translation, Rotation, Scale, Proj, Ortho };
		AGMatrixPrivate()
		{
			isIdentity = false;
			ableTranspose = false; 
			detMat = 0.0f; 
			memset( data, 0, sizeof( data ) );
			memset( adjMat, 0, sizeof( data ) );
		} 

		void setUndefinedState()
		{
			isIdentity = false;
			ableTranspose = false; 
		}

		void copyFrom( AGMatrixPrivate* p )
		{
			/*for( int i = 0; i < 4; i++ )
			{
				for( int j = 0; j < 4; j++ )
				{
					data[ i ][ j ] = p->data[ i ][ j ];
				}
			}*/

			memcpy_s( data, sizeof( data ), p->data, sizeof( data ) );

			isIdentity = p->isIdentity;
			ableTranspose = p->ableTranspose; 
		}

		float findDeterminant2x2( IndexPair leftTop, IndexPair rightBot )
		{
			return data[ leftTop.i ][ leftTop.j ] * data[ rightBot.i ][ rightBot.j ] - data[ leftTop.i ][ rightBot.j ] * data[ rightBot.i ][ leftTop.j ]; 
		}

		float findDeterminant3x3( IndexPair leftTop, IndexPair rightBot, IndexPair middle )
		{
			float detA00 = data[ leftTop.i ][ leftTop.j ] * findDeterminant2x2( IndexPair( middle.i, rightBot.j ), rightBot );
			float detA01 = data[ leftTop.i ][ middle.j ] * findDeterminant2x2( IndexPair( middle.i, leftTop.j ), rightBot ); 
			float detA02 = data[ leftTop.i ][ rightBot.j ] * findDeterminant2x2( IndexPair( middle.i, leftTop.j ), IndexPair( rightBot.i, middle.j ) );

			return detA00 + detA01 + detA02; 
		}

		void computeAdjMat()
		{
			adjMat[ 0 ][ 0 ] = data[ 0 ][ 0 ] * findDeterminant3x3( IndexPair( 1, 1 ), IndexPair( 3, 3 ), IndexPair( 2, 2 ) );
			adjMat[ 0 ][ 1 ] = data[ 0 ][ 1 ] * findDeterminant3x3( IndexPair( 1, 0 ), IndexPair( 3, 3 ), IndexPair( 2, 2 ) );
			adjMat[ 0 ][ 2 ] = data[ 0 ][ 2 ] * findDeterminant3x3( IndexPair( 1, 0 ), IndexPair( 3, 3 ), IndexPair( 2, 1 ) );
			adjMat[ 0 ][ 3 ] = data[ 0 ][ 3 ] * findDeterminant3x3( IndexPair( 1, 0 ), IndexPair( 3, 2 ), IndexPair( 2, 1 ) );
			
			detMat = adjMat[ 0 ][ 0 ] + adjMat[ 0 ][ 1 ] + adjMat[ 0 ][ 2 ] + adjMat[ 0 ][ 3 ]; 

			adjMat[ 1 ][ 0 ] = data[ 1 ][ 0 ] * findDeterminant3x3( IndexPair( 0, 1 ), IndexPair( 3, 3 ), IndexPair( 2, 2 ) );
			adjMat[ 1 ][ 1 ] = data[ 1 ][ 1 ] * findDeterminant3x3( IndexPair( 0, 0 ), IndexPair( 3, 3 ), IndexPair( 2, 2 ) ); 
			adjMat[ 1 ][ 2 ] = data[ 1 ][ 2 ] * findDeterminant3x3( IndexPair( 0, 0 ), IndexPair( 3, 3 ), IndexPair( 2, 2 ) );
			adjMat[ 1 ][ 3 ] = data[ 1 ][ 3 ] * findDeterminant3x3( IndexPair( 0, 0 ), IndexPair( 3, 2 ), IndexPair( 2, 1 ) );
			
			adjMat[ 2 ][ 0 ] = data[ 2 ][ 0 ] * findDeterminant3x3( IndexPair( 0, 1 ), IndexPair( 3, 3 ), IndexPair( 1, 2 ) );
			adjMat[ 2 ][ 1 ] = data[ 2 ][ 1 ] * findDeterminant3x3( IndexPair( 0, 0 ), IndexPair( 3, 3 ), IndexPair( 1, 2 ) ); 
			adjMat[ 2 ][ 2 ] = data[ 2 ][ 2 ] * findDeterminant3x3( IndexPair( 0, 0 ), IndexPair( 3, 3 ), IndexPair( 1, 1 ) );
			adjMat[ 2 ][ 3 ] = data[ 2 ][ 3 ] * findDeterminant3x3( IndexPair( 0, 0 ), IndexPair( 3, 2 ), IndexPair( 1, 1 ) ); 
			
			adjMat[ 3 ][ 0 ] = data[ 3 ][ 0 ] * findDeterminant3x3( IndexPair( 0, 1 ), IndexPair( 2, 3 ), IndexPair( 1, 2 ) );
			adjMat[ 3 ][ 1 ] = data[ 3 ][ 1 ] * findDeterminant3x3( IndexPair( 0, 0 ), IndexPair( 2, 3 ), IndexPair( 1, 2 ) ); 
			adjMat[ 3 ][ 2 ] = data[ 3 ][ 2 ] * findDeterminant3x3( IndexPair( 0, 0 ), IndexPair( 2, 3 ), IndexPair( 1, 1 ) );
			adjMat[ 3 ][ 3 ] = data[ 3 ][ 3 ] * findDeterminant3x3( IndexPair( 0, 0 ), IndexPair( 2, 2 ), IndexPair( 1, 1 ) );  

			swapAdj( IndexPair( 0, 1 ), IndexPair( 1, 0 ) );
			swapAdj( IndexPair( 0, 2 ), IndexPair( 2, 0 ) );
			swapAdj( IndexPair( 0, 3 ), IndexPair( 3, 0 ) );
			swapAdj( IndexPair( 1, 2 ), IndexPair( 2, 1 ) );
			swapAdj( IndexPair( 1, 3 ), IndexPair( 3, 1 ) );
			swapAdj( IndexPair( 2, 3 ), IndexPair( 3, 2 ) );
		}

		void swapAdj( IndexPair e1, IndexPair e2 )
		{
			float tmp = adjMat[ e1.i ][ e1.j ];
			adjMat[ e1.i ][ e1.j ] = adjMat[ e2.i ][ e2.j ];
			adjMat[ e2.i ][ e2.j ] = tmp; 
		}

		void inverse()
		{
			computeAdjMat(); 
			for( int i = 0; i < 4; i++ )
			{
				for( int j = 0; j < 4; j++ )
				{
					data[ i ][ j ] = adjMat[ i ][ j ] / detMat; 
				}
			}
		}

		float data[ 4 ][ 4 ]; 
		float adjMat[ 4 ][ 4 ];
		float detMat; 

		bool isIdentity; 
		bool ableTranspose; 
};

AGMatrix::AGMatrix()
{
	p = new AGMatrixPrivate; 
}

AGMatrix::AGMatrix(float e)
{
	p = new AGMatrixPrivate; 

	for( int i = 0; i < 4; i++ )
	{
		for( int j = 0; j < 4; j++ )
		{
			p->data[ i ][ j ] = e; 
		}
	}

	p->isIdentity = false;
	p->ableTranspose = true; 
}

void AGMatrix::setData(float* data)
{
	memcpy_s( p->data, sizeof( p->data ), data, sizeof( p->data ) );
	p->setUndefinedState(); 
}

AGMatrix::AGMatrix(const AGMatrix& copy)
{
	p = new AGMatrixPrivate; 
	p->copyFrom( copy.p );
}

AGMatrix::AGMatrix(float* data)
{
	p = new AGMatrixPrivate;
	memcpy_s( p->data, sizeof( p->data ), data, sizeof( p->data ) );
}

float* AGMatrix::getData() const
{
	return p->data[ 0 ]; 
}

void AGMatrix::setIdentity()
{
	float m[] = { 1.0f, 0.0f, 0.0f, 0.0f,
	              0.0f, 1.0f, 0.0f, 0.0f,
	              0.0f, 0.0f, 1.0f, 0.0f,
	              0.0f, 0.0f, 0.0f, 1.0f };

	memcpy_s( p->data, sizeof( p->data ), m, sizeof( m ) );

	p->isIdentity = true; 
}

bool AGMatrix::isIdentity()
{
	return p->isIdentity; 
}

float& AGMatrix::operator()(int i, int j)
{
	if( i < 0 || i > 4 || j < 0 || j > 4 )
	{
		return p->data[ 0 ][ 0 ];  
	}
	return p->data[ i ][ j ]; 

}

float AGMatrix::operator()(int i, int j) const
{
	if( i < 0 || i > 4 || j < 0 || j > 4 )
	{
		return p->data[ 0 ][ 0 ];  
	}
	return p->data[ i ][ j ]; 
}

float& AGMatrix::getElem(int i, int j)
{
	if( i < 0 || i > 4 || j < 0 || j > 4 )
	{
		return p->data[ 0 ][ 0 ];
	}
	return p->data[ i ][ j ]; 
}

float AGMatrix::getElem(int i, int j) const
{
	if( i < 0 || i > 4 || j < 0 || j > 4 )
	{
		return p->data[ 0 ][ 0 ];
	}
	return p->data[ i ][ j ]; 
}

AGMatrix AGMatrix::operator+(const AGMatrix& mtx)
{
	AGMatrix newMtx = *this; 
	newMtx.setData( sumMatrices( newMtx, mtx ) );
	return newMtx; 
}

AGMatrix& AGMatrix::operator+=(const AGMatrix& mtx)
{
	setData( sumMatrices( *this, mtx ) );
	return *this; 
}

AGMatrix AGMatrix::operator-(const AGMatrix& mtx)
{
	AGMatrix newMtx = *this; 
	newMtx.setData( subMatrices( newMtx, mtx ) );
	return newMtx;
}

AGMatrix& AGMatrix::operator-=(const AGMatrix& mtx)
{
	setData( subMatrices( *this, mtx ) );
	return *this; 
}

AGMatrix AGMatrix::operator*(float var)
{
	AGMatrix newMtx = *this; 
	newMtx.setData( mulMatrix( newMtx, var ) );
	return newMtx;
}

AGMatrix& AGMatrix::operator*=(float var)
{
	setData( mulMatrix( *this, var ) );
	return *this; 
}

AGMatrix operator*( const AGMatrix& m1, const AGMatrix& m2 )
{
	return m1 * m2; 
}

AGMatrix AGMatrix::operator*(const AGMatrix& m2)
{
	AGMatrix m1 = *this; 
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

	AGMatrix retMtx( data );
	return retMtx;  
}

AGMatrix& AGMatrix::operator*=(const AGMatrix& mtx)
{
	AGMatrix newMtx = *this;
	newMtx = newMtx * mtx; 
	*this = newMtx;
	return *this; 
}

void AGMatrix::operator=(const AGMatrix& mtx)
{
	if( p )
		delete p;
	p = new AGMatrixPrivate; 
	p->copyFrom( mtx.p );
}

AGMatrix AGMatrix::operator/(float var)
{
	AGMatrix newMtx = *this; 
	newMtx.setData( divMatrix( newMtx, var ) );
	return newMtx;
}

AGMatrix& AGMatrix::operator/=(float var)
{
	setData( divMatrix( *this, var ) );
	return *this; 
}

float AGMatrix::getDeterminant()
{
	float detA00 = p->data[ 0 ][ 0 ] * p->findDeterminant3x3( IndexPair( 1, 1 ), IndexPair( 3, 3 ), IndexPair( 2, 2 ) );
	float detA01 = p->data[ 0 ][ 1 ] * p->findDeterminant3x3( IndexPair( 1, 0 ), IndexPair( 3, 3 ), IndexPair( 2, 2 ) );
	float detA02 = p->data[ 0 ][ 2 ] * p->findDeterminant3x3( IndexPair( 1, 0 ), IndexPair( 3, 3 ), IndexPair( 2, 1 ) );
	float detA03 = p->data[ 0 ][ 3 ] * p->findDeterminant3x3( IndexPair( 1, 0 ), IndexPair( 3, 2 ), IndexPair( 2, 1 ) );

	return detA00 + detA01 + detA02 + detA03; 
}

void AGMatrix::inverse()
{
	p->inverse();
}

AGMatrix AGMatrix::getInversed()
{
	AGMatrix mtx( *this );
	mtx.inverse(); 
	return mtx; 
}

void AGMatrix::setPerspectiveLH(float angle, float aspectRatio, float nearPlane, float farPlane)
{
	if( AGMath::isEqual( nearPlane, farPlane ) || aspectRatio == 0.0f )
		return; 

	float alpha = AGMath::toRadians( angle * 0.5f );
	float sinA = sin( alpha );
	if( sinA == 0 )
		return; 
	float cosA = cos( alpha );
	float cotA = cosA / sinA; 
	float clip = farPlane - nearPlane; 

	memset( p->data, 0, sizeof( p->data ) );
	p->data[ 0 ][ 0 ] = cotA / aspectRatio; 
	p->data[ 1 ][ 1 ] = cotA; 
	p->data[ 2 ][ 2 ] = farPlane / ( farPlane - nearPlane );
	p->data[ 2 ][ 3 ] = 1.0f; 
	p->data[ 3 ][ 2 ] = -p->data[ 2 ][ 2 ] * nearPlane; 
}

void AGMatrix::setOrthoLH(float viewWidth, float viewHeight, float nearPlane, float farPlane)
{
	if( AGMath::isEqual( nearPlane, farPlane ) ||
	    AGMath::isEqual( viewWidth, 0.0f )     ||
	    AGMath::isEqual( viewHeight, 0.0f ) )
	{
		return; 
	}

	float range = 1.0f / ( farPlane - nearPlane );
	
	memset( p->data, 0, sizeof( p->data ) );

	p->data[ 0 ][ 0 ] = 2.0f / viewWidth; 
	p->data[ 1 ][ 1 ] = 2.0f / viewHeight;
	p->data[ 2 ][ 2 ] = range; 
	p->data[ 3 ][ 2 ] = -range * nearPlane; 
	p->data[ 3 ][ 3 ] = 1.0f; 
}

void AGMatrix::setLookAtLH( const AGVec3& inEye, const AGVec3& inCenter, const AGVec3& inUp )
{
	AGVec3 zAxis = inCenter - inEye;
	zAxis.normilize(); 
	AGVec3 xAxis = AGVec3::cross( inUp, zAxis );
	xAxis.normilize();
	AGVec3 yAxis = AGVec3::cross( zAxis, xAxis ); 

	memset( p->data, 0, sizeof( p->data ) );

	p->data[ 0 ][ 0 ] = xAxis.x; 
	p->data[ 1 ][ 0 ] = xAxis.y;
	p->data[ 2 ][ 0 ] = xAxis.z; 

	p->data[ 0 ][ 1 ] = yAxis.x; 
	p->data[ 1 ][ 1 ] = yAxis.y;
	p->data[ 2 ][ 1 ] = yAxis.z; 

	p->data[ 0 ][ 2 ] = zAxis.x; 
	p->data[ 1 ][ 2 ] = zAxis.y;
	p->data[ 2 ][ 2 ] = zAxis.z;
	
	p->data[ 3 ][ 0 ] = -AGVec3::dot( xAxis, inEye );
	p->data[ 3 ][ 1 ] = -AGVec3::dot( yAxis, inEye );
	p->data[ 3 ][ 2 ] = -AGVec3::dot( zAxis, inEye );

	p->data[ 3 ][ 3 ] = 1.0f; 

	/*AGMatrix rotMatrix = *this; 

	AGMatrix translMatrix; 
	translMatrix.setIdentity(); 
	translMatrix( 3, 0 ) = -inEye.x; 
	translMatrix( 3, 1 ) = -inEye.y;
	translMatrix( 3, 2 ) = -inEye.z; 
	
	*this = rotMatrix * translMatrix; */
}

void AGMatrix::copyFrom(const AGMatrix& copy)
{
	p->copyFrom( copy.p );
}



