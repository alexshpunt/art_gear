#ifndef AG_CONESHAPE_H
#define AG_CONESHAPE_H

#include <vector>

#include <Engine/Graphics/Interfaces/AGPrimitive.h>
#include "AGShape.h"
#include <Engine/Graphics/Objects/AGGizmo.h>

#include "Engine/Math/AGMath.h"

#include "Engine/Graphics/AGInputLayouts.h"

using namespace std;

class AGConeShapePrivate; 

class AGConeShape : public AGShape
{
	public:
		AGConeShape( float radius = 1.0f, float height = 1.0f, const AGColor& color = AGColor( 1.0f ) );
		~AGConeShape();

		void draw(  AGSurface* surface  ) override;

		void setRadius( float radius );
		float getRadius() const; 

		void setHeight( float height );
		float getHeight() const; 

		void setupShape() override;
		
	private:
		AGConeShapePrivate* p; 
};

#endif 