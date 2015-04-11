#ifndef AG_ROTATEMANIP_H
#define AG_ROTATEMANIP_H

#include "Engine/Graphics/Objects/AGManipulator.h"

class AGGameObject; 
class AGDrawable;
class AGCircle; 
class AGSurface; 
class AGGizmo; 
class AGLine; 

using namespace std; 

class AGRotater : public AGManipulator
{
	public:
		AGRotater();
		~AGRotater();

		bool mouseClickEvent( AGMouseButton btn, AGSurface* surface );
		bool mouseMoveEvent( AGSurface* surface );
		void mouseReleaseEvent( AGMouseButton btn );

		void draw( AGSurface* surface );

	private:
		AGCircle* m_xCircle; 
		AGCircle* m_yCircle; 
		AGCircle* m_zCircle; 

		AGGizmo* m_selectedObject; 

		AGVec3 m_v1;
		AGVec3 m_v2; 
		AGVec3 m_v3; 

		AGVec3 m_tangent; 

		AGVec3 m_angles; 
};


#endif 