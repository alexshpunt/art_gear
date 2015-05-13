#include "AGCamera.h"

#include <windows.h>
#include <math.h>

#include "Managers/AGEStateManager.h"
#include "Managers/AGLogger.h"
#include "Managers/AGTimeManager.h"
#include "Managers/AGInputManager.h"
#include "Managers/AGGraphicsSettings.h"

class AGCameraPrivate
{
	public:
		AGCameraPrivate()
		{
			aspectRatio = 1.0f; 
			farPlane = 1000.0f; 
			nearPlane = 0.001f; 
			sensX = 1.1f; 
			sensY = 1.1f; 
			speed = 0.9f; 
			sprintSpeed = speed * 2.0f; 
			up      = AGVec3::Up(); 
			target  = AGVec3::Forward(); 
			pos     = AGVec3::Zero(); 

			horSpeed = vertSpeed = 0; 
			angleX = angleY = AGRadians( 0.0f );

			zoom = 5.0;
		}
		
		float nearPlane;
		float farPlane;
		float aspectRatio;
		float speed;
		float sprintSpeed; 
		float sensX;
		float sensY;
		int   layer;

		float targetDistance; 
		AGRadians angleX;
		AGRadians angleY; 

		AGVec3 target;
		AGVec3 up;
		AGVec3 pos;

		AGMatrix viewMatrix;
		AGMatrix projMatrix; 

		float vertSpeed;
		float horSpeed; 

		AGDegrees fov;

		float zoom; 

		AGCamera::AGCameraType type; 
};

AGCamera::AGCamera( AGCameraType type )
{
	p = new AGCameraPrivate; 

	setFov( AGDegrees( 45.0f ) );

	p->viewMatrix.setLookAtLH( p->pos, p->target, p->up );
	p->targetDistance = p->target.getLength(); 

	p->type = type; 

	if( p->type == Ortho )
		updateOrtho();
	else 
		updateProj();
}

AGCamera::~AGCamera()
{
	delete p; 
}

void AGCamera::setAspectRatio(float aspectRatio)
{
	p->aspectRatio = aspectRatio; 

	if( p->type == Ortho )
		updateOrtho();
	else 
		updateProj();
}

float AGCamera::getAspectRatio() const
{
	return p->aspectRatio;
}

void AGCamera::setNearPlane(float nearPlane)
{
	p->nearPlane = nearPlane; 
	if( p->type == Ortho )
		updateOrtho();
	else 
		updateProj();
}

float AGCamera::getNearPlane() const
{
	return p->nearPlane; 
}

void AGCamera::setFarPlane(float farPlane)
{
	p->farPlane = farPlane; 
	if( p->type == Ortho )
		updateOrtho();
	else 
		updateProj();
}

float AGCamera::getFarPlane() const
{
	return p->farPlane; 
}

void AGCamera::setSpeed(float speed)
{
	p->speed = speed;
}

float AGCamera::getSpeed() const
{
	return p->speed;
}

void AGCamera::setSprintSpeed(float sprintSpeed)
{
	p->sprintSpeed = sprintSpeed;
}

float AGCamera::getSprintSpeed() const
{
	return p->sprintSpeed;
}

void AGCamera::setSensX(float sensX)
{
	p->sensX = sensX; 
}

float AGCamera::getSensX() const
{
	return p->sensX; 
}

void AGCamera::setSensY(float sensY)
{
	p->sensY = sensY; 
}

float AGCamera::getSensY() const
{
	return p->sensY;
}

void AGCamera::setTarget(const AGVec3& at)
{
	p->target = at; 
	p->viewMatrix.setLookAtLH( p->pos, p->target, p->up );
}

const AGVec3& AGCamera::getTarget() const
{
	return p->target; 
}

void AGCamera::setUp(const AGVec3& up)
{
	p->up = up; 
	p->viewMatrix.setLookAtLH( p->pos, p->target, p->up );
}

const AGVec3& AGCamera::getUp() const
{
	return p->up; 
}

