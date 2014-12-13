#include "AGDXCamera.h"

#include <math.h>

#include "Managers/AGStateManager.h"
#include "Managers/AGLogger.h"
#include "Managers/AGTimeManager.h"
#include "Managers/AGInputManager.h"
#include "Managers/AGGraphicsSettings.h"

#define PI_2 1.5707963267948966192313216916398

AGDXCamera::AGDXCamera()
{
	m_fov = 70.0f;
	m_aspectRatio = AGGraphicsSettings::getInstance().getAspectRatio(); 
	m_farPlane = 1000.0f; 
	m_nearPlane = 0.001f; 
	m_sensX = 0.005f; 
	m_sensY = 0.005f; 
	m_speed = 0.02f; 
	m_sprintSpeed = 0.05f; 
	m_up = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
	m_at = D3DXVECTOR3( 0.0f, 0.0f, 1.0f );
	m_eye = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );

	m_angleX = m_angleY = 0.0f;

	D3DXMatrixPerspectiveFovLH( &m_projMatrix, m_fov, m_aspectRatio, m_nearPlane, m_farPlane );
	D3DXMatrixLookAtLH( &m_viewMatrix, &m_eye, &m_at, &m_up );
	m_targetDistance = D3DXVec3Length( &m_at );
}

AGDXCamera::~AGDXCamera()
{

}

void AGDXCamera::setFov(float fov)
{
	m_fov = fov;
	D3DXMatrixPerspectiveFovLH( &m_projMatrix, m_fov, m_aspectRatio, m_nearPlane, m_farPlane );
}

float AGDXCamera::getFov() const
{
	return m_fov; 
}

void AGDXCamera::setAspectRatio(float aspectRatio)
{
	m_aspectRatio = aspectRatio; 
	D3DXMatrixPerspectiveFovLH( &m_projMatrix, m_fov, m_aspectRatio, m_nearPlane, m_farPlane );
}

float AGDXCamera::getAspectRatio() const
{
	return m_aspectRatio; 
}

void AGDXCamera::setNearPlane(float nearPlane)
{
	m_nearPlane = nearPlane; 
	D3DXMatrixPerspectiveFovLH( &m_projMatrix, m_fov, m_aspectRatio, m_nearPlane, m_farPlane );
}

float AGDXCamera::getNearPlane() const
{
	return m_nearPlane; 
}

void AGDXCamera::setFarPlane(float farPlane)
{
	m_farPlane = farPlane; 
	D3DXMatrixPerspectiveFovLH( &m_projMatrix, m_fov, m_aspectRatio, m_nearPlane, m_farPlane );
}

float AGDXCamera::getFarPlane() const
{
	return m_farPlane; 
}

void AGDXCamera::setSpeed(float speed)
{
	m_speed = speed;
}

float AGDXCamera::getSpeed() const
{
	return m_speed;
}

void AGDXCamera::setSprintSpeed(float sprintSpeed)
{
	m_sprintSpeed = sprintSpeed;
}

float AGDXCamera::getSprintSpeed() const
{
	return m_sprintSpeed;
}

void AGDXCamera::setSensX(float sensX)
{
	m_sensX = sensX; 
}

float AGDXCamera::getSensX() const
{
	return m_sensX; 
}

void AGDXCamera::setSensY(float sensY)
{
	m_sensY = sensY; 
}

float AGDXCamera::getSensY() const
{
	return m_sensY;
}

void AGDXCamera::setLayer(int layer)
{
	m_layer = layer; 
}

int AGDXCamera::getLayer() const
{
	return m_layer;
}

void AGDXCamera::setAt(D3DXVECTOR3 at)
{
	m_at = at; 
	D3DXMatrixLookAtLH( &m_viewMatrix, &m_eye, &m_at, &m_up );
}

D3DXVECTOR3 AGDXCamera::getAt() const
{
	return m_at; 
}

void AGDXCamera::setUp(D3DXVECTOR3 up)
{
	m_up = up; 
	D3DXMatrixLookAtLH( &m_viewMatrix, &m_eye, &m_at, &m_up );
}

D3DXVECTOR3 AGDXCamera::getUp() const
{
	return m_up; 
}

void AGDXCamera::setEye(D3DXVECTOR3 forward)
{
	m_eye = forward; 
	D3DXMatrixLookAtLH( &m_viewMatrix, &m_eye, &m_at, &m_up );
}

