#include "AGMovable.h"

AGMovable::AGMovable()
{
	D3DXMatrixIdentity( &m_pivotMatrix );
	D3DXMatrixIdentity( &m_translMatrix );
	D3DXMatrixIdentity( &m_rotMatrix );

	D3DXMatrixIdentity( &m_local );
	D3DXMatrixIdentity( &m_localTranslMatrix );
	D3DXMatrixIdentity( &m_localScaleMatrix );
	D3DXMatrixIdentity( &m_localRotMatrix );

	D3DXMatrixIdentity( &m_world );
	D3DXMatrixIdentity( &m_worldTranslMatrix );
	D3DXMatrixIdentity( &m_worldScaleMatrix );
	D3DXMatrixIdentity( &m_worldRotMatrix );

	m_pivot      = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	m_pos        = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	m_rot        = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );

	m_localPos   = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	m_localAngle = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	m_localScale = D3DXVECTOR3( 1.0f, 1.0f, 1.0f );

	m_worldPos   = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	m_worldAngle = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	m_worldScale = D3DXVECTOR3( 1.0f, 1.0f, 1.0f );

	m_updateLocalMatrix = false; 
	m_updateWorldMatrix = false; 
}

AGMovable::~AGMovable()
{

}

void AGMovable::setPivot(D3DXVECTOR3 pivot)
{
	m_pivot = -pivot;
	D3DXMatrixIdentity( &m_pivotMatrix );
	D3DXMatrixTranslation( &m_pivotMatrix, m_pivot.x, m_pivot.y, m_pivot.z );
}

void AGMovable::setPivot(float x, float y, float z)
{
	setPivot( D3DXVECTOR3( x, y, z ) );
}

D3DXVECTOR3 AGMovable::getPivot()
{
	return m_pivot; 
}

void AGMovable::setLocalPos( D3DXVECTOR3 pos )
{
	m_updateLocalMatrix = true; 
	m_localPos = pos; 

	D3DXMatrixTranslation( &m_localTranslMatrix, m_localPos.x, m_localPos.y, m_localPos.z );

	handleChanges( LocalTrans );
}

void AGMovable::setLocalPos(float x, float y, float z)
{
	m_localPos = D3DXVECTOR3( x, y, z );
	setLocalPos( m_localPos );
}

D3DXVECTOR3 AGMovable::getLocalPos() const
{
	return m_localPos; 
}

void AGMovable::setWorldPos(D3DXVECTOR3 pos)
{
	/*m_updateWorldMatrix = true;
	m_worldPos = pos;
	//D3DXMatrixIdentity( &m_worldTranslMatrix );
	D3DXMatrixTranslation( &m_worldTranslMatrix, m_worldPos.x, m_worldPos.y, m_worldPos.z );

	//m_translMatrix *= m_worldTranslMatrix; 

	handleChanges( WorldTrans );*/

	//При учёте того, что у нас нет родителей TODO: Сделать зависимость 
	m_updateLocalMatrix = true; 
	m_localPos = pos; 

	D3DXMatrixTranslation( &m_localTranslMatrix, m_localPos.x, m_localPos.y, m_localPos.z );

	handleChanges( LocalTrans );
}

void AGMovable::setWorldPos(float x, float y, float z)
{
	m_worldPos = D3DXVECTOR3( x, y ,z);
	setWorldPos( m_worldPos ); 
}

D3DXVECTOR3 AGMovable::getWorldPos() const
{
	return m_worldPos; 
}

void AGMovable::translateLocal(D3DXVECTOR3 pos)
{
	m_localPos += pos; 
	setLocalPos( m_localPos );
}

void AGMovable::translateLocal(float x, float y, float z)
{
	m_localPos += D3DXVECTOR3( x, y, z );
	setLocalPos( m_localPos );
}

void AGMovable::translateWorld(D3DXVECTOR3 pos)
{
	m_worldPos += pos;
	setWorldPos( m_worldPos );
}

void AGMovable::translateWorld(float x, float y, float z)
{
	m_worldPos += D3DXVECTOR3( x, y, z );
	setWorldPos( m_worldPos );
}

void AGMovable::setLocalAngle( D3DXVECTOR3 angles )
{
	m_updateWorldMatrix = true;
	m_localAngle = angles;
	D3DXMatrixRotationYawPitchRoll( &m_localRotMatrix, angles.y, angles.x, angles.z );
	handleChanges( LocalRot );
}

void AGMovable::setLocalAngle( float x, float y, float z )
{
	m_localAngle = D3DXVECTOR3( x, y, z );
	setLocalAngle( m_localAngle );
}

void AGMovable::setWorldAngle(D3DXVECTOR3 angle)
{
	m_updateWorldMatrix = true;
	m_worldAngle = angle;
	D3DXMatrixRotationYawPitchRoll( &m_worldRotMatrix, angle.y, angle.x, angle.z );
	handleChanges( WorldRot );
}

