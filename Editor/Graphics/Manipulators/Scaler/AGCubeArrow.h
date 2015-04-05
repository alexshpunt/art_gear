#ifndef AG_ARROW_H
#define AG_ARROW_H

#include <vector>

#include "Engine/Graphics/Objects/AGGizmo.h"
#include "Engine/Graphics/Objects/Shapes/AGBoxShape.h"

using namespace std;

class AGCubeArrow : public AGGizmo
{
	public:
		enum CubeArrowAxis{ X_AXIS, Y_AXIS, Z_AXIS };
		AGCubeArrow( CubeArrowAxis axis );
		~AGCubeArrow();

		void draw(  AGSurface* surface  );
		float intersect( const AGVec3& rayOrigin, const AGVec3& rayDir );

		AGVec3 getAxis(); 
	private:
		CubeArrowAxis m_axis; 
		AGBoxShape* m_boundingBox;
		AGVec3 m_axisDir; 
};

#endif 