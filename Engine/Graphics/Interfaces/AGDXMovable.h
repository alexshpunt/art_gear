#ifndef AGDX_MOVABLE_H
#define AGDX_MOVABLE_H

#include <d3dx10.h>
#include <d3d10.h>

/*
 * Класс, который помогает реализовывать передвигаемые объекты, содержит методы необходимые для изменения положения объектов в пространстве
 */
class AGDXMovable 
{
	public:
		AGDXMovable();
		virtual ~AGDXMovable(); 

		void setPos( D3DXVECTOR3 pos );
		void setPos( float x, float y, float z );
		D3DXVECTOR3 getPos() const;

		void translate( D3DXVECTOR3 pos );
		void translate( float x, float y, float z );

		void setAngle( D3DXVECTOR3 angle );
		void setAngle( float x, float y, float z );
		D3DXVECTOR3 getAngle() const; 

		void rotate( D3DXVECTOR3 angle );
		void rotate( float x, float y, float z );

		void setScale( D3DXVECTOR3 factor );
		void setScale( float x, float y, float z ); 
		D3DXVECTOR3 getScale() const; 

		void scale( D3DXVECTOR3 factor ); 
		void scale( float x, float y, float z );

		void setWorld( D3DXMATRIX world );
		D3DXMATRIX getWorld();

	private:
		D3DXVECTOR3 m_pos;
		D3DXVECTOR3 m_angle;
		D3DXVECTOR3 m_scale; 

		D3DXMATRIX m_translMatrix;
		D3DXMATRIX m_rotMatrix;
		D3DXMATRIX m_scaleMatrix; 

		D3DXMATRIX m_world;

		bool m_updateMatrix; 
};

#endif 