void AGMovable::setWorldAngle(float x, float y, float z)
{
	m_worldAngle = D3DXVECTOR3( x, y, z );
	setWorldAngle( m_worldAngle );
}

D3DXVECTOR3 AGMovable::getWorldAngle() const
{
	return m_worldAngle; 
}

void AGMovable::rotateLocalAxis(D3DXVECTOR3 axis, float angle)
{
	D3DXMATRIX rotMatrix; 
	D3DXMatrixRotationAxis( &rotMatrix, &axis, angle );
	m_localRotMatrix *= rotMatrix;
	handleChanges( LocalRot );
}

void AGMovable::rotateLocalX(float angle)
{
	m_updateLocalMatrix = true; 
	D3DXMATRIX rotX; 

	D3DXMatrixRotationX( &rotX, angle );
	m_localAngle.x += angle;
	m_localRotMatrix = rotX * m_localRotMatrix; 
	handleChanges( LocalRot );
}

void AGMovable::rotateLocalY(float angle)
{
	m_updateLocalMatrix = true; 
	D3DXMATRIX rotY; 

	D3DXMatrixRotationY( &rotY, angle );
	m_localAngle.y += angle;
	m_localRotMatrix = rotY * m_localRotMatrix; 
	handleChanges( LocalRot );
}

void AGMovable::rotateLocalZ(float angle)
{
	m_updateLocalMatrix = true; 
	D3DXMATRIX rotZ; 

	D3DXMatrixRotationZ( &rotZ, angle );
	m_localAngle.z += angle;
	m_localRotMatrix = rotZ * m_localRotMatrix; 
	handleChanges( LocalRot );
}

void AGMovable::rotateLocal(D3DXVECTOR3 angle)
{
	m_localAngle += angle;
	setLocalAngle( m_localAngle );
}

void AGMovable::rotateLocal(float x, float y, float z)
{
	m_localAngle += D3DXVECTOR3( x, y, z );
	setLocalAngle( m_localAngle );
}


void AGMovable::rotateWorldAxis(D3DXVECTOR3 axis, float angle)
{
	D3DXMatrixRotationAxis( &m_worldRotMatrix, &axis, angle );
}

void AGMovable::rotateAroundWorldX(float angle)
{
	m_updateWorldMatrix = true; 
	D3DXMATRIX rotX; 

	D3DXVECTOR3 xAxis( 1.0f, 0.0f, 0.0f );

	D3DXMatrixRotationAxis( &rotX, &xAxis, angle );

	m_worldAngle.x += angle;
	m_worldRotMatrix = m_worldRotMatrix * rotX; 
	handleChanges( WorldRot );
}

void AGMovable::rotateAroundWorldY(float angle)
{
	m_updateWorldMatrix = true; 
	D3DXMATRIX rotY; 

	D3DXVECTOR3 yAxis( 0.0f, 1.0f, 0.0f );

	D3DXMatrixRotationAxis( &rotY, &yAxis, angle );

	m_worldAngle.y += angle;
	m_worldRotMatrix = m_worldRotMatrix * rotY; 
	handleChanges( WorldRot );
}

void AGMovable::rotateAroundWorldZ(float angle)
{
	m_updateWorldMatrix = true; 
	D3DXMATRIX rotZ; 

	D3DXVECTOR3 zAxis( 0.0f, 0.0f, 1.0f );

	D3DXMatrixRotationAxis( &rotZ, &zAxis, angle );

	m_worldAngle.z += angle;
	m_worldRotMatrix = m_worldRotMatrix * rotZ; 
	handleChanges( WorldRot );
}

void AGMovable::rotateWorldX(float angle)
{
	m_updateWorldMatrix = true; 
	D3DXMATRIX rotX; 

	D3DXMatrixRotationY( &rotX, angle );
	m_worldAngle.x += angle;
	m_worldRotMatrix = rotX * m_worldRotMatrix; 
	handleChanges( WorldRot );
}

void AGMovable::rotateWorldY(float angle)
{
	m_updateWorldMatrix = true; 
	D3DXMATRIX rotY; 

	D3DXMatrixRotationY( &rotY, angle );
	m_worldAngle.y += angle;
	m_worldRotMatrix = rotY * m_worldRotMatrix; 
	handleChanges( WorldRot );
}

void AGMovable::rotateWorldZ(float angle)
{
	m_updateWorldMatrix = true; 
	D3DXMATRIX rotZ; 

	D3DXMatrixRotationZ( &rotZ, angle );
	m_worldAngle.z += angle;
	m_worldRotMatrix = rotZ * m_worldRotMatrix; 
	handleChanges( WorldRot );
}

void AGMovable::rotateWorld(D3DXVECTOR3 angle)
{
	m_worldAngle += angle; 
	setWorldAngle( m_worldAngle );
}

void AGMovable::rotateWorld(float x, float y, float z)
{
	m_worldAngle += D3DXVECTOR3( x, y, z );
	setWorldAngle( m_worldAngle );
}

D3DXVECTOR3 AGMovable::getLocalAngle() const
{
	return m_localAngle;
}

