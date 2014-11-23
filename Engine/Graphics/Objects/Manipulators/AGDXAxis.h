#ifndef AGDX_AXIS_H
#define AGDX_AXIS_H

#include "Graphics/Objects/AGDXPrimitive.h"

class AGObject; 

class AGDXAxises : public AGDXPrimitive 
{
	public:
		AGDXAxises( ID3D10Device* device );
		~AGDXAxises();

		void setObject( AGObject* object );
		AGObject* getObject() const; 

		void draw( AGDXSurface* surface );
		float intersect( D3DXVECTOR3 rayOrigin, D3DXVECTOR3 rayDir );

		D3DXVECTOR3 getAxis(); 
	private:
		int m_nIndices; 
		ID3D10DepthStencilState* m_depthState; 
		AGObject* m_object; 
		ID3DX10Font* m_font; 
};

#endif 