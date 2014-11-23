#ifndef AGDX_LINE_H
#define AGDX_LINE_H

#include <d3dx10.h>
#include <d3d10.h>

#include "AGDXPrimitive.h"

class AGDXLine : public AGDXPrimitive
{
	public:
		AGDXLine( ID3D10Device* device, float length, D3DXVECTOR4 color );
		~AGDXLine();

		void draw( AGDXSurface* surface );
		float intersect( D3DXVECTOR3 rayOrigin, D3DXVECTOR3 rayDir );
};

#endif 