#ifndef AG_ARROW_H
#define AG_ARROW_H

#include <vector>

#include "Engine/Graphics/Objects/AGGizmo.h"
#include "Engine/Graphics/Objects/AGBoundingBox.h"

using namespace std;

class AGCubeArrow : public AGGizmo
{
	public:
		enum CubeArrowAxis{ X_AXIS, Y_AXIS, Z_AXIS };
		AGCubeArrow( CubeArrowAxis axis );
		~AGCubeArrow();

		void draw(  AGSurface* surface  );
		float intersect( D3DXVECTOR3 rayOrigin, D3DXVECTOR3 rayDir );

		D3DXVECTOR3 getAxis(); 
	private:
		int m_nIndices; 
		CubeArrowAxis m_axis; 
		ID3D10DepthStencilState* m_depthState; 
		ID3DX10Font* m_font; 
		AGBoundingBox* m_boundingBox;
		vector< AGPrimitiveVertex > m_vertices;
		vector< int > m_indices; 
		D3DXVECTOR3 m_axisDir; 
};

#endif 