#ifndef AGDX_INTERSECTTRIANGLE_H
#define AGDX_INTERSECTTRIANGLE_H

#include "Graphics/Objects/AGDXGizmo.h"
#include "Graphics/Objects/AGDXBoundingBox.h"

class AGDXArrow; 

class AGDXIntersectTriangle : public AGDXGizmo
{
	public:
		enum TriangleAxis{ XZ_AXIS, YZ_AXIS, XY_AXIS, XYZ_AXIS };
		AGDXIntersectTriangle( ID3D10Device* device, TriangleAxis axis );
		~AGDXIntersectTriangle();

		void setArrows( AGDXArrow* arrow1, AGDXArrow* arrow2 );

		void draw(  AGDXSurface* surface  );
		float intersect( D3DXVECTOR3 rayOrigin, D3DXVECTOR3 rayDir );

		D3DXVECTOR3 getAxis();
	private:
		ID3D10DepthStencilState* m_depthState; 
		TriangleAxis m_axis;
		D3DXVECTOR3 m_vertices[ 9 ]; 

		AGDXArrow* m_arrow1; 
		AGDXArrow* m_arrow2; 
};

#endif 