#ifndef AG_MOVABLE_H
#define AG_MOVABLE_H

#include <d3dx10.h>
#include <d3d10.h>

/*
 * Класс, который помогает реализовывать передвигаемые объекты, содержит методы необходимые для изменения положения объектов в пространстве
 */
class AGMovable 
{
	public:
		enum Changes{ World, WorldTrans, WorldRot, WorldScale, Local, LocalTrans, LocalRot, LocalScale };

		AGMovable();
		virtual ~AGMovable(); 

		void setPivot( D3DXVECTOR3 pivot );
		void setPivot( float x, float y, float z );
		D3DXVECTOR3 getPivot();

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

		void rotateLocalAxis( D3DXVECTOR3 axis, float angle );
		void rotateLocalX( float angle );
		void rotateLocalY( float angle );
		void rotateLocalZ( float angle );
		void rotateLocal( D3DXVECTOR3 angle );
		void rotateLocal( float x, float y, float z );

		void rotateWorldAxis( D3DXVECTOR3 axis, float angle );

		//Здесь, вращение вокруг мировой координаты значит, что сама мировая ось объекта не меняется
		//как это происходит в мировом вращении
		void rotateAroundWorldX( float angle );
		void rotateAroundWorldY( float angle );
		void rotateAroundWorldZ( float angle );
		
		//Rotate around "parent" axis
		void rotateWorldX( float angle );
		void rotateWorldY( float angle );
		void rotateWorldZ( float angle );
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

		void setLocalTranslMatrix( D3DXMATRIX transl );
		D3DXMATRIX getLocalTranslMatrix();

		void setLocalRotMatrix( D3DXMATRIX rot );
		D3DXMATRIX getLocalRotMatrix();

		void setLocalScaleMatrix( D3DXMATRIX scale );
		D3DXMATRIX getLocalScaleMatrix();

		void setWorldMatrix( D3DXMATRIX world );
		D3DXMATRIX getWorldMatrix();

		void setWorldTranslMatrix( D3DXMATRIX transl ); 
		D3DXMATRIX getWorldTranslMatrix();

		void setWorldRotMatrix( D3DXMATRIX rot ); 
		D3DXMATRIX getWorldRotMatrix();

		void setWorldScaleMatrix( D3DXMATRIX scale ); 
		D3DXMATRIX getWorldScaleMatrix(); 

		void setResultMatrix( D3DXMATRIX world );
		D3DXMATRIX getResultMatrix(); 

		void setLookAt( D3DXVECTOR3 dir ){}
	protected:
		virtual void handleChanges( Changes changes ); 

	private:
		D3DXVECTOR3 m_pivot; 
		D3DXMATRIX m_pivotMatrix; 

		D3DXVECTOR3 m_pos; 
		D3DXMATRIX m_translMatrix;
		D3DXVECTOR3 m_rot;
		D3DXMATRIX m_rotMatrix; 

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