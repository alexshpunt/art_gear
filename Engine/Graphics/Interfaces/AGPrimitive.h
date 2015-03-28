#ifndef AG_PRIMITIVE_H
#define AG_PRIMITIVE_H

#include "Engine/Interfaces/AGMovable.h"

#include "AGPureInterfaces.h"

#include "Engine/Graphics/Objects/AGBuffer.h"
#include "Engine/Graphics/Objects/AGShader.h"

#include "Engine/Math/AGMath.h"

struct AGPrimitiveVertex 
{
	AGVec3 pos;
	AGColor color; 
};

class AGPrimitive :  public AGMovable, public AGDrawable
{
	public:
		AGPrimitive();
		virtual ~AGPrimitive();

	protected:
		AGBuffer< int >* m_indexBuffer;
		AGBuffer< AGPrimitiveVertex >* m_vertexBuffer; 
		
		AGShader* m_shader; 
};

#endif 