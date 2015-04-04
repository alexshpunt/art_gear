#ifndef AG_MOVABLE_H
#define AG_MOVABLE_H

#include <d3dx10.h>
#include <d3d10.h>

#include "Engine/Math/AGMath.h"

class AGMovablePrivate; 

class AGMovable 
{
	public:
		enum Changes{ World, WorldTrans, WorldRot, WorldScale, Local, LocalTrans, LocalRot, LocalScale };

		AGMovable();
		virtual ~AGMovable(); 

		void setPivot( const AGVec3& pivot );
		void setPivot( float x, float y, float z );
		const AGVec3& getPivot();

		void setLocalPos( const AGVec3& pos );
		void setLocalPos( float x, float y, float z );
		const AGVec3& getLocalPos() const;

		void setWorldPos( const AGVec3& pos );
		void setWorldPos( float x, float y, float z );
		const AGVec3& getWorldPos() const;

		void translateLocal( const AGVec3& pos );
		void translateLocal( float x, float y, float z );

		void translateWorld( const AGVec3& pos );
		void translateWorld( float x, float y, float z );

		void setLocalAngle( const AGVec3& angle );
		void setLocalAngle( float x, float y, float z );
		const AGVec3& getLocalAngle() const; 

		void setWorldAngle( const AGVec3& angle );
		void setWorldAngle( float x, float y, float z );
		const AGVec3& getWorldAngle() const; 

		void rotateLocalAxis( const AGVec3& axis, float angle );
		void rotateLocalX( float angle );
		void rotateLocalY( float angle );
		void rotateLocalZ( float angle );
		void rotateLocal( const AGVec3& angle );
		void rotateLocal( float x, float y, float z );

		void rotateWorldAxis( const AGVec3& axis, float angle );

		void rotateAroundWorldX( float angle );
		void rotateAroundWorldY( float angle );
		void rotateAroundWorldZ( float angle );
		
		//Rotate around "parent" axis
		void rotateWorldX( float angle );
		void rotateWorldY( float angle );
		void rotateWorldZ( float angle );
		void rotateWorld( const AGVec3& angle );
		void rotateWorld( float x, float y, float z );

		void setLocalScale( const AGVec3& factor );
		void setLocalScale( float x, float y, float z ); 
		const AGVec3& getLocalScale() const; 

		void setWorldScale( const AGVec3& factor );
		void setWorldScale( float x, float y, float z ); 
		const AGVec3& getWorldScale() const; 

		void scaleLocal( const AGVec3& factor ); 
		void scaleLocal( float x, float y, float z );

		void scaleWorld( const AGVec3& factor ); 
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

		void setLookAt( const AGVec3& dir );
		
	protected:
		virtual void handleChanges( Changes changes ) = 0;

	private:
		AGMovablePrivate* m_p; 
};

#endif 