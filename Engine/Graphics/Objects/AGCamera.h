#ifndef AG_CAMERA_H
#define AG_CAMERA_H

#include "Engine/Math/AGMath.h"

#include "Graphics/AGGraphics.h"

class AGCameraPrivate; 

class AGCamera
{
	public:
		enum AGCameraType{ Ortho, Perspective };
		AGCamera( AGCameraType type = Perspective );
		~AGCamera();

		void setType( AGCameraType type );
		AGCameraType getType() const; 

		void setFov( AGRadians fov );
		void setFov( AGDegrees fov );
		AGDegrees getFov() const; 

		void setAspectRatio( float aspectRatio );
		float getAspectRatio() const; 

		void setNearPlane( float nearPlane );
		float getNearPlane() const; 

		void setFarPlane( float farPlane );
		float getFarPlane() const; 

		void setSpeed( float speed );
		float getSpeed() const; 

		void setSprintSpeed( float sprintSpeed );
		float getSprintSpeed() const; 

		void setSensX( float sensX );
		float getSensX() const;

		void setSensY( float sensY );
		float getSensY() const; 

		void setTarget( const AGVec3& at );
		const AGVec3& getTarget() const;

		void setUp( const AGVec3& up );
		const AGVec3& getUp() const;

		const AGVec3& getDir(); 

		void setPos( const AGVec3& forward );
		const AGVec3& getPos() const;  

		const AGMatrix& getViewMatrix() const; 
		const AGMatrix& getProjMatrix() const; 

		float getAngleX() const;
		float getAngleY() const; 

		void setTargetDistance( float dist );
		void update(); 
		void updateProj();
		void updateOrtho();   

		void rotate( AGRadians angleX, AGRadians angleY ); 
		void rotate( AGDegrees angleX, AGDegrees angleY ); 

		void translateInDirection( float z );
	protected:
		AGCameraPrivate* p; 
};
#endif 