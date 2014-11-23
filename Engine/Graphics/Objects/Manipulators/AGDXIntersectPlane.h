#ifndef AGDX_INTERSECTPLANE_H
#define AGDX_INTERSECTPLANE_H

#include "Graphics/Objects/AGDXGizmo.h"
#include "Graphics/Objects/AGDXBoundingBox.h"

class AGDXArrow; 

class AGDXIntersectPlane : public AGDXGizmo
{
	public:
		enum PlaneAxis{ XZ_AXIS, YZ_AXIS, XY_AXIS };
		AGDXIntersectPlane( ID3D10Device* device, PlaneAxis axis );
		~AGDXIntersectPlane();

		void setArrows( AGDXArrow* arrow1, AGDXArrow* arrow2 );

		void draw(  AGDXSurface* surface  );
		float intersect( D3DXVECTOR3 rayOrigin, D3DXVECTOR3 rayDir );

		D3DXVECTOR3 getAxis();
	private:
		ID3D10DepthStencilState* m_depthState; 
		PlaneAxis m_axis;
		D3DXVECTOR3 m_vertices[ 6 ]; 

		AGDXArrow* m_arrow1; 
		AGDXArrow* m_arrow2; 
};

#endif 