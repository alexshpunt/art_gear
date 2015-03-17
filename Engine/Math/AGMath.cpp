#include "AGMath.h"

namespace AGMath
{

	bool isEqual( double a, double b )
	{
		if( fabs( a - b ) < 0.001 )
			return true; 
		else 
			return false; 
	}

	bool isEqual( float a, float b )
	{
		if( fabs( a - b ) < 0.001 )
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
