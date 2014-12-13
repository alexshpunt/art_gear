#ifndef AGDX_SCALER_H
#define AGDX_SCALER_H

#include "Graphics/Objects/Manipulators/AGDXManipulator.h"

class AGDXPrimitive;
class AGDXCubeArrow; 
class AGDXSurface; 
class AGDXGizmo; 
class AGDXIntersectTriangle; 
class AGDXCircle; 

using namespace std; 

class AGDXScaler : public AGDXManipulator
{
	public:
		AGDXScaler( ID3D10Device* device );
		~AGDXScaler();

		void mouseClickEvent( MouseButton btn, AGDXSurface* surface );
		void mouseMoveEvent( AGDXSurface* surface );

		void draw( AGDXSurface* surface );

	private:
		AGDXCubeArrow* m_xArrow;
		AGDXCubeArrow* m_yArrow; 
		AGDXCubeArrow* m_zArrow; 

		AGDXIntersectTriangle* m_xyPlane;
		AGDXIntersectTriangle* m_xzPlane;
		AGDXIntersectTriangle* m_yzPlane;
		AGDXIntersectTriangle* m_xyzPlane;

		AGDXGizmo* m_selectedObject;  
};

#endif 