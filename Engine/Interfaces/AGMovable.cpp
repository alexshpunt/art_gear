#include "AGMovable.h"

#include <d3d10.h>
#include <d3dx10.h>

class AGMovablePrivate
{
	public:
		AGMovablePrivate()
		{
			localScale = AGVec3( 1.0f );
			worldScale = AGVec3( 1.0f );

			forward    = AGVec3::Forward();
			up         = AGVec3::Up();
			right      = AGVec3::Right(); 

			updateLocalMatrix = false; 
			updateWorldMatrix = false; 
		}
		AGVec3 pivot; 
		AGMatrix pivotMatrix; 

		AGVec3 forward;
		AGVec3 up;
		AGVec3 right; 

		AGVec3 pos; 
		AGMatrix translMatrix;
		AGVec3 rot;
		AGMatrix rotMatrix; 

		AGVec3 localPos;
		AGEulerAngles localAngle;
		AGVec3 localScale; 

		AGVec3 worldPos;
		AGEulerAngles worldAngle;
		AGVec3 worldScale; 

		AGMatrix localTranslMatrix;
		AGMatrix localRotMatrix;
		AGMatrix localScaleMatrix; 

		AGMatrix worldTranslMatrix;
		AGMatrix worldRotMatrix;
		AGMatrix worldScaleMatrix; 

		AGMatrix local;
		AGMatrix world;
		AGMatrix matrix; 

		bool updateLocalMatrix; 
		bool updateWorldMatrix; 
		bool updateResMatrix; 
};

AGMovable::AGMovable()
{
	p = new AGMovablePrivate; 
}

AGMovable::~AGMovable()
{
	delete p; 
}

void AGMovable::setPivot(const AGVec3& pivot)
{
	p->pivot = -pivot;
	p->pivotMatrix = AGMatrix::Translation( pivot );
}

const AGVec3& AGMovable::getPivot()
{
	return p->pivot; 
}

void AGMovable::setLocalPos( const AGVec3& pos )
{
	p->updateLocalMatrix = true; 
	p->localPos = pos; 

	p->localTranslMatrix.setTranslate( pos );

	handleChanges( LocalTrans );
}

const AGVec3& AGMovable::getLocalPos() const
{
	return p->localPos; 
}

void AGMovable::setWorldPos(const AGVec3& pos)
{
	/*m_p->updateWorldMatrix = true;
	m_p->worldPos = pos;
	//AGMatrixIdentity( &m_p->worldTranslMatrix );
	AGMatrixTranslation( &m_p->worldTranslMatrix, m_p->worldPos.x, m_p->worldPos.y, m_p->worldPos.z );

	//m_p->translMatrix *= m_p->worldTranslMatrix; 

	handleChanges( WorldTrans );*/

	//При учёте того, что у нас нет родителей TODO: Сделать зависимость 
	p->updateLocalMatrix = true; 
	p->localPos = pos; 
	p->localTranslMatrix.setIdentity(); 
	p->localTranslMatrix.setTranslate( pos );

	handleChanges( LocalTrans );
}

const AGVec3& AGMovable::getWorldPos() const
{
	return p->worldPos; 
}

void AGMovable::translateLocal(const AGVec3& pos)
{
	p->localPos += pos; 
	setLocalPos( p->localPos );
}

void AGMovable::translateWorld(const AGVec3& pos)
{
	p->worldPos += pos;
	setWorldPos( p->worldPos );
}

void AGMovable::setLocalAngle(AGRadians x, AGRadians y, AGRadians z)
{
	p->updateWorldMatrix = true;
	p->localAngle = AGEulerAngles( x, y, z );
	//p->localRotMatrix.setIdentity();
	p->localRotMatrix.setRotate( x, y, z );

	p->forward *= p->localRotMatrix; 
	p->up *= p->localRotMatrix;
	//p->rotMatrix *= p->localRotMatrix; 

	handleChanges( LocalRot );
}

