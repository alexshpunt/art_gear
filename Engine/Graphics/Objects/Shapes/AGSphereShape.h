#ifndef AG_SPHERESHAPE_H
#define AG_SPHERESHAPE_H

#include "Engine/Math/AGColor.h"

#include "Engine/Graphics/Interfaces/AGPrimitive.h"

class AGSphereShapePrivate; 

class AGSphereShape : public AGPrimitive
{
	public:
		AGSphereShape( float radius = 1.0f, const AGColor& color = AGColor( 1.0f ) );
		~AGSphereShape();

		void setRadius( float radius );
		float getRadius() const;

		void setColor( const AGColor& color );
		const AGColor& getColor() const; 

		void draw( AGSurface* surface ); 

		void setup(); 
	private:
		AGSphereShapePrivate* m_p; 
};

#endif 