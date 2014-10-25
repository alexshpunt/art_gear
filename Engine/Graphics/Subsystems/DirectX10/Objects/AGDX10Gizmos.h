#ifndef AGDX10_GIZMOS_H
#define AGDX10_GIZMOS_H

#include "AGDX10Primitive.h"

class AGDX10PosGizmo : public AGDX10Primitive
{
	public:
		AGDX10PosGizmo( ID3D10Device* device );
		~AGDX10PosGizmo();

		void draw(  ID3D10Device* device, AGDX10Camera* camera );
		float intersect( D3DXVECTOR3 rayOrigin, D3DXVECTOR3 rayDir );

	private:
	 
};

#endif 