#ifndef AG_ARROW_H
#define AG_ARROW_H

#include <vector>

#include "Engine/Graphics/Objects/AGGizmo.h"
#include "Engine/Graphics/Objects/Shapes/AGBoxShape.h"

using namespace std;

class AGArrow : public AGGizmo
{
	public:
		enum ArrowAxis{ X_AXIS, Y_AXIS, Z_AXIS };
		AGArrow( ArrowAxis axis );
		~AGArrow();

		void draw(  AGSurface* surface  );
		float intersect( const AGVec3& rayOrigin, const AGVec3& rayDir );

		AGVec3 getAxis(); 
	private:
		ArrowAxis m_axis; 
		AGBoxShape* m_boundingBox;
};

#endif 