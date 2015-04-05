#ifndef AG_BOXSHAPE_H
#define AG_BOXSHAPE_H

#include <Engine/Graphics/Interfaces/AGPrimitive.h>
#include "Graphics/Objects/AGGizmo.h"

/*class AGBoxShape : public AGPrimitive
{
	public:
		AGBoxShape();
		AGBoxShape( float lenght, float width, float height, D3DXVECTOR4 color = D3DXVECTOR4( 1.0f, 1.0f, 1.0f, 1.0f ) );
		AGBoxShape( float side, D3DXVECTOR4 color = D3DXVECTOR4( 1.0f, 1.0f, 1.0f, 1.0f ) ); 

		~AGBoxShape(); 

		void draw( AGSurface* surface );
		float intersect( D3DXVECTOR3 rayOrigin, D3DXVECTOR3 rayDir );

		void setSide( float side );
		
		void setSize( float length, float width, float height );

		void setWidth( float width );
		float getWidth() const;

		void setHeight( float height );
		float getHeight() const;

		void setLength( float length );
		float getLength() const; 

		void setColor( D3DXVECTOR4 color );
		D3DXVECTOR4 getColor() const; 

		void setupShape();

		D3DXVECTOR3 getAxis(); 

	private:
		float m_length; 
		float m_width;
		float m_height; 

		int m_indices[ 36 ];
		D3DXVECTOR3 m_vertices[ 8 ];

		D3DXVECTOR4 m_color; 
};*/

#include "AGShape.h"

#include "Engine/Math/AGMath.h"

class AGBoxShapePrivate;

class AGBoxShape : public AGShape
{
	public:
		AGBoxShape( const AGVec3& v1, const AGVec3& v2, const AGColor& color = AGColor( 1.0f ) ); 
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