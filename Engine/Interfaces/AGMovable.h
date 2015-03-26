#ifndef AG_MOVABLE_H
#define AG_MOVABLE_H

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

		void setLocalAngle( const AGEulerAngles& angles );
		void setLocalAngle( AGRadians x, AGRadians y, AGRadians z );
		void setLocalAngle( AGDegrees x, AGDegrees y, AGDegrees z );
		const AGEulerAngles& getLocalAngle() const; 

		void setWorldAngle( const AGEulerAngles& angles );
		void setWorldAngle( AGRadians x, AGRadians y, AGRadians z );
		void setWorldAngle( AGDegrees x, AGDegrees y, AGDegrees z );
		const AGEulerAngles& getWorldAngle() const; 

		void rotateLocalAxis( const AGVec3& axis, AGRadians angle );
		void rotateLocalAxis( const AGVec3& axis, AGDegrees angle );
		void rotateLocalX( AGRadians angle );
		void rotateLocalX( AGDegrees angle );
		void rotateLocalY( AGRadians angle );
		void rotateLocalY( AGDegrees angle );
		void rotateLocalZ( AGRadians angle );
		void rotateLocalZ( AGDegrees angle );

		void rotateLocal( const AGEulerAngles& angles ); 
		void rotateLocal( AGRadians x, AGRadians y, AGRadians z );
		void rotateLocal( AGDegrees x, AGDegrees y, AGDegrees z );

		void rotateWorldAxis( const AGVec3& axis, AGRadians angle );
		void rotateWorldAxis( const AGVec3& axis, AGDegrees angle );

		void rotateAroundWorldX( AGRadians angle );
		void rotateAroundWorldX( AGDegrees angle );
		void rotateAroundWorldY( AGRadians angle );
		void rotateAroundWorldY( AGDegrees angle );
		void rotateAroundWorldZ( AGRadians angle );
		void rotateAroundWorldZ( AGDegrees angle );
		
		//Rotate around "parent" axis
		void rotateWorldX( AGRadians angle );
		void rotateWorldX( AGDegrees angle );
		void rotateWorldY( AGRadians angle );
		void rotateWorldY( AGDegrees angle );
		void rotateWorldZ( AGRadians angle );
		void rotateWorldZ( AGDegrees angle );
	
		void rotateWorld( const AGEulerAngles& angles );
		void rotateWorld( AGRadians x, AGRadians y, AGRadians z );
		void rotateWorld( AGDegrees x, AGDegrees y, AGDegrees z );

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