#ifndef AG_CIRCLESHAPE_H
#define AG_CIRCLESHAPE_H

#include <vector>

#include "Engine/Graphics/Interfaces/AGPrimitive.h"
#include "Engine/Graphics/AGInputLayouts.h"

#include "AGShape.h"

#include "Engine/Math/AGMath.h"

using namespace std;

class AGCircleShapePrivate; 

class AGCircleShape : public AGShape
{
	public:
		AGCircleShape( float radius = 1.0f, const AGColor& color = AGColor( 1.0f ) );
		~AGCircleShape();

		void draw(  AGSurface* surface  ) override;

		void setRadius( float radius );
		float getRadius() const; 

		void setupShape() override;
		
	private:
		AGCircleShapePrivate* p; 
};

#endif 