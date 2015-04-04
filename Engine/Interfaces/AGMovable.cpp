#include "AGMovable.h"

class AGMovablePrivate
{
	public:
		AGMovablePrivate()
		{
			D3DXMatrixIdentity( &pivotMatrix );
			D3DXMatrixIdentity( &translMatrix );
			D3DXMatrixIdentity( &rotMatrix );

			D3DXMatrixIdentity( &local );
			D3DXMatrixIdentity( &localTranslMatrix );
			D3DXMatrixIdentity( &localScaleMatrix );
			D3DXMatrixIdentity( &localRotMatrix );

			D3DXMatrixIdentity( &world );
			D3DXMatrixIdentity( &worldTranslMatrix );
			D3DXMatrixIdentity( &worldScaleMatrix );
			D3DXMatrixIdentity( &worldRotMatrix );

			pivot      = AGVec3( 0.0f, 0.0f, 0.0f );
			pos        = AGVec3( 0.0f, 0.0f, 0.0f );
			rot        = AGVec3( 0.0f, 0.0f, 0.0f );

			localPos   = AGVec3( 0.0f, 0.0f, 0.0f );
			localAngle = AGVec3( 0.0f, 0.0f, 0.0f );
			localScale = AGVec3( 1.0f, 1.0f, 1.0f );

			worldPos   = AGVec3( 0.0f, 0.0f, 0.0f );
			worldAngle = AGVec3( 0.0f, 0.0f, 0.0f );
			worldScale = AGVec3( 1.0f, 1.0f, 1.0f );

			forward    = AGVec3::getForward();
			up         = AGVec3::getUp();
			right      = AGVec3::getRight(); 

			updateLocalMatrix = false; 
			updateWorldMatrix = false; 
		}
		AGVec3 pivot; 
		D3DXMATRIX pivotMatrix; 

		AGVec3 forward;
		AGVec3 up;
		AGVec3 right; 

		AGVec3 pos; 
		D3DXMATRIX translMatrix;
		AGVec3 rot;
		D3DXMATRIX rotMatrix; 

		AGVec3 localPos;
		AGVec3 localAngle;
		AGVec3 localScale; 

		AGVec3 worldPos;
		AGVec3 worldAngle;
		AGVec3 worldScale; 

		D3DXMATRIX localTranslMatrix;
		D3DXMATRIX localRotMatrix;
		D3DXMATRIX localScaleMatrix; 

		D3DXMATRIX worldTranslMatrix;
		D3DXMATRIX worldRotMatrix;
		D3DXMATRIX worldScaleMatrix; 

		D3DXMATRIX local;
		D3DXMATRIX world;
		D3DXMATRIX matrix; 

		bool updateLocalMatrix; 
		bool updateWorldMatrix; 
		bool updateResMatrix; 
};

AGMovable::AGMovable()
{
	m_p->p = new AGMovablePrivate; 
}

AGMovable::~AGMovable()
{

}

void AGMovable::setPivot(const AGVec3& pivot)
{
	m_p->pivot = -pivot;
	D3DXMatrixIdentity( &m_p->pivotMatrix );
	D3DXMatrixTranslation( &m_p->pivotMatrix, m_p->pivot.x, m_p->pivot.y, m_p->pivot.z );
}

void AGMovable::setPivot(float x, float y, float z)
{
	setPivot( const AGVec3&( x, y, z ) );
}

const AGVec3& AGMovable::getPivot()
{
	return m_p->pivot; 
}

void AGMovable::setLocalPos( const AGVec3& pos )
{
	m_p->p->updateLocalMatrix = true; 
	m_p->p->localPos = pos; 

	D3DXMatrixTranslation( &m_p->p.localTranslMatrix, m_p->localPos.x, m_p->localPos.y, m_p->localPos.z );

	handleChanges( LocalTrans );
}

void AGMovable::setLocalPos(float x, float y, float z)
{
	m_p->localPos = const AGVec3&( x, y, z );
	setLocalPos( m_p->localPos );
}

const AGVec3& AGMovable::getLocalPos() const
{
	return m_p->localPos; 
}

