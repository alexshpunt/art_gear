#ifndef AGDX_BOUNDINGBOX_H
#define AGDX_BOUNDINGBOX_H

#include <d3dx10.h>
#include <d3d10.h>

#include "AGDXPrimitive.h"
#include "Math/AGPoint3.h"

class AGDXCamera;

class AGDXBoundingBox  : public AGDXPrimitive
{
	public:
		//V1 - конец диагонали, V2 - начало диагонали 
		AGDXBoundingBox( D3DXVECTOR3 v1, D3DXVECTOR3 v2, ID3D10Device* device );
		~AGDXBoundingBox();

		void draw( AGDXSurface* surface );
		//Если возвращаемое значение < 0, значит, что луч не коснулся коробки, иначе это дистанция 
		float intersect( D3DXVECTOR3 rayOrigin, D3DXVECTOR3 rayDir );

	private:
		int m_indices[ 36 ];
		D3DXVECTOR3 m_vertices[ 8 ]; 
};

#endif 