#include "AGDX10Camera.h"

#include <math.h>

#include "Managers/AGLogger.h"
#include "Managers/AGTimeManager.h"
#include "Managers/AGInputManager.h"

AGDX10Camera::AGDX10Camera()
{
	m_mode = Editor3D;
	m_fov = 70.0f;
	m_aspectRatio = 1.333333333333f;
	m_farPlane = 1000.0f; 
	m_nearPlane = 0.001f; 
	m_sensX = 0.005f; 
	m_sensY = 0.005f; 
	m_speed = 0.1f; 
	m_sprintSpeed = 2.0f; 
	m_up = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
	m_at = D3DXVECTOR3( 0.0f, 0.0f, 1.3f );
	m_eye = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );

	m_angleX = m_angleY = 0.0f;

	D3DXMatrixPerspectiveFovLH( &m_projMatrix, m_fov, m_aspectRatio, m_nearPlane, m_farPlane );
	D3DXMatrixLookAtLH( &m_viewMatrix, &m_eye, &m_at, &m_up );
}

AGDX10Camera::~AGDX10Camera()
{

}

void AGDX10Camera::setManipulator(Manipulator mode)
{
	m_mode = mode; 
}

int AGDX10Camera::getManipulator() const
{
	return m_mode; 
}

void AGDX10Camera::setFov(float fov)
{
	m_fov = fov;
	D3DXMatrixPerspectiveFovLH( &m_projMatrix, m_fov, m_aspectRatio, m_nearPlane, m_farPlane );
}

float AGDX10Camera::getFov() const
{
	return m_fov; 
}

void AGDX10Camera::setAspectRatio(float aspectRatio)
{
	m_aspectRatio = aspectRatio; 
	D3DXMatrixPerspectiveFovLH( &m_projMatrix, m_fov, m_aspectRatio, m_nearPlane, m_farPlane );
}

float AGDX10Camera::getAspectRatio() const
{
	return m_aspectRatio; 
}

void AGDX10Camera::setNearPlane(float nearPlane)
{
	m_nearPlane = nearPlane; 
	D3DXMatrixPerspectiveFovLH( &m_projMatrix, m_fov, m_aspectRatio, m_nearPlane, m_farPlane );
}

float AGDX10Camera::getNearPlane() const
{
	return m_nearPlane; 
}

void AGDX10Camera::setFarPlane(float farPlane)
{
	m_farPlane = farPlane; 
	D3DXMatrixPerspectiveFovLH( &m_projMatrix, m_fov, m_aspectRatio, m_nearPlane, m_farPlane );
}

float AGDX10Camera::getFarPlane() const
{
	return m_farPlane; 
}

void AGDX10Camera::setSpeed(float speed)
{
	m_speed = speed;
}

float AGDX10Camera::getSpeed() const
{
	return m_speed;
}

void AGDX10Camera::setSprintSpeed(float sprintSpeed)
{
	m_sprintSpeed = sprintSpeed;
}

float AGDX10Camera::getSprintSpeed() const
{
	return m_sprintSpeed;
}

void AGDX10Camera::setSensX(float sensX)
{
	m_sensX = sensX; 
}

float AGDX10Camera::getSensX() const
{
	return m_sensX; 
}

void AGDX10Camera::setSensY(float sensY)
{
	m_sensY = sensY; 
}

float AGDX10Camera::getSensY() const
{
	return m_sensY;
}

void AGDX10Camera::setLayer(int layer)
{
	m_layer = layer; 
}

int AGDX10Camera::getLayer() const
{
	return m_layer;
}

void AGDX10Camera::setAt(D3DXVECTOR3 at)
{
	m_at = at; 
	D3DXMatrixLookAtLH( &m_viewMatrix, &m_eye, &m_at, &m_up );
}

D3DXVECTOR3 AGDX10Camera::getAt() const
{
	return m_at; 
}

void AGDX10Camera::setUp(D3DXVECTOR3 up)
{
	m_up = up; 
	D3DXMatrixLookAtLH( &m_viewMatrix, &m_eye, &m_at, &m_up );
}

D3DXVECTOR3 AGDX10Camera::getUp() const
{
	return m_up; 
}

void AGDX10Camera::setEye(D3DXVECTOR3 forward)
{
	m_eye = forward; 
	D3DXMatrixLookAtLH( &m_viewMatrix, &m_eye, &m_at, &m_up );
}

D3DXVECTOR3 AGDX10Camera::getEye() const
{
	return m_eye; 
}

D3DXMATRIX AGDX10Camera::getViewMatrix() const
{
	return m_viewMatrix; 
}

D3DXMATRIX AGDX10Camera::getProjMatrix() const
{
	return m_projMatrix; 
}

void AGDX10Camera::update()
{
	switch( m_mode )
	{
		case Editor3D:
			moveAs3DEditor();
		break;
		case FPS:
			moveAsFPS();
		break; 
	}
}

void AGDX10Camera::moveAs3DEditor()
{
	bool mmb = AGInput().isButtonPressed( "MMB" );
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
		D3DXMatrixLookAtLH( &m_viewMatrix, &m_eye, &m_at, &m_up );
	}

	if( mmb )
	{
		if( alt )
		{
			float dAngleY = dPos.x * dt;
			float dAngleX = dPos.y * dt; 
			m_angleY += dAngleY;
			m_angleX += dAngleX;

			D3DXVECTOR3 v( 0.0f, 0.0f, -1.3f );
			D3DXMatrixRotationYawPitchRoll( &m_rotMatrix, 0.0f, m_angleX, 0.0f );
			D3DXVec3TransformCoord( &v, &v, &m_rotMatrix );

			D3DXMatrixRotationYawPitchRoll( &m_rotMatrix, m_angleY, 0.0f, 0.0f );
			D3DXVec3TransformCoord( &v, &v, &m_rotMatrix ); 

			m_eye = m_at + v; 

			D3DXMatrixLookAtLH( &m_viewMatrix, &m_eye, &m_at, &m_up );
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

			m_at -= right * dPos.x * m_sensX; 
			m_at += up * dPos.y * m_sensY;
			m_eye -= right * dPos.x * m_sensX; 
			m_eye += up * dPos.y * m_sensY;

			D3DXMatrixLookAtLH( &m_viewMatrix, &m_eye, &m_at, &m_up );
		}
	}
}

void AGDX10Camera::moveAsFPS()
{

}

float AGDX10Camera::getAngleX() const
{
	return m_angleX;
}

float AGDX10Camera::getAngleY() const
{
	return m_angleY;
}
