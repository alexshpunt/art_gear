#include "AGCamera.h"

#include <windows.h>
#include <math.h>

#include "Managers/AGEStateManager.h"
#include "Managers/AGLogger.h"
#include "Managers/AGTimeManager.h"
#include "Managers/AGInputManager.h"
#include "Managers/AGGraphicsSettings.h"

#include "Engine/Utils/AGConversion.h"

#define PI_2 1.5707963267948966192313216916398

AGCamera::AGCamera( AGCameraType type )
{
	m_aspectRatio = 1.0f; 
	m_farPlane = 1000.0f; 
	m_nearPlane = 0.001f; 
	m_sensX = 1.1f; 
	m_sensY = 1.1f; 
	m_speed = 0.2f; 
	m_sprintSpeed = m_speed * 2.0f; 
	m_up = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
	m_at = D3DXVECTOR3( 0.0f, 0.0f, 1.0f );
	m_eye = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );

	m_zoom = 5.0;

	setFov( 45 );

	m_horSpeed = m_vertSpeed = 0; 

	m_angleX = m_angleY = 0.0f;

	D3DXMatrixLookAtLH( &m_viewMatrix, &m_eye, &m_at, &m_up );
	m_targetDistance = D3DXVec3Length( &m_at );

	m_type = type; 

	if( m_type == Ortho )
		updateOrtho();
	else 
		updateProj();
}

AGCamera::~AGCamera()
{

}

void AGCamera::setAspectRatio(float aspectRatio)
{
	m_aspectRatio = aspectRatio; 

	if( m_type == Ortho )
		updateOrtho();
	else 
		updateProj();
}

float AGCamera::getAspectRatio() const
{
	return m_aspectRatio;
}

void AGCamera::setNearPlane(float nearPlane)
{
	m_nearPlane = nearPlane; 
	if( m_type == Ortho )
		updateOrtho();
	else 
		updateProj();
}

float AGCamera::getNearPlane() const
{
	return m_nearPlane; 
}

void AGCamera::setFarPlane(float farPlane)
{
	m_farPlane = farPlane; 
	if( m_type == Ortho )
		updateOrtho();
	else 
		updateProj();
}

float AGCamera::getFarPlane() const
{
	return m_farPlane; 
}

void AGCamera::setSpeed(float speed)
{
	m_speed = speed;
}

float AGCamera::getSpeed() const
{
	return m_speed;
}

void AGCamera::setSprintSpeed(float sprintSpeed)
{
	m_sprintSpeed = sprintSpeed;
}

float AGCamera::getSprintSpeed() const
{
	return m_sprintSpeed;
}

void AGCamera::setSensX(float sensX)
{
	m_sensX = sensX; 
}

float AGCamera::getSensX() const
{
	return m_sensX; 
}

void AGCamera::setSensY(float sensY)
{
	m_sensY = sensY; 
}

float AGCamera::getSensY() const
{
	return m_sensY;
}

void AGCamera::setLayer(int layer)
{
	m_layer = layer; 
}

int AGCamera::getLayer() const
{
	return m_layer;
}

void AGCamera::setAt(D3DXVECTOR3 at)
{
	m_at = at; 
	D3DXMatrixLookAtLH( &m_viewMatrix, &m_eye, &m_at, &m_up );
	m_vm.setLookAtLH( AGConversion::toAGVec3D( m_eye ), AGConversion::toAGVec3D( m_at ), AGConversion::toAGVec3D( m_up ) );
}

D3DXVECTOR3 AGCamera::getAt() const
{
	return m_at; 
}

void AGCamera::setUp(D3DXVECTOR3 up)
{
	m_up = up; 
	D3DXMatrixLookAtLH( &m_viewMatrix, &m_eye, &m_at, &m_up );
	m_vm.setLookAtLH( AGConversion::toAGVec3D( m_eye ), AGConversion::toAGVec3D( m_at ), AGConversion::toAGVec3D( m_up ) );
}

D3DXVECTOR3 AGCamera::getUp() const
{
	return m_up; 
}

void AGCamera::setEye(D3DXVECTOR3 forward)
{
	m_eye = forward; 
	D3DXMatrixLookAtLH( &m_viewMatrix, &m_eye, &m_at, &m_up );
	m_vm.setLookAtLH( AGConversion::toAGVec3D( m_eye ), AGConversion::toAGVec3D( m_at ), AGConversion::toAGVec3D( m_up ) );
}

D3DXVECTOR3 AGCamera::getEye() const
{
	return m_eye; 
}

D3DXMATRIX AGCamera::getViewMatrix() const
{
	return m_viewMatrix; 
}

D3DXMATRIX AGCamera::getProjMatrix() const
{
	return m_projMatrix; 
}

void AGCamera::setTargetDistance(float dist)
{
	m_targetDistance = dist;
	D3DXVECTOR3 v( 0.0f, 0.0f, dist );
	D3DXMatrixRotationYawPitchRoll( &m_rotMatrix, 0.0f, m_angleX, 0.0f );
	D3DXVec3TransformCoord( &v, &v, &m_rotMatrix );

	D3DXMatrixRotationYawPitchRoll( &m_rotMatrix, m_angleY, 0.0f, 0.0f );
	D3DXVec3TransformCoord( &v, &v, &m_rotMatrix ); 

	m_at = m_eye + v; 
}

