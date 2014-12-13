#ifndef AGDX_ROTATEMANIP_H
#define AGDX_ROTATEMANIP_H

#include "Graphics/Objects/Manipulators/AGDXManipulator.h"

class AGObject; 
class AGDXPrimitive;
class AGDXCircle; 
class AGDXSurface; 
class AGDXGizmo; 
class AGDXLine; 

using namespace std; 

class AGDXRotater : public AGDXManipulator
{
	public:
		AGDXRotater( ID3D10Device* device );
		~AGDXRotater();

		void mouseClickEvent( MouseButton btn, AGDXSurface* surface );
		void mouseMoveEvent( AGDXSurface* surface );

		void draw( AGDXSurface* surface );

	private:
		AGDXCircle* m_xCircle; 
		AGDXCircle* m_yCircle; 
		AGDXCircle* m_zCircle; 

		AGDXGizmo* m_selectedObject; 

		D3DXVECTOR3 m_v1;
		D3DXVECTOR3 m_v2; 
		D3DXVECTOR3 m_v3; 

		D3DXVECTOR3 m_tangent; 
};


#endif 