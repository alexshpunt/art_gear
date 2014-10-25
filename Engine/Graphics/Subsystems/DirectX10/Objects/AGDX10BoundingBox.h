#ifndef AGDX10_BOUNDINGBOX_H
#define AGDX10_BOUNDINGBOX_H

#include <d3dx10.h>
#include <d3d10.h>

#include "AGDX10Primitive.h"
#include "Math/AGPoint3.h"

class AGDX10Camera;

class AGDX10BoundingBox  : public AGDX10Primitive
{
	public:
		AGDX10BoundingBox( D3DXVECTOR3 v1, D3DXVECTOR3 v2, ID3D10Device* device );
		~AGDX10BoundingBox();

		void draw( ID3D10Device* device, AGDX10Camera* camera );
		//≈сли возвращаемое значение < 0, значит, что луч не коснулс€ коробки, иначе это дистанци€ 
		float intersect( D3DXVECTOR3 rayOrigin, D3DXVECTOR3 rayDir );

	private:
		int m_indices[ 36 ];
		D3DXVECTOR3 m_vertices[ 8 ]; 
};

#endif 