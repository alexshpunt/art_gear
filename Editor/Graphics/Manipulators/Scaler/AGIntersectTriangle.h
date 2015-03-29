#ifndef AG_INTERSECTTRIANGLE_H
#define AG_INTERSECTTRIANGLE_H

#include <map>

#include "Engine/Graphics/Objects/AGGizmo.h"
#include "Engine/Graphics/Objects/AGBoundingBox.h"

class AGArrow; 

class AGIntersectTriangle : public AGGizmo
{
	public:
		enum TriangleAxis{ XZ_AXIS, YZ_AXIS, XY_AXIS, XYZ_AXIS };
		AGIntersectTriangle( TriangleAxis axis );
		~AGIntersectTriangle();

		void setArrows( AGArrow* arrow1, AGArrow* arrow2 );

		void draw(  AGSurface* surface  );
		float intersect( const AGVec3& rayOrigin, const AGVec3& rayDir );

		AGVec3 getAxis();
	private:
		TriangleAxis m_axis;

		AGArrow* m_arrow1; 
		AGArrow* m_arrow2; 
};

#endif 