#ifndef AG_SHAPE_H
#define AG_SHAPE_H

#include "Engine/Math/AGMath.h"

#include "Engine/Graphics/Interfaces/AGPrimitive.h"

class AGShape : public AGPrimitive
{
	public:
		explicit AGShape( const AGColor& color =  AGColor( 1.0f ) ); 
		virtual ~AGShape();

		void setColor( const AGColor& color );
		const AGColor& getColor() const; 

		virtual void setupShape() = 0; 
	protected:
		virtual void prepareDraw( AGSurface* surface ); 
		AGBuffer< AGColorVertex >* m_vertexBuffer;
		AGColor m_color; 
};

#endif 