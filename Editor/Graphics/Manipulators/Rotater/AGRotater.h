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

		void draw( AGSurface* surface );

	private:
		AGCircle* m_xCircle; 
		AGCircle* m_yCircle; 
		AGCircle* m_zCircle; 

		AGGizmo* m_selectedObject; 

		D3DXVECTOR3 m_v1;
		D3DXVECTOR3 m_v2; 
		D3DXVECTOR3 m_v3; 

		D3DXVECTOR3 m_tangent; 

		D3DXVECTOR3 m_angles; 
};


#endif 