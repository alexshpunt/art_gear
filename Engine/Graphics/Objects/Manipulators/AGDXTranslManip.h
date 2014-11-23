#ifndef AGDX_TRANSLMANIP_H
#define AGDX_TRANSLMANIP_H

#include <d3dx10.h>
#include <d3d10.h>
#include <string>

class AGObject; 
class AGDXPrimitive;
class AGDXArrow; 
class AGDXSurface; 
class AGDXGizmo; 
class AGDXIntersectPlane; 
class AGDXCircle; 

using namespace std; 

class AGDXDragger 
{
	public:
		AGDXDragger( ID3D10Device* device );
		~AGDXDragger();

		void setObject( AGObject* object );
		AGObject* getObject() const; 

		void mouseClickEvent( const string& btn, AGDXSurface* surface );
		void mouseMoveEvent( AGDXSurface* surface );

		void draw( AGDXSurface* surface );

	private:
		float intersect( AGDXPrimitive* primitive, D3DXVECTOR3 rayOrigin, D3DXVECTOR3 rayDir );

		AGDXArrow* m_xArrow;
		AGDXArrow* m_yArrow; 
		AGDXArrow* m_zArrow; 

		AGDXIntersectPlane* m_xyPlane;
		AGDXIntersectPlane* m_xzPlane;
		AGDXIntersectPlane* m_yzPlane;

		AGDXCircle* m_circle; 

		AGDXGizmo* m_selectedObject; 

		AGObject* m_object; 
};

#endif 