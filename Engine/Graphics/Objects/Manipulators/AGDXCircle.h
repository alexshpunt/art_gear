#ifndef AGDX_CIRCLE_H
#define AGDX_CIRCLE_H

#include <vector>

#include "Graphics/Objects/AGDXGizmo.h"

using namespace std;

class AGDXCircle : public AGDXGizmo
{
	public:
		enum CircleAxis{ X_AXIS, Y_AXIS, Z_AXIS };
		AGDXCircle( ID3D10Device* device, CircleAxis axis );
		~AGDXCircle();

		void draw(  AGDXSurface* surface  );
		float intersect( D3DXVECTOR3 rayOrigin, D3DXVECTOR3 rayDir );
		AGDXIntersectedTriangle getIntersectedTriangle( D3DXVECTOR3 rayOrigin, D3DXVECTOR3 rayDir );

		D3DXVECTOR3 getAxis(); 
	private:
		int m_nIndices; 
		CircleAxis m_axis; 
		ID3D10DepthStencilState* m_depthState; 
		ID3DX10Font* m_font; 
		//AGDXBoundingBox* m_boundingBox;
		vector< AGColorVertex > m_vertices;
		vector< int > m_indices; 
};


#endif 