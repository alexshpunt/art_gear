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
		const AGVec3& getPivot();

		void setLocalPos( const AGVec3& pos );
		const AGVec3& getLocalPos() const;

		void setWorldPos( const AGVec3& pos );
		const AGVec3& getWorldPos() const;

		void translateLocal( const AGVec3& pos );

		void translateWorld( const AGVec3& pos );

		void setLocalAngle( float x, float y, float z );
		const AGVec3& getLocalAngle() const; 

		void setWorldAngle( float x, float y, float z );
		const AGVec3& getWorldAngle() const; 

		void rotateLocalAxis( const AGVec3& axis, float angle );
		void rotateLocalX( float angle );
		void rotateLocalY( float angle );
		void rotateLocalZ( float angle );
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

		void setLocalScale( const AGVec3& factor );
		const AGVec3& getLocalScale() const; 

		void setWorldScale( const AGVec3& factor );
		const AGVec3& getWorldScale() const; 

		void scaleLocal( const AGVec3& factor ); 

		void scaleWorld( const AGVec3& factor ); 

		void setLocalMatrix( const AGMatrix& world );
		const AGMatrix& getLocalMatrix();

		void setLocalTranslMatrix( const AGMatrix& transl );
		const AGMatrix& getLocalTranslMatrix();

		void setLocalRotMatrix( const AGMatrix& rot );
		const AGMatrix& getLocalRotMatrix();

		void setLocalScaleMatrix( const AGMatrix& scale );
		const AGMatrix& getLocalScaleMatrix();

		void setWorldMatrix( const AGMatrix& world );
		const AGMatrix& getWorldMatrix();

		void setWorldTranslMatrix( const AGMatrix& transl ); 
		const AGMatrix& getWorldTranslMatrix();

		void setWorldRotMatrix( const AGMatrix& rot ); 
		const AGMatrix& getWorldRotMatrix();

		void setWorldScaleMatrix( const AGMatrix& scale ); 
		const AGMatrix& getWorldScaleMatrix(); 

		void setResultMatrix( const AGMatrix& world );
		const AGMatrix& getResultMatrix(); 

		void setLookAt( const AGVec3& dir );
		
	protected:
		virtual void handleChanges( Changes changes ) = 0;

	private:
		AGMovablePrivate* p; 
};

#endif 