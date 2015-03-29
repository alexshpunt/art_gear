#ifndef AG_INTERSECTPLANE_H
#define AG_INTERSECTPLANE_H

#include <map>

#include "Engine/Graphics/Objects/AGGizmo.h"
#include "Engine/Graphics/Objects/AGBoundingBox.h"

class AGArrow; 

class AGIntersectPlane : public AGGizmo
{
	public:
		enum PlaneAxis{ XZ_AXIS, YZ_AXIS, XY_AXIS };
		AGIntersectPlane( PlaneAxis axis );
		~AGIntersectPlane();

		void draw(  AGSurface* surface  );

		AGVec3 getAxis();
	private:
		PlaneAxis m_axis;
};

#endif 