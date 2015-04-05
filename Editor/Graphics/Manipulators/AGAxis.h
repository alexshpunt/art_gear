#ifndef AG_AXIS_H
#define AG_AXIS_H

#include "Engine/Graphics/Interfaces/AGPrimitive.h"

#include <Engine/Graphics/Objects/AGShader.h>
#include <Engine/Managers/AGResourceManager.h>

class AGGameObject; 

class AGAxises : public AGPrimitive
{
	public:
		AGAxises();
		~AGAxises();

		void setObject( AGGameObject* object );
		AGGameObject* getObject() const; 

		void draw( AGSurface* surface );
		float intersect( const AGVec3& rayOrigin, const AGVec3& rayDir );

		AGVec3 getAxis(); 
	private:
		AGGameObject* m_object; 
};

#endif 