void AGMovable::setWorldPos(const AGVec3& pos)
{
	/*m_p->updateWorldMatrix = true;
	m_p->worldPos = pos;
	//D3DXMatrixIdentity( &m_p->worldTranslMatrix );
	D3DXMatrixTranslation( &m_p->worldTranslMatrix, m_p->worldPos.x, m_p->worldPos.y, m_p->worldPos.z );

	//m_p->translMatrix *= m_p->worldTranslMatrix; 

	handleChanges( WorldTrans );*/

	//При учёте того, что у нас нет родителей TODO: Сделать зависимость 
	m_p->updateLocalMatrix = true; 
	m_p->localPos = pos; 

	D3DXMatrixTranslation( &m_p->localTranslMatrix, m_p->localPos.x, m_p->localPos.y, m_p->localPos.z );

	handleChanges( LocalTrans );
}

void AGMovable::setWorldPos(float x, float y, float z)
{
	m_p->worldPos = AGVec3( x, y ,z);
	setWorldPos( m_p->worldPos ); 
}

const AGVec3& AGMovable::getWorldPos() const
{
	return m_p->worldPos; 
}

void AGMovable::translateLocal(const AGVec3& pos)
{
	m_p->localPos += pos; 
	setLocalPos( m_p->localPos );
}

void AGMovable::translateLocal(float x, float y, float z)
{
	m_p->localPos += AGVec3( x, y, z );
	setLocalPos( m_p->localPos );
}

void AGMovable::translateWorld(const AGVec3& pos)
{
	m_p->worldPos += pos;
	setWorldPos( m_p->worldPos );
}

void AGMovable::translateWorld(float x, float y, float z)
{
	m_p->worldPos += AGVec3( x, y, z );
	setWorldPos( m_p->worldPos );
}

void AGMovable::setLocalAngle( const AGVec3& angles )
{
	m_p->updateWorldMatrix = true;
	m_p->localAngle = angles;
	D3DXMatrixRotationYawPitchRoll( &m_p->localRotMatrix, angles.y, angles.x, angles.z );

	D3DXVec3TransformCoord( &m_p->forward, &m_p->forward, &m_p->localRotMatrix );
	D3DXVec3TransformCoord( &m_p->up, &m_p->up, &m_p->localRotMatrix );
	D3DXVec3TransformCoord( &m_p->right, &m_p->right, &m_p->localRotMatrix );

	handleChanges( LocalRot );
}

void AGMovable::setLocalAngle( float x, float y, float z )
{
	m_p->localAngle = const AGVec3&( x, y, z );
	setLocalAngle( m_p->localAngle );
}

void AGMovable::setWorldAngle(const AGVec3& angle)
{
	m_p->updateWorldMatrix = true;
	m_p->worldAngle = angle;
	D3DXMatrixRotationYawPitchRoll( &m_p->worldRotMatrix, angle.y, angle.x, angle.z );
	handleChanges( WorldRot );
}

void AGMovable::setWorldAngle(float x, float y, float z)
{
	m_p->worldAngle = const AGVec3&( x, y, z );
	setWorldAngle( m_p->worldAngle );
}

const AGVec3& AGMovable::getWorldAngle() const
{
	return m_p->worldAngle; 
}

void AGMovable::rotateLocalAxis(const AGVec3& axis, float angle)
{
	D3DXMATRIX rotMatrix; 
	D3DXMatrixRotationAxis( &rotMatrix, &axis, angle );
	m_p->localRotMatrix *= rotMatrix;
	handleChanges( LocalRot );
}

void AGMovable::rotateLocalX(float angle)
{
	m_p->updateLocalMatrix = true; 
	D3DXMATRIX rotX; 

	D3DXMatrixRotationX( &rotX, angle );
	m_p->localAngle.x += angle;
	m_p->localRotMatrix = rotX * m_p->localRotMatrix; 
	handleChanges( LocalRot );
}

void AGMovable::rotateLocalY(float angle)
{
	m_p->updateLocalMatrix = true; 
	D3DXMATRIX rotY; 

	D3DXMatrixRotationY( &rotY, angle );
	m_p->localAngle.y += angle;
	m_p->localRotMatrix = rotY * m_p->localRotMatrix; 
	handleChanges( LocalRot );
}

void AGMovable::rotateLocalZ(float angle)
{
	m_p->updateLocalMatrix = true; 
	D3DXMATRIX rotZ; 

	D3DXMatrixRotationZ( &rotZ, angle );
	m_p->localAngle.z += angle;
	m_p->localRotMatrix = rotZ * m_p->localRotMatrix; 
	handleChanges( LocalRot );
}

void AGMovable::rotateLocal(const AGVec3& angle)
{
	m_p->localAngle += angle;
	setLocalAngle( m_p->localAngle );
}

void AGMovable::rotateLocal(float x, float y, float z)
{
	m_p->localAngle += const AGVec3&( x, y, z );
	setLocalAngle( m_p->localAngle );
}


