#ifndef AG_BOXSHAPE_H
#define AG_BOXSHAPE_H

#include "AGShape.h"

#include "Engine/Math/AGMath.h"

class AGBoxShapePrivate;

class AGBoxShape : public AGShape
{
	public:
		AGBoxShape( float side = 1.0f, const AGColor& color = AGColor( 1.0f ) ); 
		AGBoxShape( float lenght, float width, float height, const AGColor& color = AGColor( 1.0f ) );

		~AGBoxShape(); 

		void draw( AGSurface* surface ) override;
		float intersect( const AGVec3& rayOrigin, const AGVec3& rayDir ) override;

		void setSide( float side );

		void setSize( float length, float width, float height );

		void setWidth( float width );
		float getWidth() const;

		void setHeight( float height );
		float getHeight() const;

		void setLength( float length );
		float getLength() const; 

		void setupShape();

	private:
		AGBoxShapePrivate* p; 
};

#endif 