#ifndef AG_INPUTLAYOUTS_H
#define AG_INPUTLAYOUTS_H

#include <d3dx10.h>
#include <d3d10.h>

#include "Engine/Math/AGMath.h"

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
	AGVec3 pos;
	AGVec3 normal;
	AGVec3 binormal;
	AGVec3 tangent; 
	AGVec2 uv; 
};

struct AGColorVertex 
{
	AGVec3 pos;
	AGVec3 color; 
};

struct AGTextureVertex 
{
	AGVec3 pos;
	AGVec2 uv; 
};

struct AGSimpleVertex 
{
	AGVec3 pos; 
};

struct AGBillboardVertex
{
	AGVec3 pos;
	AGSize size; 
};

#endif 