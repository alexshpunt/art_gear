#ifndef AG_INTERSECTPLANE_H
#define AG_INTERSECTPLANE_H

#include <map>

#include "Engine/Graphics/Objects/AGGizmo.h"
#include "Engine/Graphics/Objects/AGBoundingBox.h"

class AGArrow; 

class AGIntersectPlane : public AGGizmo
{
	public:
		enum PlaneAxis{ XZ_AXIS, YZ_AXIS, XY_AXIS };
		AGIntersectPlane( PlaneAxis axis );
		~AGIntersectPlane();

		void draw(  AGSurface* surface  );
		float intersect( D3DXVECTOR3 rayOrigin, D3DXVECTOR3 rayDir );

		D3DXVECTOR3 getAxis();
	private:
		std::map< ID3D10Device* , ID3D10DepthStencilState* > m_depthState; 
		PlaneAxis m_axis;
		D3DXVECTOR3 m_vertices[ 6 ]; 
};

#endif 