void AGMovable::rotateWorldAxis(const AGVec3& axis, float angle)
{
	D3DXMatrixRotationAxis( &m_p->worldRotMatrix, &axis, angle );
}

void AGMovable::rotateAroundWorldX(float angle)
{
	m_p->updateWorldMatrix = true; 
	D3DXMATRIX rotX; 

	const AGVec3& xAxis( 1.0f, 0.0f, 0.0f );

	D3DXMatrixRotationAxis( &rotX, &xAxis, angle );

	m_p->worldAngle.x += angle;
	m_p->worldRotMatrix = m_p->worldRotMatrix * rotX; 
	handleChanges( WorldRot );
}

void AGMovable::rotateAroundWorldY(float angle)
{
	m_p->updateWorldMatrix = true; 
	D3DXMATRIX rotY; 

	const AGVec3& yAxis( 0.0f, 1.0f, 0.0f );

	D3DXMatrixRotationAxis( &rotY, &yAxis, angle );

	m_p->worldAngle.y += angle;
	m_p->worldRotMatrix = m_p->worldRotMatrix * rotY; 
	handleChanges( WorldRot );
}

void AGMovable::rotateAroundWorldZ(float angle)
{
	m_p->updateWorldMatrix = true; 
	D3DXMATRIX rotZ; 

	const AGVec3& zAxis( 0.0f, 0.0f, 1.0f );

	D3DXMatrixRotationAxis( &rotZ, &zAxis, angle );

	m_p->worldAngle.z += angle;
	m_p->worldRotMatrix = m_p->worldRotMatrix * rotZ; 
	handleChanges( WorldRot );
}

void AGMovable::rotateWorldX(float angle)
{
	m_p->updateWorldMatrix = true; 
	D3DXMATRIX rotX; 

	D3DXMatrixRotationY( &rotX, angle );
	m_p->worldAngle.x += angle;
	m_p->worldRotMatrix = rotX * m_p->worldRotMatrix; 
	handleChanges( WorldRot );
}

void AGMovable::rotateWorldY(float angle)
{
	m_p->updateWorldMatrix = true; 
	D3DXMATRIX rotY; 

	D3DXMatrixRotationY( &rotY, angle );
	m_p->worldAngle.y += angle;
	m_p->worldRotMatrix = rotY * m_p->worldRotMatrix; 
	handleChanges( WorldRot );
}

void AGMovable::rotateWorldZ(float angle)
{
	m_p->updateWorldMatrix = true; 
	D3DXMATRIX rotZ; 

	D3DXMatrixRotationZ( &rotZ, angle );
	m_p->worldAngle.z += angle;
	m_p->worldRotMatrix = rotZ * m_p->worldRotMatrix; 
	handleChanges( WorldRot );
}

void AGMovable::rotateWorld(const AGVec3& angle)
{
	m_p->worldAngle += angle; 
	setWorldAngle( m_p->worldAngle );
}

void AGMovable::rotateWorld(float x, float y, float z)
{
	m_p->worldAngle += const AGVec3&( x, y, z );
	setWorldAngle( m_p->worldAngle );
}

const AGVec3& AGMovable::getLocalAngle() const
{
	return m_p->localAngle;
}

void AGMovable::setLocalScale( const AGVec3& scale )
{
	m_p->updateLocalMatrix = true; 
	m_p->localScale = scale; 
	D3DXMatrixIdentity( &m_p->localScaleMatrix );
	D3DXMatrixScaling( &m_p->localScaleMatrix, scale.x, scale.y, scale.z );
	handleChanges( LocalScale );
}

void AGMovable::setLocalScale( float x, float y, float z )
{
	m_p->localScale = const AGVec3&( x, y, z );
	setLocalScale( m_p->localScale );
}

const AGVec3& AGMovable::getLocalScale() const
{
	return m_p->localScale; 
}

void AGMovable::setWorldScale(const AGVec3& factor)
{
	m_p->updateWorldMatrix = true; 
	m_p->worldScale = factor; 
	D3DXMatrixIdentity( &m_p->worldScaleMatrix );
	D3DXMatrixScaling( &m_p->worldScaleMatrix, factor.x, factor.y, factor.z ); 
	handleChanges( WorldScale );
}	

void AGMovable::setWorldScale(float x, float y, float z)
{
	m_p->worldScale = const AGVec3&( x, y, z );
	setWorldScale( m_p->worldScale );
}

const AGVec3& AGMovable::getWorldScale() const
{
	return m_p->worldScale; 
}

