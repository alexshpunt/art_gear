#ifndef AGDX10_PRIMITIVE_H
#define AGDX10_PRIMITIVE_H

#include <d3dx10.h>
#include <d3d10.h>

#include "Math/AGPoint3.h"

class AGDX10Camera;

struct AGColorVertex 
{
	D3DXVECTOR3 pos;
	D3DXVECTOR4 color; 
};

class AGDX10Primitive 
{
	public:
		AGDX10Primitive( ID3D10Device* device );
		virtual ~AGDX10Primitive();

		virtual void draw( ID3D10Device* device, AGDX10Camera* camera ) = 0;
		//Если возвращаемое значение < 0, значит, что луч не коснулся сетки примитива, иначе это дистанция 
		virtual float intersect( D3DXVECTOR3 rayOrigin, D3DXVECTOR3 rayDir ) = 0;

	protected:
		ID3D10InputLayout* m_inputLayout; 

		ID3D10Effect* m_effect;
		ID3D10EffectTechnique* m_technique; 

		ID3D10EffectMatrixVariable* m_worldVar; 
		ID3D10EffectMatrixVariable* m_viewVar;
		ID3D10EffectMatrixVariable* m_projectionVar;

		D3DXMATRIX m_world;
		D3DXMATRIX m_view;
		D3DXMATRIX m_proj; 
		
		ID3D10Buffer* m_vertexBuffer; 
		ID3D10Buffer* m_indexBuffer; 
};

#endif 