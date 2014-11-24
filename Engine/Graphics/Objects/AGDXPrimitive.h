#ifndef AGDX_PRIMITIVE_H
#define AGDX_PRIMITIVE_H

#include <d3dx10.h>
#include <d3d10.h>

#include "Graphics/Interfaces/AGDXMovable.h"

class AGDXSurface;

struct AGColorVertex 
{
	D3DXVECTOR3 pos;
	D3DXVECTOR4 color; 
};

struct AGDXIntersectedTriangle
{
	D3DXVECTOR3 v1;
	D3DXVECTOR3 v2;
	D3DXVECTOR3 v3; 
	float dist; 
};

class AGDXPrimitive : public AGDXMovable
{
	public:
		AGDXPrimitive( ID3D10Device* device );
		virtual ~AGDXPrimitive();

		virtual void draw( AGDXSurface* surface ) = 0;
		//Если возвращаемое значение < 0, значит, что луч не коснулся сетки примитива, иначе это дистанция 
		virtual float intersect( D3DXVECTOR3 rayOrigin, D3DXVECTOR3 rayDir ) = 0;

	protected:
		ID3D10InputLayout* m_inputLayout; 

		ID3D10Effect* m_effect;
		ID3D10EffectTechnique* m_technique; 

		ID3D10EffectMatrixVariable* m_worldVar; 
		ID3D10EffectMatrixVariable* m_viewVar;
		ID3D10EffectMatrixVariable* m_projectionVar;
		
		ID3D10Buffer* m_vertexBuffer; 
		ID3D10Buffer* m_additionalVB; 
		ID3D10Buffer* m_indexBuffer; 
};

#endif 