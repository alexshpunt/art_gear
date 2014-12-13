#ifndef AGDX_DRAGGER_H
#define AGDX_DRAGGER_H

#include "Graphics/Objects/Manipulators/AGDXManipulator.h"

class AGObject; 
class AGDXPrimitive;
class AGDXArrow; 
class AGDXSurface; 
class AGDXGizmo; 
class AGDXIntersectPlane; 
class AGDXCircle; 

using namespace std; 

class AGDXDragger : public AGDXManipulator
{
	public:
		AGDXDragger( ID3D10Device* device );
		~AGDXDragger();

		void mouseClickEvent( MouseButton btn, AGDXSurface* surface );
		void mouseMoveEvent( AGDXSurface* surface );

		void draw( AGDXSurface* surface );

	private:
		AGDXArrow* m_xArrow;
		AGDXArrow* m_yArrow; 
		AGDXArrow* m_zArrow; 

		AGDXIntersectPlane* m_xyPlane;
		AGDXIntersectPlane* m_xzPlane;
		AGDXIntersectPlane* m_yzPlane;

		AGDXCircle* m_circle; 

		AGDXGizmo* m_selectedObject; 
};

#endif 