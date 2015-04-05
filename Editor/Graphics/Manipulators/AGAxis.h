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
		float intersect( D3DXVECTOR3 rayOrigin, D3DXVECTOR3 rayDir );

		D3DXVECTOR3 getAxis(); 
	private:
		int m_nIndices; 
		
		AGShader* m_shader; 

		AGGameObject* m_object; 
};

#endif 