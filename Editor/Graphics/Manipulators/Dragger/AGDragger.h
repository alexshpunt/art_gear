#ifndef AG_DRAGGER_H
#define AG_DRAGGER_H

#include "Engine/Graphics/Objects/AGManipulator.h"

class AGGameObject; 
class AGDrawable;
class AGArrow; 
class AGSurface; 
class AGGizmo; 
class AGIntersectPlane; 
class AGCircle; 

using namespace std; 

class AGDragger : public AGManipulator
{
	public:
		AGDragger();
		~AGDragger();

		bool mouseClickEvent( AGMouseButton btn, AGSurface* surface );
		bool mouseMoveEvent( AGSurface* surface );
		void mouseReleaseEvent( AGMouseButton btn ) override;

		void draw( AGSurface* surface );

	private:
		AGArrow* m_xArrow;
		AGArrow* m_yArrow; 
		AGArrow* m_zArrow; 

		AGIntersectPlane* m_xyPlane;
		AGIntersectPlane* m_xzPlane;
		AGIntersectPlane* m_yzPlane;

		AGGizmo* m_selectedObject; 
};

#endif 