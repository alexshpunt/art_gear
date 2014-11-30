#ifndef AGDX_SCALER_H
#define AGDX_SCALER_H

#include <d3dx10.h>
#include <d3d10.h>
#include <string>

class AGObject; 
class AGDXPrimitive;
class AGDXCubeArrow; 
class AGDXSurface; 
class AGDXGizmo; 
class AGDXIntersectTriangle; 
class AGDXCircle; 

using namespace std; 

class AGDXScaler 
{
	public:
		AGDXScaler( ID3D10Device* device );
		~AGDXScaler();

		void setObject( AGObject* object );
		AGObject* getObject() const; 

		void mouseClickEvent( const string& btn, AGDXSurface* surface );
		void mouseMoveEvent( AGDXSurface* surface );

		void draw( AGDXSurface* surface );

	private:
		float intersect( AGDXPrimitive* primitive, D3DXVECTOR3 rayOrigin, D3DXVECTOR3 rayDir );

		AGDXCubeArrow* m_xArrow;
		AGDXCubeArrow* m_yArrow; 
		AGDXCubeArrow* m_zArrow; 

		AGDXIntersectTriangle* m_xyPlane;
		AGDXIntersectTriangle* m_xzPlane;
		AGDXIntersectTriangle* m_yzPlane;
		AGDXIntersectTriangle* m_xyzPlane;

		AGDXGizmo* m_selectedObject; 

		AGObject* m_object; 
};

#endif 