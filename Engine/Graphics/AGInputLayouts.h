#ifndef AG_INPUTLAYOUTS_H
#define AG_INPUTLAYOUTS_H

#include <d3dx10.h>
#include <d3d10.h>

struct AGInputLayout
{
	ID3D10InputLayout* vertexInputLayout;
	ID3D10InputLayout* colorVertexInputLayout; 
	ID3D10InputLayout* simpleVertexInputLayout; 
	ID3D10InputLayout* textureVertexInputLayout; 
	ID3D10InputLayout* billboardVertexInputLayout; 
};

struct AGVertex 
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 normal;
	D3DXVECTOR3 binormal;
	D3DXVECTOR3 tangent; 
	D3DXVECTOR2 uv; 
};

struct AGColorVertex 
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 color; 
};

struct AGTextureVertex 
{
	D3DXVECTOR3 pos;
	D3DXVECTOR2 uv; 
};

struct AGSimpleVertex 
{
	D3DXVECTOR3 pos; 
};

struct AGBillboardVertex
{
	D3DXVECTOR3 pos;
	D3DXVECTOR2 size; 
};

#endif 