D3DXVECTOR3 AGDXCamera::getEye() const
{
	return m_eye; 
}

D3DXMATRIX AGDXCamera::getViewMatrix() const
{
	return m_viewMatrix; 
}

D3DXMATRIX AGDXCamera::getProjMatrix() const
{
	return m_projMatrix; 
}

void AGDXCamera::setTargetDistance(float dist)
{
	m_targetDistance = dist;
	D3DXVECTOR3 v( 0.0f, 0.0f, dist );
	D3DXMatrixRotationYawPitchRoll( &m_rotMatrix, 0.0f, m_angleX, 0.0f );
	D3DXVec3TransformCoord( &v, &v, &m_rotMatrix );

	D3DXMatrixRotationYawPitchRoll( &m_rotMatrix, m_angleY, 0.0f, 0.0f );
	D3DXVec3TransformCoord( &v, &v, &m_rotMatrix ); 

	m_at = m_eye + v; 
}

void AGDXCamera::update()
{
	bool mmb = AGInput().isButtonPressed( "MMB" );
	int vertSpeed = AGInput().isKeyPressed( 'W' ) ? 1 : AGInput().isKeyPressed( 'S' ) ? -1 : 0; 
	int horSpeed = AGInput().isKeyPressed( 'D' ) ? -1 : AGInput().isKeyPressed( 'A' ) ? 1 : 0; 
	bool rmb = AGInput().isButtonPressed( "RMB" );
	bool alt = AGInput().isKeyPressed( "Alt" );
	int wheelDelta = AGInput().getWheelDelta(); 
	
	AGPoint2 dPos = AGInput().getMouseDeltaPos(); 
	double dt = AGTimeManager::getInstance().getDeltaTime(); 

	if( wheelDelta != 0 )
	{
		bool shift = AGInput().isKeyPressed( "Shift" );
		D3DXVECTOR3 vec = m_eye - m_at; 
		vec *= -wheelDelta * m_speed * ( shift ? 10 : 1 ); 
		m_eye += vec;
		m_at += vec; 
		AGStateManager::getInstance().setRotating( false );
	}

	if( mmb )
	{
		if( alt )
		{
			float dAngleY = dPos.x * dt;
			float dAngleX = dPos.y * dt; 
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
			AGStateManager::getInstance().setRotating( true );
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

			m_at -= right * dPos.x * m_sensX; 
			m_at += up * dPos.y * m_sensY;
			m_eye -= right * dPos.x * m_sensX; 
			m_eye += up * dPos.y * m_sensY;
			AGStateManager::getInstance().setRotating( false );
		}
	}
	else if( rmb )
	{
		float dAngleY = dPos.x * dt;
		float dAngleX = dPos.y * dt; 
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

		AGStateManager::getInstance().setRotating( true );
	}
	if( horSpeed != 0 || vertSpeed != 0 )
	{
		D3DXVECTOR3 vec = m_eye - m_at; 
		D3DXVec3Normalize( &vec, &vec );
		D3DXVECTOR3 rightVec( 1.0, 0.0f, 0.0f );
		D3DXMATRIX rotMatrix; 
		D3DXMatrixIdentity( &rotMatrix );
		D3DXMatrixRotationYawPitchRoll( &rotMatrix, m_angleY, 0.0f, 0.0f );

		D3DXVec3TransformCoord( &rightVec, &rightVec, &rotMatrix );
		rightVec *= -horSpeed * m_speed; 
		vec *= ( AGInput().isKeyPressed( "Shift" ) ? -m_sprintSpeed : -m_speed ) * vertSpeed; 
		m_eye += vec;
		m_eye += rightVec;
		m_at += vec; 
		m_at += rightVec;
		AGStateManager::getInstance().setRotating( false );
	}
	D3DXMatrixLookAtLH( &m_viewMatrix, &m_eye, &m_at, &m_up );
}

float AGDXCamera::getAngleX() const
{
	return m_angleX;
}

float AGDXCamera::getAngleY() const
{
	return m_angleY;
}

D3DXVECTOR3 AGDXCamera::getDir()
{
	D3DXVECTOR3 dir = m_at - m_eye; 
	D3DXVec3Normalize( &dir, &dir );
	return dir; 
}
