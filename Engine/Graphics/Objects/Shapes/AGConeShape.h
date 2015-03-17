#ifndef AG_CONESHAPE_H
#define AG_CONESHAPE_H

#include <vector>

#include <Engine/Graphics/Interfaces/AGPrimitive.h>
#include <Engine/Graphics/Objects/AGGizmo.h>

using namespace std;

class AGConeShape : public AGPrimitive
{
	public:
		AGConeShape( D3DXVECTOR4 color = D3DXVECTOR4( 1.0f, 1.0f, 1.0f, 1.0f ), float radius = 1.0f, float height = 1.0f );
		~AGConeShape();

		virtual void draw(  AGSurface* surface  );

		void setRadius( float radius );
		float getRadius() const; 

		void setHeight( float height );
		float getHeight() const; 

		void setColor( D3DXVECTOR4 color );
		D3DXVECTOR4 getColor() const; 

		void setupShape();
		
	private:
		D3DXVECTOR4 m_color; 
		float m_radius;
		float m_height; 

		int m_nIndices; 
		vector< AGPrimitiveVertex > m_vertices;
		vector< int > m_indices; 
};

#endif 