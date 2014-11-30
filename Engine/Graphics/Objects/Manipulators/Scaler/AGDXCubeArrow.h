#ifndef AGDX_ARROW_H
#define AGDX_ARROW_H

#include <vector>

#include "Graphics/Objects/AGDXGizmo.h"
#include "Graphics/Objects/AGDXBoundingBox.h"

using namespace std;

class AGDXCubeArrow : public AGDXGizmo
{
	public:
		enum CubeArrowAxis{ X_AXIS, Y_AXIS, Z_AXIS };
		AGDXCubeArrow( ID3D10Device* device, CubeArrowAxis axis );
		~AGDXCubeArrow();

		void draw(  AGDXSurface* surface  );
		float intersect( D3DXVECTOR3 rayOrigin, D3DXVECTOR3 rayDir );

		D3DXVECTOR3 getAxis(); 
	private:
		int m_nIndices; 
		CubeArrowAxis m_axis; 
		ID3D10DepthStencilState* m_depthState; 
		ID3DX10Font* m_font; 
		AGDXBoundingBox* m_boundingBox;
		vector< AGColorVertex > m_vertices;
		vector< int > m_indices; 
};

#endif 