void AGCamera::setPos(const AGVec3& forward)
{
	p->pos = forward; 
	p->viewMatrix.setLookAtLH( p->pos, p->target, p->up );
}

const AGVec3& AGCamera::getPos() const
{
	return p->pos; 
}

const AGMatrix& AGCamera::getViewMatrix() const
{
	return p->viewMatrix; 
}

const AGMatrix& AGCamera::getProjMatrix() const
{
	return p->projMatrix; 
}

void AGCamera::setTargetDistance(float dist)
{
	p->targetDistance = dist;
	
	AGVec3 v( 0.0f, 0.0f, dist );

	v *= AGMatrix::RotationY( AGRadians( p->angleX ) ); 
	v *= AGMatrix::RotationX( AGRadians( p->angleY ) ); 

	p->target = p->pos + v; 
}

void AGCamera::update()
{
	/*if( AGEStateManager::getInstance().isCameraFovChanged() )
	{
		setFov( AGDegrees( AGEStateManager::getInstance().getCameraFov() ) );
	}*/

	bool mmb = AGInput().isButtonPressed( "MMB" );
	p->vertSpeed = AGMath::toRadians( AGInput().isKeyPressed( 'W' ) ? 1 : AGInput().isKeyPressed( 'S' ) ? -1 : 0 );
	p->horSpeed = AGMath::toRadians( AGInput().isKeyPressed( 'D' ) ? -1 : AGInput().isKeyPressed( 'A' ) ? 1 : 0 ); 

	bool rmb = AGInput().isButtonPressed( "RMB" );
	bool alt = AGInput().isKeyPressed( "Alt" );
	int wheelDelta = AGInput().getWheelDelta(); 

	AGPoint2 dPos = AGInput().getMouseDeltaPos(); 
	double dt = AGTimeManager::getInstance().getDeltaTime();

	float dAngleY = AGMath::toRadians( dPos.x ) * p->sensX;
	float dAngleX = AGMath::toRadians( dPos.y ) * p->sensY;  

	if( wheelDelta != 0 )
	{
		if( p->type == Perspective )
		{
			bool shift = AGInput().isKeyPressed( "Shift" );
			AGVec3 vec = p->pos - p->target; 
			vec *= -wheelDelta * p->speed * ( shift ? 5 : 0.5f ); 
			p->pos += vec;
			p->target += vec;
		}
		else
		{
			p->zoom += -wheelDelta * p->speed; 
			if( p->zoom < 0.1f )
			{
				p->zoom = 0.1f;
			}
			//translateInDirection( wheelDelta * p->speed );
			updateOrtho();
		}

		AGEStateManager::getInstance().setRotating( false );
	}

	if( mmb )
	{
		if( alt ) //TODO: Доделать 
		{
			p->angleY += AGRadians( dAngleY );
			p->angleX += AGRadians( dAngleX );

			float critAngle = AGMath::toRadians( 89.8f );

			if( p->angleX > critAngle )
			{
				p->angleX = AGRadians( critAngle );
			}
			else if( p->angleX < -critAngle )
			{
				p->angleX = AGRadians( -critAngle );
			}

			AGVec3 v( 0.0f, 0.0f, p->targetDistance );

			v *= AGMatrix::RotationY( p->angleX ); 
			v *= AGMatrix::RotationX( p->angleY );

			p->pos = p->target - v; 
			AGEStateManager::getInstance().setRotating( true );
		}
		else 
		{
			AGVec3 right( 1.0, 0.0f, 0.0f );
			AGVec3 up( 0.0f, 1.0, 0.0f );
			AGMatrix rotMatRight = AGMatrix::RotationY( p->angleY );

			right *= rotMatRight;
			up *= AGMatrix::RotationX( p->angleX );
			up *= rotMatRight; 

			p->target -= right * dAngleY; 
			p->target += up * dAngleX;
			p->pos -= right * dAngleY; 
			p->pos += up * dAngleX;
			AGEStateManager::getInstance().setRotating( true );
		}
	}
	else if( rmb )
	{
		p->angleY += AGRadians( dAngleY );
		p->angleX += AGRadians( dAngleX );

		float critAngle = AGMath::toRadians( 89.8f );

		if( p->angleX > critAngle )
		{
			p->angleX = AGRadians( critAngle );
		}
		else if( p->angleX < -critAngle )
		{
			p->angleX = AGRadians( -critAngle );
		}
		AGVec3 v = AGVec3::Forward();

		v *= AGMatrix::YawPitchRoll( p->angleY, p->angleX, AGRadians( 0.0f ) ); 

		p->target = p->pos + v; 

		AGEStateManager::getInstance().setRotating( true );
	}
	if( p->horSpeed != 0 || p->vertSpeed != 0 )
	{
		AGVec3 vec = ( p->pos - p->target ).normilized(); 

		AGVec3 rightVec = AGVec3::Right(); 

		rightVec *= AGMatrix::RotationY( p->angleY ); 
		rightVec *= -p->horSpeed * p->speed; 

		p->pos += rightVec;
		p->target += rightVec;

		if( p->type == Ortho )
		{
			p->zoom += ( AGInput().isKeyPressed( "Shift" ) ? -p->sprintSpeed : -p->speed ) * p->vertSpeed; 
			if( p->zoom < 0.01f )
			{
				p->zoom = 0.01f; 
			}
			//translateInDirection( ( AGInput().isKeyPressed( "Shift" ) ? -p->sprintSpeed : -p->speed ) * p->vertSpeed );
			updateOrtho(); 
		}
		else
		{
			vec *= ( AGInput().isKeyPressed( "Shift" ) ? -p->sprintSpeed : -p->speed ) * p->vertSpeed; 
			p->pos += vec;
			p->target += vec; 
		}

		AGEStateManager::getInstance().setRotating( false );
	}
	p->viewMatrix.setLookAtLH( p->pos, p->target, p->up );
}