void AGMovable::setLocalAngle(AGDegrees x, AGDegrees y, AGDegrees z)
{
	setLocalAngle( x.toRadians(), y.toRadians(), z.toRadians() );
}

void AGMovable::setLocalAngle(const AGEulerAngles& angles)
{
	setLocalAngle( angles.x, angles.y, angles.z );
}

void AGMovable::setWorldAngle(AGRadians x, AGRadians y, AGRadians z)
{
	p->updateWorldMatrix = true;
	p->worldAngle = AGEulerAngles( x, y, z );
	p->worldRotMatrix.setRotate( x, y, z );
	handleChanges( WorldRot );
}

void AGMovable::setWorldAngle(AGDegrees x, AGDegrees y, AGDegrees z)
{
	setWorldAngle( x.toRadians(), y.toRadians(), z.toRadians() );
}

void AGMovable::setWorldAngle(const AGEulerAngles& angles)
{
	p->worldAngle = angles; 
}

const AGEulerAngles& AGMovable::getWorldAngle() const
{
	return p->worldAngle; 
}

void AGMovable::rotateLocalAxis(const AGVec3& axis, AGRadians angle)
{
	AGMatrix rotMatrix; 
	rotMatrix.setRotate( axis, angle );
	p->localRotMatrix *= rotMatrix;
	handleChanges( LocalRot );
}

void AGMovable::rotateLocalAxis(const AGVec3& axis, AGDegrees angle)
{
	rotateLocalAxis( axis, angle.toRadians() ); 
}

void AGMovable::rotateLocalX(AGRadians angle)
{
	p->updateLocalMatrix = true; 
	AGMatrix rotX; 
	rotX.setRotateX( angle );

	p->localAngle.x += angle;
	p->localRotMatrix = rotX * p->localRotMatrix; 

	handleChanges( LocalRot );
}

void AGMovable::rotateLocalX(AGDegrees angle)
{
	rotateLocalX( angle.toRadians() );
}

void AGMovable::rotateLocalY(AGRadians angle)
{
	p->updateLocalMatrix = true; 
	AGMatrix rotY; 
	rotY.setRotateY( angle );

	p->localAngle.y += angle;
	p->localRotMatrix = rotY * p->localRotMatrix; 
	handleChanges( LocalRot );
}

void AGMovable::rotateLocalY(AGDegrees angle)
{
	rotateLocalY( angle.toRadians() );
}

void AGMovable::rotateLocalZ(AGRadians angle)
{
	p->updateLocalMatrix = true; 
	AGMatrix rotZ; 
	rotZ.setRotateZ( angle );

	p->localAngle.z += angle;
	p->localRotMatrix = rotZ * p->localRotMatrix; 
	handleChanges( LocalRot );
}

void AGMovable::rotateLocalZ(AGDegrees angle)
{
	rotateLocalZ( angle.toRadians() );
}

void AGMovable::rotateLocal(AGRadians x, AGRadians y, AGRadians z)
{
	p->localAngle += AGEulerAngles( x, y, z );
	setLocalAngle( p->localAngle );
}

void AGMovable::rotateLocal(AGDegrees x, AGDegrees y, AGDegrees z)
{
	rotateLocal( x.toRadians(), y.toRadians(), z.toRadians() );
}

void AGMovable::rotateLocal(const AGEulerAngles& angles)
{
	rotateLocal( angles.x, angles.y, angles.z );
}

void AGMovable::rotateWorldAxis(const AGVec3& axis, AGRadians angle)
{
	p->worldRotMatrix.setIdentity(); 
	p->worldRotMatrix.setRotate( axis, angle );
}

void AGMovable::rotateWorldAxis(const AGVec3& axis, AGDegrees angle)
{
	rotateWorldAxis( axis, angle.toRadians() );
}

void AGMovable::rotateAroundWorldX(AGRadians angle)
{
	p->updateWorldMatrix = true; 
	AGMatrix rotX; 
	rotX.setRotate( AGVec3( 1.0f, 0.0f, 0.0f ), angle );

	p->worldAngle.x += angle;
	p->worldRotMatrix = p->worldRotMatrix * rotX; 

	handleChanges( WorldRot );
}

