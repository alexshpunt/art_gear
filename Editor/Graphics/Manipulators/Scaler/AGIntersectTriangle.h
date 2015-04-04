#ifndef AG_INTERSECTTRIANGLE_H
#define AG_INTERSECTTRIANGLE_H

#include <map>

#include "Engine/Graphics/Objects/AGGizmo.h"
#include "Engine/Graphics/Objects/AGBoundingBox.h"

class AGArrow; 

class AGIntersectTriangle : public AGGizmo
{
	public:
		enum TriangleAxis{ XZ_AXIS, YZ_AXIS, XY_AXIS, XYZ_AXIS };
		AGIntersectTriangle( TriangleAxis axis );
		~AGIntersectTriangle();

		void setArrows( AGArrow* arrow1, AGArrow* arrow2 );

		void draw(  AGSurface* surface  );
		float intersect( D3DXVECTOR3 rayOrigin, D3DXVECTOR3 rayDir );

		D3DXVECTOR3 getAxis();
	private:
		std::map< ID3D10Device* , ID3D10DepthStencilState* > m_depthState; 
		TriangleAxis m_axis;
		D3DXVECTOR3 m_vertices[ 9 ]; 

		AGArrow* m_arrow1; 
		AGArrow* m_arrow2; 
};

#endif 