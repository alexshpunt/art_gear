#ifndef AGE_LIGHT_H
#define AGE_LIGHT_H

#include "Engine/Graphics/Interfaces/AGPureInterfaces.h"

class AGELightPrivate; 
class AGLight; 

class AGELight : public AGClickable
{
	public:
		AGELight(); 
		~AGELight(); 

		void draw( AGSurface* surface );
		float intersect( D3DXVECTOR3 rayOrigin, D3DXVECTOR3 rayDir );

		bool mouseMoveEvent( AGSurface* surface );
		bool mouseClickEvent(  AGMouseButton button, AGSurface* surface );

		AGLight* getLight() const; 

	private:
		AGELightPrivate* m_p;  
};

#endif 