void AGMovable::rotateAroundWorldX(AGDegrees angle)
{
	rotateAroundWorldX( angle.toRadians() );
}

void AGMovable::rotateAroundWorldY(AGRadians angle)
{
	p->updateWorldMatrix = true; 
	AGMatrix rotY; 
	rotY.setRotate( AGVec3( 0.0f, 1.0f, 0.0f ), angle );

	p->worldAngle.y += angle;
	p->worldRotMatrix = p->worldRotMatrix * rotY; 

	handleChanges( WorldRot );
}

void AGMovable::rotateAroundWorldY(AGDegrees angle)
{
	rotateAroundWorldY( angle.toRadians() );
}

void AGMovable::rotateAroundWorldZ(AGRadians angle)
{
	p->updateWorldMatrix = true; 
	AGMatrix rotZ; 
	rotZ.setRotate( AGVec3( 0.0f, 0.0f, 1.0f ), angle );

	p->worldAngle.z += angle;
	p->worldRotMatrix = p->worldRotMatrix * rotZ; 

	handleChanges( WorldRot );
}

void AGMovable::rotateAroundWorldZ(AGDegrees angle)
{
	rotateAroundWorldZ( angle.toRadians() );
}

void AGMovable::rotateWorldX(AGRadians angle)
{
	p->updateWorldMatrix = true; 
	AGMatrix rotX; 
	rotX.setRotateX( angle );

	p->worldAngle.x += angle;
	p->worldRotMatrix = rotX * p->worldRotMatrix; 

	handleChanges( WorldRot );
}

void AGMovable::rotateWorldX(AGDegrees angle)
{
	rotateWorldX( angle.toRadians() );
}

void AGMovable::rotateWorldY(AGRadians angle)
{
	p->updateWorldMatrix = true; 
	AGMatrix rotY; 
	rotY.setRotateY( angle );

	p->worldAngle.y += angle;
	p->worldRotMatrix = rotY * p->worldRotMatrix; 

	handleChanges( WorldRot );
}

void AGMovable::rotateWorldY(AGDegrees angle)
{
	rotateWorldY( angle.toRadians() );
}

void AGMovable::rotateWorldZ(AGRadians angle)
{
	p->updateWorldMatrix = true; 
	AGMatrix rotZ; 
	rotZ.setRotateZ( angle );

	p->worldAngle.z += angle;
	p->worldRotMatrix = rotZ * p->worldRotMatrix; 

	handleChanges( WorldRot );
}

void AGMovable::rotateWorldZ(AGDegrees angle)
{
	rotateWorldZ( angle.toRadians() );
}

void AGMovable::rotateWorld(AGRadians x, AGRadians y, AGRadians z)
{
	p->worldAngle += AGEulerAngles( x, y, z );
	setWorldAngle( p->worldAngle );
}

void AGMovable::rotateWorld(AGDegrees x, AGDegrees y, AGDegrees z)
{
	rotateWorld( x.toRadians(), y.toRadians(), z.toRadians() );
}

const AGEulerAngles& AGMovable::getLocalAngle() const
{
	return p->localAngle;
}

void AGMovable::setLocalScale( const AGVec3& scale )
{
	p->updateLocalMatrix = true; 
	p->localScale = scale; 
	p->localScaleMatrix.setIdentity();
	p->localScaleMatrix.setScale( scale );

	handleChanges( LocalScale );
}


const AGVec3& AGMovable::getLocalScale() const
{
	return p->localScale; 
}

void AGMovable::setWorldScale(const AGVec3& factor)
{
	p->updateWorldMatrix = true; 
	p->worldScale = factor; 
	p->worldScaleMatrix.setIdentity();
	p->worldScaleMatrix.setScale( factor );

	handleChanges( WorldScale );
}	


const AGVec3& AGMovable::getWorldScale() const
{
	return p->worldScale; 
}