void AGCamera::update()
{
	if( AGEStateManager::getInstance().isCameraFovChanged() )
	{
		setFov( AGEStateManager::getInstance().getCameraFov() );
	}

	bool mmb = AGInput().isButtonPressed( "MMB" );
	m_vertSpeed = AGInput().isKeyPressed( 'W' ) ? 1 : AGInput().isKeyPressed( 'S' ) ? -1 : 0;
	m_horSpeed = AGInput().isKeyPressed( 'D' ) ? -1 : AGInput().isKeyPressed( 'A' ) ? 1 : 0; 

	m_vertSpeed = D3DXToRadian( m_vertSpeed );
	m_horSpeed = D3DXToRadian( m_horSpeed );

	bool rmb = AGInput().isButtonPressed( "RMB" );
	bool alt = AGInput().isKeyPressed( "Alt" );
	int wheelDelta = AGInput().getWheelDelta(); 

	AGPoint2 dPos = AGInput().getMouseDeltaPos(); 
	double dt = AGTimeManager::getInstance().getDeltaTime();

	float dAngleY = D3DXToRadian( dPos.x ) * m_sensX;
	float dAngleX = D3DXToRadian( dPos.y ) * m_sensY;  

	if( wheelDelta != 0 )
	{
		if( m_type == Perspective )
		{
			bool shift = AGInput().isKeyPressed( "Shift" );
			D3DXVECTOR3 vec = m_eye - m_at; 
			vec *= -wheelDelta * m_speed * ( shift ? 5 : 0.5f ); 
			m_eye += vec;
			m_at += vec;
		}
		else
		{
			m_zoom += -wheelDelta * m_speed; 
			if( m_zoom < 0.1f )
			{
				m_zoom = 0.1f;
			}
			//translateInDirection( wheelDelta * m_speed );
			updateOrtho();
		}

		AGEStateManager::getInstance().setRotating( false );
	}

	if( mmb )
	{
		if( alt )
		{
			m_angleY += dAngleY;
			m_angleX += dAngleX;

			float critAngle = D3DXToRadian( 89.8f );

			if( m_angleX > critAngle )
			{
				m_angleX = critAngle;
			}
			else if( m_angleX < -critAngle )
			{
				m_angleX = -critAngle;
			}

			D3DXVECTOR3 v( 0.0f, 0.0f, m_targetDistance );
			D3DXMatrixRotationYawPitchRoll( &m_rotMatrix, 0.0f, m_angleX, 0.0f );
			D3DXVec3TransformCoord( &v, &v, &m_rotMatrix );

			D3DXMatrixRotationYawPitchRoll( &m_rotMatrix, m_angleY, 0.0f, 0.0f );
			D3DXVec3TransformCoord( &v, &v, &m_rotMatrix ); 

			m_eye = m_at - v; 
			AGEStateManager::getInstance().setRotating( true );
		}
		else 
		{
			D3DXVECTOR3 right( 1.0, 0.0f, 0.0f );
			D3DXVECTOR3 up( 0.0f, 1.0, 0.0f );
			D3DXMATRIX rotMatRight;
			D3DXMATRIX rotMatUp;  

			D3DXMatrixRotationYawPitchRoll( &rotMatRight, m_angleY, 0.0f, 0.0f );
			D3DXMatrixRotationYawPitchRoll( &rotMatUp, 0.0f, m_angleX, 0.0f );

			D3DXVec3TransformCoord( &right, &right, &rotMatRight );
			D3DXVec3TransformCoord( &up, &up, &rotMatUp );
			D3DXVec3TransformCoord( &up, &up, &rotMatRight );

			m_at -= right * dAngleY; 
			m_at += up * dAngleX;
			m_eye -= right * dAngleY; 
			m_eye += up * dAngleX;
			AGEStateManager::getInstance().setRotating( true );
		}
	}
	else if( rmb )
	{
		m_angleY += dAngleY;
		m_angleX += dAngleX;

		float critAngle = D3DXToRadian( 89.8f );

		if( m_angleX > critAngle )
		{
			m_angleX = critAngle;
		}
		else if( m_angleX < -critAngle )
		{
			m_angleX = -critAngle;
		}
		D3DXVECTOR3 v( 0.0f, 0.0f, 1.0f );
		D3DXMatrixRotationYawPitchRoll( &m_rotMatrix, m_angleY, m_angleX, 0.0f );
		D3DXVec3TransformCoord( &v, &v, &m_rotMatrix );

		m_at = m_eye + v; 

		AGEStateManager::getInstance().setRotating( true );
	}
	if( m_horSpeed != 0 || m_vertSpeed != 0 )
	{
		D3DXVECTOR3 vec = m_eye - m_at; 
		D3DXVec3Normalize( &vec, &vec );
		D3DXVECTOR3 rightVec( 1.0, 0.0f, 0.0f );
		D3DXMATRIX rotMatrix; 
		D3DXMatrixIdentity( &rotMatrix );
		D3DXMatrixRotationYawPitchRoll( &rotMatrix, m_angleY, 0.0f, 0.0f );

		D3DXVec3TransformCoord( &rightVec, &rightVec, &rotMatrix );
		rightVec *= -m_horSpeed * m_speed; 
		m_eye += rightVec;
		m_at += rightVec;

		if( m_type == Ortho )
		{
			m_zoom += ( AGInput().isKeyPressed( "Shift" ) ? -m_sprintSpeed : -m_speed ) * m_vertSpeed; 
			if( m_zoom < 0.01f )
			{
				m_zoom = 0.01f; 
			}
			//translateInDirection( ( AGInput().isKeyPressed( "Shift" ) ? -m_sprintSpeed : -m_speed ) * m_vertSpeed );
			updateOrtho(); 
		}
		else
		{
			vec *= ( AGInput().isKeyPressed( "Shift" ) ? -m_sprintSpeed : -m_speed ) * m_vertSpeed; 
			m_eye += vec;
			m_at += vec; 
		}

		AGEStateManager::getInstance().setRotating( false );
	}
	D3DXMatrixLookAtLH( &m_viewMatrix, &m_eye, &m_at, &m_up );
	m_vm.setLookAtLH( AGConversion::toAGVec3D( m_eye ), AGConversion::toAGVec3D( m_at ), AGConversion::toAGVec3D( m_up ) );
}

