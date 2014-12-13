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

		void setLocalPos( D3DXVECTOR3 pos );
		void setLocalPos( float x, float y, float z );
		D3DXVECTOR3 getLocalPos() const;

		void setWorldPos( D3DXVECTOR3 pos );
		void setWorldPos( float x, float y, float z );
		D3DXVECTOR3 getWorldPos() const;

		void translateLocal( D3DXVECTOR3 pos );
		void translateLocal( float x, float y, float z );

		void translateWorld( D3DXVECTOR3 pos );
		void translateWorld( float x, float y, float z );

		void setLocalAngle( D3DXVECTOR3 angle );
		void setLocalAngle( float x, float y, float z );
		D3DXVECTOR3 getLocalAngle() const; 

		void setWorldAngle( D3DXVECTOR3 angle );
		void setWorldAngle( float x, float y, float z );
		D3DXVECTOR3 getWorldAngle() const; 

		void rotateLocal( D3DXVECTOR3 angle );
		void rotateLocal( float x, float y, float z );

		void rotateWorld( D3DXVECTOR3 angle );
		void rotateWorld( float x, float y, float z );

		void setLocalScale( D3DXVECTOR3 factor );
		void setLocalScale( float x, float y, float z ); 
		D3DXVECTOR3 getLocalScale() const; 

		void setWorldScale( D3DXVECTOR3 factor );
		void setWorldScale( float x, float y, float z ); 
		D3DXVECTOR3 getWorldScale() const; 

		void scaleLocal( D3DXVECTOR3 factor ); 
		void scaleLocal( float x, float y, float z );

		void scaleWorld( D3DXVECTOR3 factor ); 
		void scaleWorld( float x, float y, float z );

		void setLocalMatrix( D3DXMATRIX world );
		D3DXMATRIX getLocalMatrix();
		D3DXMATRIX getLocalTranslMatrix();
		D3DXMATRIX getLocalRotMatrix();
		D3DXMATRIX getLocalScaleMatrix();

		void setWorldMatrix( D3DXMATRIX world );
		D3DXMATRIX getWorldMatrix();
		D3DXMATRIX getWorldTranslMatrix();
		D3DXMATRIX getWorldRotMatrix();
		D3DXMATRIX getWorldScaleMatrix(); 

		void setResultMatrix( D3DXMATRIX world );
		D3DXMATRIX getResultMatrix(); 

	private:
		D3DXVECTOR3 m_localPos;
		D3DXVECTOR3 m_localAngle;
		D3DXVECTOR3 m_localScale; 
	
		D3DXVECTOR3 m_worldPos;
		D3DXVECTOR3 m_worldAngle;
		D3DXVECTOR3 m_worldScale; 

		D3DXMATRIX m_localTranslMatrix;
		D3DXMATRIX m_localRotMatrix;
		D3DXMATRIX m_localScaleMatrix; 

		D3DXMATRIX m_worldTranslMatrix;
		D3DXMATRIX m_worldRotMatrix;
		D3DXMATRIX m_worldScaleMatrix; 

		D3DXMATRIX m_local;
		D3DXMATRIX m_world;
		D3DXMATRIX m_matrix; 

		bool m_updateLocalMatrix; 
		bool m_updateWorldMatrix; 
		bool m_updateResMatrix; 
};

#endif 