#include "AGDXMovable.h"

AGDXMovable::AGDXMovable()
{
	D3DXMatrixIdentity( &m_world );
	D3DXMatrixIdentity( &m_translMatrix );
	D3DXMatrixIdentity( &m_scaleMatrix );
	D3DXMatrixIdentity( &m_rotMatrix );

	m_pos   = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	m_angle = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	m_scale = D3DXVECTOR3( 1.0f, 1.0f, 1.0f );

	m_updateMatrix = false; 
}

AGDXMovable::~AGDXMovable()
{

}

void AGDXMovable::setPos( D3DXVECTOR3 pos )
{
	m_updateMatrix = true; 
	m_pos = pos; 
	D3DXMatrixIdentity( &m_translMatrix );
	D3DXMatrixTranslation( &m_translMatrix, m_pos.x, m_pos.y, m_pos.z );
}

void AGDXMovable::setPos(float x, float y, float z)
{
	m_pos = D3DXVECTOR3( x, y, z );
	setPos( m_pos );
}

void AGDXMovable::translate(D3DXVECTOR3 pos)
{
	m_pos += pos; 
	setPos( m_pos );
}

void AGDXMovable::translate(float x, float y, float z)
{
	m_pos += D3DXVECTOR3( x, y, z );
	setPos( m_pos );
}

D3DXVECTOR3 AGDXMovable::getPos() const
{
	return m_pos; 
}

void AGDXMovable::setAngle( D3DXVECTOR3 angles )
{
	m_updateMatrix = true; 
	m_angle = angles;
	D3DXMatrixIdentity( &m_rotMatrix );
	D3DXMatrixRotationYawPitchRoll( &m_rotMatrix, angles.y, angles.x, angles.z );
}

void AGDXMovable::setAngle( float x, float y, float z )
{
	m_angle = D3DXVECTOR3( x, y, z );
	setAngle( m_angle );
}

void AGDXMovable::rotate(D3DXVECTOR3 angle)
{
	m_angle += angle;
	setAngle( m_angle );
}

void AGDXMovable::rotate(float x, float y, float z)
{
	m_angle += D3DXVECTOR3( x, y, z );
	setAngle( m_angle );
}

D3DXVECTOR3 AGDXMovable::getAngle() const
{
	return m_angle;
}

void AGDXMovable::setScale( D3DXVECTOR3 scale )
{
	m_updateMatrix = true; 
	m_scale = scale; 
	D3DXMatrixIdentity( &m_scaleMatrix );
	D3DXMatrixScaling( &m_scaleMatrix, scale.x, scale.y, scale.z );
}

void AGDXMovable::setScale( float x, float y, float z )
{
	m_scale = D3DXVECTOR3( x, y, z );
	setScale( m_scale );
}

void AGDXMovable::scale(D3DXVECTOR3 factor)
{
	m_scale += factor;
	setScale( m_scale );
}

void AGDXMovable::scale(float x, float y, float z)
{
	m_scale += D3DXVECTOR3( x, y, z );
	setScale( m_scale );
}

D3DXVECTOR3 AGDXMovable::getScale() const
{
	return m_scale; 
}

void AGDXMovable::setWorld(D3DXMATRIX world)
{
	m_world = world; 
	m_updateMatrix = false; 
}

D3DXMATRIX AGDXMovable::getWorld()
{
	if( m_updateMatrix )
	{
		D3DXMatrixIdentity( &m_world );
		m_world *= m_scaleMatrix * m_rotMatrix * m_translMatrix; 
	}
	return m_world;
}
