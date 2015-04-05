#ifndef AG_SCALER_H
#define AG_SCALER_H

#include "Engine/Graphics/Objects/AGManipulator.h"

class AGDrawable;
class AGCubeArrow; 
class AGSurface; 
class AGGizmo; 
class AGIntersectTriangle; 
class AGCircle; 

using namespace std; 

class AGScaler : public AGManipulator
{
	public:
		AGScaler();
		~AGScaler();

		bool mouseClickEvent( AGMouseButton btn, AGSurface* surface );
		bool mouseMoveEvent( AGSurface* surface );

		void draw( AGSurface* surface );

	private:
		AGCubeArrow* m_xArrow;
		AGCubeArrow* m_yArrow; 
		AGCubeArrow* m_zArrow; 

		AGIntersectTriangle* m_xyPlane;
		AGIntersectTriangle* m_xzPlane;
		AGIntersectTriangle* m_yzPlane;
		AGIntersectTriangle* m_xyzPlane;

		AGGizmo* m_selectedObject;  
};

#endif 