void AGMovable::scaleLocal(const AGVec3& factor)
{
	p->localScale += factor;
	setLocalScale( p->localScale );
}

void AGMovable::scaleWorld(const AGVec3& factor)
{
	p->worldScale += factor;
	setWorldScale( p->worldScale );
}

void AGMovable::setLocalMatrix( const AGMatrix& world)
{
	p->local = world; 
	p->updateLocalMatrix = false; 
	handleChanges( Local );
}

const AGMatrix& AGMovable::getLocalMatrix()
{
	if( p->updateLocalMatrix )
	{
		p->local = p->localScaleMatrix * p->localRotMatrix * p->localTranslMatrix; 
	}
	return p->local;
}

void AGMovable::setLocalTranslMatrix(const AGMatrix& transl)
{
	p->localTranslMatrix = transl;
	handleChanges( LocalTrans );
}

const AGMatrix& AGMovable::getLocalTranslMatrix()
{
	return p->localTranslMatrix; 
}

void AGMovable::setLocalRotMatrix(const AGMatrix& rot)
{
	p->localRotMatrix = rot; 
	handleChanges( LocalRot );
}

const AGMatrix& AGMovable::getLocalRotMatrix()
{
	return p->localRotMatrix;
}

void AGMovable::setLocalScaleMatrix(const AGMatrix& scale)
{
	p->localScaleMatrix = scale; 
	handleChanges( LocalScale );
}

const AGMatrix& AGMovable::getLocalScaleMatrix()
{
	return p->localScaleMatrix;
}

void AGMovable::setWorldMatrix(const AGMatrix& world)
{
	p->world = world; 
	p->updateWorldMatrix = false; 
	handleChanges( World );
}

const AGMatrix& AGMovable::getWorldMatrix()
{
	if( p->updateWorldMatrix )
	{
		p->world = p->worldScaleMatrix * p->worldRotMatrix * p->worldTranslMatrix;
	}
	return p->world;
}

void AGMovable::setWorldTranslMatrix(const AGMatrix& transl)
{
	p->worldTranslMatrix = transl; 
	handleChanges( WorldTrans );
}

const AGMatrix& AGMovable::getWorldTranslMatrix()
{
	return p->worldTranslMatrix;
}	

void AGMovable::setWorldRotMatrix(const AGMatrix& rot)
{
	p->worldRotMatrix = rot; 
	handleChanges( WorldRot );
}

const AGMatrix& AGMovable::getWorldRotMatrix()
{
	return p->worldRotMatrix;
}

void AGMovable::setWorldScaleMatrix(const AGMatrix& scale)
{
	p->worldScaleMatrix = scale; 
	handleChanges( WorldScale );
}

const AGMatrix& AGMovable::getWorldScaleMatrix()
{
	return p->worldScaleMatrix; 
}

void AGMovable::setResultMatrix(const AGMatrix& world)
{
	p->world = world;
}

const AGMatrix& AGMovable::getResultMatrix()
{
	if( p->updateResMatrix )
		p->matrix = p->localScaleMatrix * p->localRotMatrix *  p->worldRotMatrix * p->worldScaleMatrix * p->localTranslMatrix * p->worldTranslMatrix; 

	return p->matrix; 
}

void AGMovable::setLookAt(const AGVec3& dir)
{
	
	float cosA = AGVec3::dot( dir, p->up ); 
	float angle = acos( cosA );

	AGVec3 axis = AGVec3::cross( dir, p->up );

	D3DXMATRIX rotMat; 
	D3DXMatrixIdentity( &rotMat );

	D3DXVECTOR3 vaxis( axis );

	D3DXMatrixRotationAxis( &rotMat, &vaxis, angle );


	p->localRotMatrix = AGMatrix::RotationX( AGDegrees( 90.0f ) ) * AGMatrix::LookAtLH( p->worldPos, dir, p->up ).inversed();

	/*p->localRotMatrix.setIdentity(); 
	p->localRotMatrix.setRotate( axis, AGRadians( angle ) );*/

}







