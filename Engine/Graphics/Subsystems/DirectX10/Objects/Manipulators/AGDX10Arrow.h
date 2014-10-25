#ifndef AGDX10_ARROW_H
#define AGDX10_ARROW_H

#include "Graphics/Subsystems/DirectX10/Objects/AGDX10Primitive.h"

class AGDX10Arrow : public AGDX10Primitive 
{
	public:
		enum ArrowAxis{ X_AXIS, Y_AXIS, Z_AXIS };
		AGDX10Arrow( ID3D10Device* device, ArrowAxis axis );
		~AGDX10Arrow();

		void draw( ID3D10Device* device, AGDX10Camera* camera );
		float intersect( D3DXVECTOR3 rayOrigin, D3DXVECTOR3 rayDir );
	private:
		int m_nIndices; 
		ArrowAxis m_axis; 
		ID3D10DepthStencilState* m_depthState; 
};

#endif 