#ifndef AG_CIRCLE_H
#define AG_CIRCLE_H

#include <vector>

#include "Engine/Graphics/Objects/AGGizmo.h"

using namespace std;

class AGCircle : public AGGizmo
{
	public:
		enum CircleAxis{ X_AXIS, Y_AXIS, Z_AXIS };
		AGCircle( CircleAxis axis );
		~AGCircle();

		void draw(  AGSurface* surface  );
		float intersect( D3DXVECTOR3 rayOrigin, D3DXVECTOR3 rayDir );

		D3DXVECTOR3 getAxis(); 
		D3DXVECTOR3 getTangent(); 
	private:
		ID3D10EffectVectorVariable* m_cameraPosVar; 
		ID3D10EffectScalarVariable* m_fadingVar;

		int m_nIndices; 
		int m_nBoundIndices; 
		CircleAxis m_axis; 
		ID3D10DepthStencilState* m_depthState; 
		ID3DX10Font* m_font; 
		vector< AGPrimitiveVertex > m_vertices;
		vector< int > m_indices; 
		vector< D3DXVECTOR3 > m_tangents; 
		D3DXVECTOR3 m_tangent; 
		
		AGBuffer< AGPrimitiveVertex >* m_additionalVB; 
};


#endif 