void AGMovable::scaleLocal(const AGVec3& factor)
{
	m_p->localScale += factor;
	setLocalScale( m_p->localScale );
}

void AGMovable::scaleLocal(float x, float y, float z)
{
	m_p->localScale += const AGVec3&( x, y, z );
	setLocalScale( m_p->localScale );
}

void AGMovable::scaleWorld(const AGVec3& factor)
{
	m_p->worldScale += factor;
	setWorldScale( m_p->worldScale );
}

void AGMovable::scaleWorld(float x, float y, float z)
{
	m_p->worldScale += const AGVec3&( x, y, z );
	setWorldScale( m_p->worldScale );
}

void AGMovable::setLocalMatrix(D3DXMATRIX world)
{
	m_p->local = world; 
	m_p->updateLocalMatrix = false; 
	handleChanges( Local );
}

D3DXMATRIX AGMovable::getLocalMatrix()
{
	if( m_p->updateLocalMatrix )
	{
		m_p->local = m_p->localScaleMatrix * m_p->localRotMatrix * m_p->localTranslMatrix; 
	}
	return m_p->local;
}

void AGMovable::setLocalTranslMatrix(D3DXMATRIX transl)
{
	m_p->localTranslMatrix = transl;
	handleChanges( LocalTrans );
}

D3DXMATRIX AGMovable::getLocalTranslMatrix()
{
	return m_p->localTranslMatrix; 
}

void AGMovable::setLocalRotMatrix(D3DXMATRIX rot)
{
	m_p->localRotMatrix = rot; 
	handleChanges( LocalRot );
}

D3DXMATRIX AGMovable::getLocalRotMatrix()
{
	return m_p->localRotMatrix;
}

void AGMovable::setLocalScaleMatrix(D3DXMATRIX scale)
{
	m_p->localScaleMatrix = scale; 
	handleChanges( LocalScale );
}

D3DXMATRIX AGMovable::getLocalScaleMatrix()
{
	return m_p->localScaleMatrix;
}

void AGMovable::setWorldMatrix(D3DXMATRIX world)
{
	m_p->world = world; 
	m_p->updateWorldMatrix = false; 
	handleChanges( World );
}

D3DXMATRIX AGMovable::getWorldMatrix()
{
	if( m_p->updateWorldMatrix )
	{
		m_p->world = m_p->worldScaleMatrix * m_p->worldRotMatrix * m_p->worldTranslMatrix;
	}
	return m_p->world;
}

void AGMovable::setWorldTranslMatrix(D3DXMATRIX transl)
{
	m_p->worldTranslMatrix = transl; 
	handleChanges( WorldTrans );
}

D3DXMATRIX AGMovable::getWorldTranslMatrix()
{
	return m_p->worldTranslMatrix;
}	

void AGMovable::setWorldRotMatrix(D3DXMATRIX rot)
{
	m_p->worldRotMatrix = rot; 
	handleChanges( WorldRot );
}

D3DXMATRIX AGMovable::getWorldRotMatrix()
{
	return m_p->worldRotMatrix;
}

void AGMovable::setWorldScaleMatrix(D3DXMATRIX scale)
{
	m_p->worldScaleMatrix = scale; 
	handleChanges( WorldScale );
}

D3DXMATRIX AGMovable::getWorldScaleMatrix()
{
	return m_p->worldScaleMatrix; 
}

void AGMovable::setResultMatrix(D3DXMATRIX world)
{
	m_p->world = world;
}

D3DXMATRIX AGMovable::getResultMatrix()
{
	if( m_p->updateResMatrix )
		m_p->matrix = m_p->localScaleMatrix * m_p->localRotMatrix *  m_p->worldRotMatrix * m_p->worldScaleMatrix * m_p->localTranslMatrix * m_p->worldTranslMatrix; 

	return m_p->matrix; 
}

void AGMovable::handleChanges( Changes changes )
{

}

void AGMovable::setLookAt(const AGVec3& dir)
{
	float cosA = AGVec3::dot( dir, m_p->up ); 
	float angle = acos( cosA );

	AGVec3 axis = AGVec3::cross( dir, m_p->up );



	/*float cosA = D3DXVec3Dot( &dir, &m_p->up ); 
	float angle = acos( cosA ); 

	AGVec3 axis;
	D3DXVec3Cross( &axis, &dir, &m_p->up ); 

	D3DXMatrixRotationAxis( &m_p->localRotMatrix, &axis, angle ); 

	m_p->up = dir; */
}







