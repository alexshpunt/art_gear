#ifndef AG_PRIMITIVE_H
#define AG_PRIMITIVE_H

#include <vector>

#include <Engine/Graphics/Objects/AGBuffer.h>
#include <Engine/Graphics/Objects/AGShader.h>

#include "AGMovable.h"
#include "AGSurface.h"
#include "AGPureInterfaces.h"

#include "Engine/Math/AGMath.h"

using namespace std;

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