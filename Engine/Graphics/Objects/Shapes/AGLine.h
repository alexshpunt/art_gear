#ifndef AG_LINE_H
#define AG_LINE_H

#include "AGShape.h"

#include "Engine/Math/AGMath.h"

class AGLine : public AGShape
{
	public:
		AGLine( const AGVec3& startPoint, const AGVec3& endPoint, const AGColor& color = AGColor( 1.0f ) ); 
		~AGLine();

		void setLine( const AGVec3& startPoint, const AGVec3& endPoint, const AGColor& color = AGColor( 1.0f ) );

		void draw( AGSurface* surface ) override;
};

#endif 