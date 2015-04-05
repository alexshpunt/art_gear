#ifndef AG_SPHERESHAPE_H
#define AG_SPHERESHAPE_H

#include "AGShape.h"

#include "Engine/Math/AGMath.h"

class AGSphereShapePrivate; 

class AGSphereShape : public AGShape
{
	public:
		AGSphereShape( float radius = 1.0f, const AGColor& color = AGColor( 1.0f ) );
		~AGSphereShape();

		void setRadius( float radius );
		float getRadius() const;

		void draw( AGSurface* surface ); 

		void setupShape(); 
	private:
		AGSphereShapePrivate* p; 
};

#endif 