float AGCamera::getAngleX() const
{
	return p->angleX;
}

float AGCamera::getAngleY() const
{
	return p->angleY;
}

const AGVec3& AGCamera::getDir()
{
	AGVec3 dir = p->target - p->pos; 
	dir.normilize(); 
	return dir; 
}

void AGCamera::updateProj()
{
	p->projMatrix.setPerspectiveLH( p->fov, p->aspectRatio, p->nearPlane, p->farPlane );
}

void AGCamera::updateOrtho()
{
	p->projMatrix.setOrthoLH( p->zoom * p->aspectRatio, p->zoom, p->nearPlane, p->farPlane );
}

void AGCamera::setFov(AGDegrees fov)
{
	p->fov = fov; 
	if( p->type == Ortho )
		updateOrtho();
	else 
		updateProj();
}

void AGCamera::setFov(AGRadians fov)
{
	setFov( fov.toDegrees() );
}

AGDegrees AGCamera::getFov() const
{
	return p->fov; 
}

void AGCamera::setType(AGCameraType type)
{
	p->type = type; 
	if( p->type == Ortho )
	{
		updateOrtho();
	}
	else 
	{
		updateProj();
	}
}

AGCamera::AGCameraType AGCamera::getType() const
{
	return p->type; 
}

void AGCamera::rotate( AGRadians angleX, AGRadians angleY)
{
	p->angleY = angleY;
	p->angleX = angleX;

	AGRadians critAngle = AGDegrees( 89.8f ).toRadians();

	if( p->angleX > critAngle )
	{
		p->angleX = AGRadians( critAngle );
	}
	else if( p->angleX < -critAngle )
	{
		p->angleX = AGRadians( -critAngle );
	}
	AGVec3 v( 0.0f, 0.0f, 1.0f );
	v *= AGMatrix::Rotation( p->angleY, p->angleX, AGRadians( 0.0f ) );

	p->target = p->pos + v; 
}

void AGCamera::rotate(AGDegrees angleX, AGDegrees angleY)
{
	rotate( angleX.toRadians(), angleY.toRadians() );
}

void AGCamera::translateInDirection( float z)
{
	AGVec3 vec = ( p->pos - p->target ).normilized(); 
	
	vec *= -z;
	p->pos += vec;
	p->target += vec;
}
