#include "AGMathHelp.h"

#include "AGVec2.h"

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

}

