#ifndef AG_CYLINDERSHAPE_H
#define AG_CYLINDERSHAPE_H

#include "AGShape.h"

#include "Engine/Math/AGMath.h"

class AGCylinderShapePrivate; 

class AGCylinderShape : public AGShape
{
	public:	
		AGCylinderShape( float radius = 1.0f, float height = 1.0f, const AGColor& color = AGColor( 1.0f ) ); 
		~AGCylinderShape();

		void draw( AGSurface* surface );

		void setRadius( float radius );
		float getRadius() const;

		void setHeight( float height );
		float getHeight() const;

		void setSize( float radius, float height );
		void setSize( const AGSize& size );
		const AGSize& getSize() const; 

		void setupShape(); 

	private:
		AGCylinderShapePrivate* p; 
};

#endif 