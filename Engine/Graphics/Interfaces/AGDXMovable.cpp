#include "AGDXMovable.h"

AGDXMovable::AGDXMovable()
{
	D3DXMatrixIdentity( &m_local );
	D3DXMatrixIdentity( &m_localTranslMatrix );
	D3DXMatrixIdentity( &m_localScaleMatrix );
	D3DXMatrixIdentity( &m_localRotMatrix );

	D3DXMatrixIdentity( &m_world );
	D3DXMatrixIdentity( &m_worldTranslMatrix );
	D3DXMatrixIdentity( &m_worldScaleMatrix );
	D3DXMatrixIdentity( &m_worldRotMatrix );

	m_localPos   = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	m_localAngle = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	m_localScale = D3DXVECTOR3( 1.0f, 1.0f, 1.0f );

	m_worldPos   = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	m_worldAngle = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	m_worldScale = D3DXVECTOR3( 1.0f, 1.0f, 1.0f );

	m_updateLocalMatrix = false; 
	m_updateWorldMatrix = false; 
}

AGDXMovable::~AGDXMovable()
{

}

void AGDXMovable::setLocalPos( D3DXVECTOR3 pos )
{
	m_updateLocalMatrix = true; 
	m_localPos = pos; 
	D3DXMatrixIdentity( &m_localTranslMatrix );
	D3DXMatrixTranslation( &m_localTranslMatrix, m_localPos.x, m_localPos.y, m_localPos.z );
}

void AGDXMovable::setLocalPos(float x, float y, float z)
{
	m_localPos = D3DXVECTOR3( x, y, z );
	setLocalPos( m_localPos );
}

D3DXVECTOR3 AGDXMovable::getLocalPos() const
{
	return m_localPos; 
}

void AGDXMovable::setWorldPos(D3DXVECTOR3 pos)
{
	m_updateWorldMatrix = true;
	m_worldPos = pos;
	D3DXMatrixIdentity( &m_worldTranslMatrix );
	D3DXMatrixTranslation( &m_worldTranslMatrix, m_worldPos.x, m_worldPos.y, m_worldPos.z );
}

void AGDXMovable::setWorldPos(float x, float y, float z)
{
	m_worldPos = D3DXVECTOR3( x, y ,z);
	setWorldPos( m_worldPos ); 
}

D3DXVECTOR3 AGDXMovable::getWorldPos() const
{
	return m_worldPos; 
}

void AGDXMovable::translateLocal(D3DXVECTOR3 pos)
{
	m_localPos += pos; 
	setLocalPos( m_localPos );
}

void AGDXMovable::translateLocal(float x, float y, float z)
{
	m_localPos += D3DXVECTOR3( x, y, z );
	setLocalPos( m_localPos );
}

void AGDXMovable::translateWorld(D3DXVECTOR3 pos)
{
	m_worldPos += pos;
	setWorldPos( m_worldPos );
}

void AGDXMovable::translateWorld(float x, float y, float z)
{
	m_worldPos += D3DXVECTOR3( x, y, z );
	setWorldPos( m_worldPos );
}

void AGDXMovable::setLocalAngle( D3DXVECTOR3 angles )
{
	m_updateLocalMatrix = true; 
	m_localAngle = angles;
	D3DXMatrixIdentity( &m_localRotMatrix );
	D3DXMatrixRotationYawPitchRoll( &m_localRotMatrix, angles.y, angles.x, angles.z );
}

void AGDXMovable::setLocalAngle( float x, float y, float z )
{
	m_localAngle = D3DXVECTOR3( x, y, z );
	setLocalAngle( m_localAngle );
}

void AGDXMovable::setWorldAngle(D3DXVECTOR3 angle)
{
	m_updateWorldMatrix = true;
	m_worldAngle = angle;
	D3DXMatrixIdentity( &m_worldRotMatrix );
	D3DXMatrixRotationYawPitchRoll( &m_worldRotMatrix, angle.y, angle.x, angle.z );
}

void AGDXMovable::setWorldAngle(float x, float y, float z)
{
	m_worldAngle = D3DXVECTOR3( x, y, z );
	setWorldAngle( m_worldAngle );
}

D3DXVECTOR3 AGDXMovable::getWorldAngle() const
{
	return m_worldAngle; 
}

void AGDXMovable::rotateLocal(D3DXVECTOR3 angle)
{
	m_localAngle += angle;
	setLocalAngle( m_localAngle );
}