float AGCamera::getAngleX() const
{
	return m_angleX;
}

float AGCamera::getAngleY() const
{
	return m_angleY;
}

D3DXVECTOR3 AGCamera::getDir()
{
	D3DXVECTOR3 dir = m_at - m_eye; 
	D3DXVec3Normalize( &dir, &dir );
	return dir; 
}

void AGCamera::updateProj()
{
	D3DXMatrixPerspectiveFovLH( &m_projMatrix, D3DXToRadian( m_fov ), m_aspectRatio, m_nearPlane, m_farPlane );
	m_pm.setPerspectiveLH( m_fov, m_aspectRatio, m_nearPlane, m_farPlane );
}

void AGCamera::updateOrtho()
{
	D3DXMatrixOrthoLH( &m_projMatrix, m_zoom* m_aspectRatio, m_zoom, m_nearPlane, m_farPlane );
	m_pm.setOrthoLH( m_zoom * m_aspectRatio, m_zoom, m_nearPlane, m_farPlane );
}

void AGCamera::setFov(float fov)
{
	m_fov = fov; 
	if( m_type == Ortho )
		updateOrtho();
	else 
		updateProj();
}

float AGCamera::getFov() const
{
	return m_fov; 
}

void AGCamera::setType(AGCameraType type)
{
	m_type = type; 
	if( m_type == Ortho )
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
	return m_type; 
}

void AGCamera::rotateY(float angle)
{
	m_angleY = D3DXToRadian( angle );

	D3DXVECTOR3 v( 0.0f, 0.0f, 1.0f );
	D3DXMatrixRotationYawPitchRoll( &m_rotMatrix, m_angleY, m_angleX, 0.0f );
	D3DXVec3TransformCoord( &v, &v, &m_rotMatrix );

	m_at = m_eye + v; 
}

void AGCamera::rotateX(float angle)
{
	m_angleX = D3DXToRadian( angle );

	float critAngle = D3DXToRadian( 89.8f );

	if( m_angleX > critAngle )
	{
		m_angleX = critAngle;
	}
	else if( m_angleX < -critAngle )
	{
		m_angleX = -critAngle;
	}
	D3DXVECTOR3 v( 0.0f, 0.0f, 1.0f );
	D3DXMatrixRotationYawPitchRoll( &m_rotMatrix, m_angleY, m_angleX, 0.0f );
	D3DXVec3TransformCoord( &v, &v, &m_rotMatrix );

	m_at = m_eye + v; 
}

void AGCamera::rotate(float angleX, float angleY)
{
	m_angleY = D3DXToRadian( angleY );
	m_angleX = D3DXToRadian( angleX );

	float critAngle = D3DXToRadian( 89.8f );

	if( m_angleX > critAngle )
	{
		m_angleX = critAngle;
	}
	else if( m_angleX < -critAngle )
	{
		m_angleX = -critAngle;
	}
	D3DXVECTOR3 v( 0.0f, 0.0f, 1.0f );
	D3DXMatrixRotationYawPitchRoll( &m_rotMatrix, m_angleY, m_angleX, 0.0f );
	D3DXVec3TransformCoord( &v, &v, &m_rotMatrix );

	m_at = m_eye + v; 
}

void AGCamera::translateInDirection( float z)
{
	D3DXVECTOR3 vec = m_eye - m_at; 

	D3DXVec3Normalize( &vec, &vec );
	vec *= -z;
	m_eye += vec;
	m_at += vec;
}

AGMatrix AGCamera::getVM()
{
	return m_vm;
}

AGMatrix AGCamera::getPM()
{
	return m_pm; 
}
