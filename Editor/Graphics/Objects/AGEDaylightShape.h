#ifndef AGE_SKYLIGHTSHAPE_H
#define AGE_SKYLIGHTSHAPE_H

#include "Engine/Graphics/Objects/Shapes/AGShape.h"

#include "Engine/Math/AGMath.h"

class AGEDaylightShape : public AGShape
{
	public:	
		AGEDaylightShape( float radius = 1.0f, float height = 1.0f, const AGColor& color = AGColor( 1.0f ) ); 
		~AGEDaylightShape();

		void draw( AGSurface* surface );

		void setRadius( float radius );
		float getRadius() const;

		void setHeight( float height );
		float getHeight() const;

		void setSize( float radius, float height );
		void setSize( const AGSize& size );
		const AGSize& getSize() const; 

		void setColor( const AGColor& color );
		const AGColor& getColor() const; 

		void setupShape(); 

	private:
		AGColor m_color; 
		AGSize m_size; 

		vector< AGPrimitiveVertex > m_vertices;
};

#endif 