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

		D3DXVECTOR3 getAxis(); 
		D3DXVECTOR3 getTangent(); 
	private:
		ID3D10EffectVectorVariable* m_cameraPosVar; 

		int m_nIndices; 
		int m_nBoundIndices; 
		CircleAxis m_axis; 
		ID3D10DepthStencilState* m_depthState; 
		ID3DX10Font* m_font; 
		//AGDXBoundingBox* m_boundingBox;
		vector< AGColorVertex > m_vertices;
		vector< int > m_indices; 
		vector< D3DXVECTOR3 > m_tangents; 
		D3DXVECTOR3 m_tangent; 
};


#endif 