void AGDXMovable::rotateLocal(float x, float y, float z)
{
	m_localAngle += D3DXVECTOR3( x, y, z );
	setLocalAngle( m_localAngle );
}

void AGDXMovable::rotateWorld(D3DXVECTOR3 angle)
{
	m_worldAngle += angle; 
	setWorldAngle( m_worldAngle );
}

void AGDXMovable::rotateWorld(float x, float y, float z)
{
	m_worldAngle += D3DXVECTOR3( x, y, z );
	setWorldAngle( m_worldAngle );
}

D3DXVECTOR3 AGDXMovable::getLocalAngle() const
{
	return m_localAngle;
}

void AGDXMovable::setLocalScale( D3DXVECTOR3 scale )
{
	m_updateLocalMatrix = true; 
	m_localScale = scale; 
	D3DXMatrixIdentity( &m_localScaleMatrix );
	D3DXMatrixScaling( &m_localScaleMatrix, scale.x, scale.y, scale.z );
}

void AGDXMovable::setLocalScale( float x, float y, float z )
{
	m_localScale = D3DXVECTOR3( x, y, z );
	setLocalScale( m_localScale );
}

D3DXVECTOR3 AGDXMovable::getLocalScale() const
{
	return m_localScale; 
}

void AGDXMovable::setWorldScale(D3DXVECTOR3 factor)
{
	m_updateWorldMatrix = true; 
	m_worldScale = factor; 
	D3DXMatrixIdentity( &m_worldScaleMatrix );
	D3DXMatrixScaling( &m_worldScaleMatrix, factor.x, factor.y, factor.z ); 
}	

void AGDXMovable::setWorldScale(float x, float y, float z)
{
	m_worldScale = D3DXVECTOR3( x, y, z );
	setWorldScale( m_worldScale );
}

D3DXVECTOR3 AGDXMovable::getWorldScale() const
{
	return m_worldScale; 
}

void AGDXMovable::scaleLocal(D3DXVECTOR3 factor)
{
	m_localScale += factor;
	setLocalScale( m_localScale );
}

void AGDXMovable::scaleLocal(float x, float y, float z)
{
	m_localScale += D3DXVECTOR3( x, y, z );
	setLocalScale( m_localScale );
}

void AGDXMovable::scaleWorld(D3DXVECTOR3 factor)
{
	m_worldScale += factor;
	setWorldScale( m_worldScale );
}

void AGDXMovable::scaleWorld(float x, float y, float z)
{
	m_worldScale += D3DXVECTOR3( x, y, z );
	setWorldScale( m_worldScale );
}

void AGDXMovable::setLocalMatrix(D3DXMATRIX world)
{
	m_local = world; 
	m_updateLocalMatrix = false; 
}

D3DXMATRIX AGDXMovable::getLocalMatrix()
{
	if( m_updateLocalMatrix )
	{
		m_local = m_localScaleMatrix * m_localRotMatrix * m_localTranslMatrix; 
	}
	return m_local;
}

D3DXMATRIX AGDXMovable::getLocalTranslMatrix()
{
	return m_localTranslMatrix; 
}

D3DXMATRIX AGDXMovable::getLocalRotMatrix()
{
	return m_localRotMatrix;
}

D3DXMATRIX AGDXMovable::getLocalScaleMatrix()
{
	return m_localScaleMatrix;
}

void AGDXMovable::setWorldMatrix(D3DXMATRIX world)
{
	m_world = world; 
	m_updateWorldMatrix = false; 
}

D3DXMATRIX AGDXMovable::getWorldMatrix()
{
	if( m_updateWorldMatrix )
	{
		m_world = m_worldScaleMatrix * m_worldRotMatrix * m_worldTranslMatrix;
	}
	return m_world;
}

D3DXMATRIX AGDXMovable::getWorldTranslMatrix()
{
	return m_worldTranslMatrix;
}	

D3DXMATRIX AGDXMovable::getWorldRotMatrix()
{
	return m_worldRotMatrix;
}

D3DXMATRIX AGDXMovable::getWorldScaleMatrix()
{
	return m_worldScaleMatrix; 
}

void AGDXMovable::setResultMatrix(D3DXMATRIX world)
{
	m_world = world;
}

D3DXMATRIX AGDXMovable::getResultMatrix()
{
	m_matrix = m_localScaleMatrix * m_localRotMatrix * m_worldScaleMatrix * m_worldRotMatrix * m_localTranslMatrix * m_worldTranslMatrix; 

	return m_matrix; 
}
