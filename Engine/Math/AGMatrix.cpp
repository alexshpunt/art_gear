#include "AGMatrix.h"

#include "AGMath.h"

#include <math.h>
#include <memory.h>
#include <iomanip>
#include <iostream>

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
			float detA00 = data[ leftTop.i ][ leftTop.j ] * findDeterminant2x2( middle, rightBot );
			float detA01 = data[ leftTop.i ][ middle.j ] * findDeterminant2x2( IndexPair( middle.i, leftTop.j ), rightBot ); 
			float detA02 = data[ leftTop.i ][ rightBot.j ] * findDeterminant2x2( IndexPair( middle.i, leftTop.j ), IndexPair( rightBot.i, middle.j ) );

			return detA00 - detA01 + detA02; 
		}

		void computeAdjMat()
		{
			adjMat[ 0 ][ 0 ] = +findDeterminant3x3( IndexPair( 1, 1 ), IndexPair( 3, 3 ), IndexPair( 2, 2 ) );
			adjMat[ 0 ][ 1 ] = -findDeterminant3x3( IndexPair( 1, 0 ), IndexPair( 3, 3 ), IndexPair( 2, 2 ) );
			adjMat[ 0 ][ 2 ] = +findDeterminant3x3( IndexPair( 1, 0 ), IndexPair( 3, 3 ), IndexPair( 2, 1 ) );
			adjMat[ 0 ][ 3 ] = -findDeterminant3x3( IndexPair( 1, 0 ), IndexPair( 3, 2 ), IndexPair( 2, 1 ) );

			adjMat[ 1 ][ 0 ] = -findDeterminant3x3( IndexPair( 0, 1 ), IndexPair( 3, 3 ), IndexPair( 2, 2 ) );
			adjMat[ 1 ][ 1 ] = +findDeterminant3x3( IndexPair( 0, 0 ), IndexPair( 3, 3 ), IndexPair( 2, 2 ) ); 
			adjMat[ 1 ][ 2 ] = -findDeterminant3x3( IndexPair( 0, 0 ), IndexPair( 3, 3 ), IndexPair( 2, 1 ) );
			adjMat[ 1 ][ 3 ] = +findDeterminant3x3( IndexPair( 0, 0 ), IndexPair( 3, 2 ), IndexPair( 2, 1 ) );

			adjMat[ 2 ][ 0 ] = +findDeterminant3x3( IndexPair( 0, 1 ), IndexPair( 3, 3 ), IndexPair( 1, 2 ) );
			adjMat[ 2 ][ 1 ] = -findDeterminant3x3( IndexPair( 0, 0 ), IndexPair( 3, 3 ), IndexPair( 1, 2 ) ); 
			adjMat[ 2 ][ 2 ] = +findDeterminant3x3( IndexPair( 0, 0 ), IndexPair( 3, 3 ), IndexPair( 1, 1 ) );
			adjMat[ 2 ][ 3 ] = -findDeterminant3x3( IndexPair( 0, 0 ), IndexPair( 3, 2 ), IndexPair( 1, 1 ) ); 

			adjMat[ 3 ][ 0 ] = -findDeterminant3x3( IndexPair( 0, 1 ), IndexPair( 2, 3 ), IndexPair( 1, 2 ) );
			adjMat[ 3 ][ 1 ] = +findDeterminant3x3( IndexPair( 0, 0 ), IndexPair( 2, 3 ), IndexPair( 1, 2 ) ); 
			adjMat[ 3 ][ 2 ] = -findDeterminant3x3( IndexPair( 0, 0 ), IndexPair( 2, 3 ), IndexPair( 1, 1 ) );
			adjMat[ 3 ][ 3 ] = +findDeterminant3x3( IndexPair( 0, 0 ), IndexPair( 2, 2 ), IndexPair( 1, 1 ) );  

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

AGMatrix::AGMatrix( bool identity )
{
	p = new AGMatrixPrivate; 
	if( identity )
		setIdentity(); 
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

AGMatrix& AGMatrix::operator+=(const AGMatrix& mtx)
{
	AGMatrix newMtx( *this );
	*this = newMtx + mtx;
	return *this; 
}


AGMatrix& AGMatrix::operator-=(const AGMatrix& mtx)
{
	AGMatrix newMtx( *this );
	*this = newMtx - mtx;
	return *this; 
}

AGMatrix& AGMatrix::operator*=(float var)
{
	AGMatrix mtx( *this ); 
	*this = mtx * var; 
	return *this; 
}

AGMatrix& AGMatrix::operator*=(const AGMatrix& mtx)
{
	AGMatrix newMtx( *this ); 
	*this = newMtx * mtx;
	return *this;  
}

void AGMatrix::operator=(const AGMatrix& mtx)
{
	if( p )
		delete p;
	p = new AGMatrixPrivate; 
	p->copyFrom( mtx.p );
}

AGMatrix& AGMatrix::operator/=(float var)
{
	AGMatrix newMtx( *this ); 
	*this = newMtx / var;
	return *this; 
}

float AGMatrix::getDeterminant()
{
	float detA00 = p->data[ 0 ][ 0 ] * p->findDeterminant3x3( IndexPair( 1, 1 ), IndexPair( 3, 3 ), IndexPair( 2, 2 ) );
	float detA01 = p->data[ 0 ][ 1 ] * p->findDeterminant3x3( IndexPair( 1, 0 ), IndexPair( 3, 3 ), IndexPair( 2, 2 ) );
	float detA02 = p->data[ 0 ][ 2 ] * p->findDeterminant3x3( IndexPair( 1, 0 ), IndexPair( 3, 3 ), IndexPair( 2, 1 ) );
	float detA03 = p->data[ 0 ][ 3 ] * p->findDeterminant3x3( IndexPair( 1, 0 ), IndexPair( 3, 2 ), IndexPair( 2, 1 ) );

	p->detMat = detA00 - detA01 + detA02 - detA03; 
	return p->detMat; 
}

void AGMatrix::inverse()
{
	getDeterminant(); 
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
}

void AGMatrix::copyFrom(const AGMatrix& copy)
{
	p->copyFrom( copy.p );
}

void AGMatrix::setRotateX(float angle)
{
	float radians = AGMath::toRadians( angle );

	float cosA = cos( radians );
	float sinA = sin( radians );

	p->data[ 0 ][ 0 ] = 1.0f; 
	p->data[ 1 ][ 1 ] = cosA;
	p->data[ 2 ][ 2 ] = cosA;
	p->data[ 2 ][ 1 ] = -sinA; 
	p->data[ 1 ][ 2 ] =  sinA;
}

void AGMatrix::setRotateY(float angle)
{
	float radians = AGMath::toRadians( angle );

	float cosA = cos( radians );
	float sinA = sin( radians );

	p->data[ 0 ][ 0 ] =  cosA; 
	p->data[ 0 ][ 2 ] = -sinA;
	p->data[ 2 ][ 0 ] =  sinA; 
	p->data[ 2 ][ 2 ] =  cosA; 
}

void AGMatrix::setRotateZ(float angle)
{
	float radians = AGMath::toRadians( angle );

	float cosA = cos( radians );
	float sinA = sin( radians );

	p->data[ 0 ][ 0 ] =  cosA; 
	p->data[ 1 ][ 1 ] =  cosA;
	p->data[ 0 ][ 1 ] =  sinA; 
	p->data[ 1 ][ 0 ] = -sinA;
}

void AGMatrix::setRotate( const AGVec3& axis, float angle )
{
	float radians = AGMath::toRadians( angle );

	float cosA = cos( radians );
	float sinA = sin( radians );

	AGVec3 normal = axis; 
	normal.normilize(); 

	p->data[ 0 ][ 0 ] = cosA + ( 1 - cosA ) * ( normal.x * normal.x );
	p->data[ 1 ][ 0 ] = ( 1 - cosA ) * ( normal.x * normal.y ) - sinA * normal.z; 
	p->data[ 2 ][ 0 ] = ( 1 - cosA ) * ( normal.x * normal.z ) + sinA * normal.y;
	
	p->data[ 0 ][ 1 ] = ( 1 - cosA ) * ( normal.y * normal.x ) + sinA * normal.z;
	p->data[ 1 ][ 1 ] = cosA + ( 1 - cosA ) * ( normal.y * normal.y );  
	p->data[ 2 ][ 1 ] = ( 1 - cosA ) * ( normal.y * normal.z ) - sinA * normal.x;
	
	p->data[ 0 ][ 2 ] = ( 1 - cosA ) * ( normal.z * normal.x ) - sinA * normal.y; 
	p->data[ 1 ][ 2 ] = ( 1 - cosA ) * ( normal.z * normal.y ) + sinA * normal.x; 
	p->data[ 2 ][ 2 ] = cosA + ( 1 - cosA ) * ( normal.z * normal.z ); 
}

void AGMatrix::setRotate(float x, float y, float z)
{
	AGMatrix rX; 
	rX.setIdentity();
	rX.setRotateX( x );

	AGMatrix rY; 
	rY.setIdentity();
	rY.setRotateY( y );

	AGMatrix rZ; 
	rZ.setIdentity();
	rZ.setRotateZ( z );

	*this = rZ * rX * rY; 
}

void AGMatrix::setTranslate(const AGVec3& transl)
{
	p->data[ 3 ][ 0 ] = transl.x; 
	p->data[ 3 ][ 1 ] = transl.y;
	p->data[ 3 ][ 2 ] = transl.z; 
}

void AGMatrix::setScale(const AGVec3& scale)
{
	p->data[ 0 ][ 0 ] = scale.x; 
	p->data[ 1 ][ 1 ] = scale.y;
	p->data[ 2 ][ 2 ] = scale.z; 
}

AGMatrix::operator float *() const
{
	return p->data[ 0 ];
}


