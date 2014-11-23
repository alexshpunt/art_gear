#ifndef AGDX_ROTATEMANIP_H
#define AGDX_ROTATEMANIP_H

#include <d3dx10.h>
#include <d3d10.h>
#include <string>

class AGObject; 
class AGDXPrimitive;
class AGDXCircle; 
class AGDXSurface; 
class AGDXGizmo; 
class AGDXLine; 

using namespace std; 

class AGDXRotater 
{
	public:
		AGDXRotater( ID3D10Device* device );
		~AGDXRotater();

		void setObject( AGObject* object );
		AGObject* getObject() const; 

		void mouseClickEvent( const string& btn, AGDXSurface* surface );
		void mouseMoveEvent( AGDXSurface* surface );

		void draw( AGDXSurface* surface );

	private:
		float intersect( AGDXPrimitive* primitive, D3DXVECTOR3 rayOrigin, D3DXVECTOR3 rayDir );

		AGDXCircle* m_xCircle; 
		AGDXCircle* m_yCircle; 
		AGDXCircle* m_zCircle; 

		AGDXGizmo* m_selectedObject; 

		AGObject* m_object; 
		AGDXLine* m_tangentLine; 
};


#endif 