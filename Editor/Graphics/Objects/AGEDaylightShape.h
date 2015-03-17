#ifndef AGE_SKYLIGHTSHAPE_H
#define AGE_SKYLIGHTSHAPE_H

#include "Engine/Graphics/Interfaces/AGPrimitive.h"

#include "Engine/Math/AGMath.h"

class AGEDaylightShape : public AGPrimitive
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

		void setColor( float r, float g, float b, float a = 1.0f );
		void setColor( int r, int g, int b, int a = 255 );
		void setColor( const AGColor& color );

		const AGColor& getColor() const; 

		void setup(); 

	private:
		AGColor m_color; 
		AGSize m_size; 

		int m_nIndices; 
		vector< AGPrimitiveVertex > m_vertices;
		vector< int > m_indices; 
};

#endif 