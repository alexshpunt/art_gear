#include "AGMathHelp.h"

#include "AGVec2.h"
#include "AGVec3.h"

AGRadians AGDegrees::toRadians()
{
	return AGRadians( AGMath::toRadians( value ) ); 
}


AGDegrees AGRadians::toDegrees()
{
	return AGDegrees( AGMath::toDegrees( value ) );
}

namespace AGMath
{

	bool isEqual( double a, double b )
	{
		if( fabs( a - b ) < EPSILON_FOR_DOUBLE )
			return true; 
		else 
			return false; 
	}

	bool isEqual( float a, float b )
	{
		if( fabs( a - b ) < EPSILON_FOR_FLOAT )
			return true; 
		else 
			return false; 
	}

	void generateCircle2D(float radius, float step, std::vector< AGVec2 >& points)
	{
		for( float angle = 0.0f; angle < PiX2 + step; angle += step )
		{
			points.push_back( AGVec2( radius * cos( angle ), radius * sin( angle ) ) );
		}
	}

	AGMath::IntersectResult intersectTriangle(const AGVec3& rayOrigin, const AGVec3& rayDir, const Triangle& triangle, bool cullFace )
	{
		IntersectResult res; 
		double det, invDet; 

		AGVec3 edge1 = triangle.v2 - triangle.v1; 
		AGVec3 edge2 = triangle.v3 - triangle.v1; 

		AGVec3 pVec = AGVec3::cross( rayDir, edge2 );

		det = AGVec3::dot( edge1, pVec ); 

		if( cullFace )
		{
			if( det < EPSILON_FOR_DOUBLE )
			{
				return res; 
			}

			AGVec3 tVec = rayOrigin - triangle.v1; 

			res.u = AGVec3::dot( tVec, pVec );

			if( res.u < 0.0f || res.u > det )
			{
				return res; 
			}

			AGVec3 qVec = AGVec3::cross( tVec, edge1 );

			res.v = AGVec3::dot( rayDir, qVec );

			if( res.v < 0.0f || ( res.v + res.u ) > det )
			{
				return res; 
			}

			res.distance = AGVec3::dot( edge2, qVec );

			invDet = 1.0f / det; 

			res.distance *= invDet;
			res.u *= invDet;
			res.v *= invDet; 
			res.hit = true;
		}
		else 
		{
			if( fabs( det ) < EPSILON_FOR_DOUBLE )
			{
				return res; 
			}
			invDet = 1.0f / det; 

			AGVec3 tVec = rayOrigin - triangle.v1; 

			res.u = AGVec3::dot( tVec, pVec ) * invDet; 

			if( res.u < 0.0f || res.u > 1.0f ) 
			{
				return res; 
			}

			AGVec3 qVec = AGVec3::cross( tVec, edge1 );

			res.v = AGVec3::dot( rayDir, qVec ) * invDet;

			if( res.v < 0.0f || res.v > 1.0f ) 
			{
				return res; 
			}

			res.distance = AGVec3::dot( edge2, qVec ) * invDet; 

			if( res.distance > EPSILON_FOR_DOUBLE )
			{
				res.hit = true;
			}
		}

		return res; 
	}


}

AGEulerAngles& AGEulerAngles::operator+=(const AGEulerAngles& a)
{
	x += a.x; 
	y += a.y;
	z += a.z;

	return *this; 
}

bool AGEulerAngles::operator==(const AGEulerAngles& a)
{
	return AGMath::isEqual( x, a.x ) && AGMath::isEqual( y, a.y ) && AGMath::isEqual( z, a.z );
}

AGEulerAngles& AGEulerAngles::operator=(const AGEulerAngles& copy)
{
	AGEulerAngles a( copy );
	*this = a; 
	return *this; 
}

AGEulerAngles operator+( const AGEulerAngles& a1, const AGEulerAngles& a2 )
{
	return AGEulerAngles( a1.x + a2.x, a1.y + a2.y, a1.z + a2.z );
}

AGEulerAngles operator-( const AGEulerAngles& a1, const AGEulerAngles& a2 )
{
	return AGEulerAngles( a1.x - a2.x, a1.y - a2.y, a1.z - a2.z );
}