void AGMovable::setLocalScale( D3DXVECTOR3 scale )
{
	m_updateLocalMatrix = true; 
	m_localScale = scale; 
	D3DXMatrixIdentity( &m_localScaleMatrix );
	D3DXMatrixScaling( &m_localScaleMatrix, scale.x, scale.y, scale.z );
	handleChanges( LocalScale );
}

void AGMovable::setLocalScale( float x, float y, float z )
{
	m_localScale = D3DXVECTOR3( x, y, z );
	setLocalScale( m_localScale );
}

D3DXVECTOR3 AGMovable::getLocalScale() const
{
	return m_localScale; 
}

void AGMovable::setWorldScale(D3DXVECTOR3 factor)
{
	m_updateWorldMatrix = true; 
	m_worldScale = factor; 
	D3DXMatrixIdentity( &m_worldScaleMatrix );
	D3DXMatrixScaling( &m_worldScaleMatrix, factor.x, factor.y, factor.z ); 
	handleChanges( WorldScale );
}	

void AGMovable::setWorldScale(float x, float y, float z)
{
	m_worldScale = D3DXVECTOR3( x, y, z );
	setWorldScale( m_worldScale );
}

D3DXVECTOR3 AGMovable::getWorldScale() const
{
	return m_worldScale; 
}

void AGMovable::scaleLocal(D3DXVECTOR3 factor)
{
	m_localScale += factor;
	setLocalScale( m_localScale );
}

void AGMovable::scaleLocal(float x, float y, float z)
{
	m_localScale += D3DXVECTOR3( x, y, z );
	setLocalScale( m_localScale );
}

void AGMovable::scaleWorld(D3DXVECTOR3 factor)
{
	m_worldScale += factor;
	setWorldScale( m_worldScale );
}

void AGMovable::scaleWorld(float x, float y, float z)
{
	m_worldScale += D3DXVECTOR3( x, y, z );
	setWorldScale( m_worldScale );
}

void AGMovable::setLocalMatrix(D3DXMATRIX world)
{
	m_local = world; 
	m_updateLocalMatrix = false; 
	handleChanges( Local );
}

D3DXMATRIX AGMovable::getLocalMatrix()
{
	if( m_updateLocalMatrix )
	{
		m_local = m_localScaleMatrix * m_localRotMatrix * m_localTranslMatrix; 
	}
	return m_local;
}

void AGMovable::setLocalTranslMatrix(D3DXMATRIX transl)
{
	m_localTranslMatrix = transl;
	handleChanges( LocalTrans );
}

D3DXMATRIX AGMovable::getLocalTranslMatrix()
{
	return m_localTranslMatrix; 
}

void AGMovable::setLocalRotMatrix(D3DXMATRIX rot)
{
	m_localRotMatrix = rot; 
	handleChanges( LocalRot );
}

D3DXMATRIX AGMovable::getLocalRotMatrix()
{
	return m_localRotMatrix;
}

void AGMovable::setLocalScaleMatrix(D3DXMATRIX scale)
{
	m_localScaleMatrix = scale; 
	handleChanges( LocalScale );
}

D3DXMATRIX AGMovable::getLocalScaleMatrix()
{
	return m_localScaleMatrix;
}

void AGMovable::setWorldMatrix(D3DXMATRIX world)
{
	m_world = world; 
	m_updateWorldMatrix = false; 
	handleChanges( World );
}

D3DXMATRIX AGMovable::getWorldMatrix()
{
	if( m_updateWorldMatrix )
	{
		m_world = m_worldScaleMatrix * m_worldRotMatrix * m_worldTranslMatrix;
	}
	return m_world;
}

void AGMovable::setWorldTranslMatrix(D3DXMATRIX transl)
{
	m_worldTranslMatrix = transl; 
	handleChanges( WorldTrans );
}

D3DXMATRIX AGMovable::getWorldTranslMatrix()
{
	return m_worldTranslMatrix;
}	

void AGMovable::setWorldRotMatrix(D3DXMATRIX rot)
{
	m_worldRotMatrix = rot; 
	handleChanges( WorldRot );
}

D3DXMATRIX AGMovable::getWorldRotMatrix()
{
	return m_worldRotMatrix;
}

void AGMovable::setWorldScaleMatrix(D3DXMATRIX scale)
{
	m_worldScaleMatrix = scale; 
	handleChanges( WorldScale );
}

D3DXMATRIX AGMovable::getWorldScaleMatrix()
{
	return m_worldScaleMatrix; 
}

void AGMovable::setResultMatrix(D3DXMATRIX world)
{
	m_world = world;
}

D3DXMATRIX AGMovable::getResultMatrix()
{
	m_matrix = m_localScaleMatrix * m_localRotMatrix *  m_worldRotMatrix * m_worldScaleMatrix * m_localTranslMatrix * m_worldTranslMatrix; 
	//m_matrix = m_rotMatrix * m_translMatrix;

	return m_matrix; 
}

void AGMovable::handleChanges( Changes changes )
{

}
