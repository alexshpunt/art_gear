#include "AGMovable.h"

class AGMovablePrivate
{
	public:
		AGMovablePrivate()
		{
			localScale = AGVec3( 1.0f );
			worldScale = AGVec3( 1.0f );

			forward    = AGVec3::getForward();
			up         = AGVec3::getUp();
			right      = AGVec3::getRight(); 

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
		AGVec3 localAngle;
		AGVec3 localScale; 

		AGVec3 worldPos;
		AGVec3 worldAngle;
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

}

void AGMovable::setPivot(const AGVec3& pivot)
{
	p->pivot = -pivot;
	p->pivotMatrix.setIdentity();
	p->pivotMatrix.setTranslate( pivot ); 
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

void AGMovable::setLocalAngle( float x, float y, float z )
{
	p->updateWorldMatrix = true;
	p->localAngle = AGVec3( x, y, z );
	p->localRotMatrix.setIdentity();
	p->localRotMatrix.setRotate( x, y, z );

	p->forward *= p->localRotMatrix; 
	p->up *= p->localRotMatrix;
	p->rotMatrix *= p->localRotMatrix; 

	handleChanges( LocalRot );
}

void AGMovable::setWorldAngle(float x, float y, float z)
{
	p->updateWorldMatrix = true;
	p->worldAngle = AGVec3( x, y, z );
	p->worldRotMatrix.setRotate( x, y, z );
	handleChanges( WorldRot );
}

const AGVec3& AGMovable::getWorldAngle() const
{
	return p->worldAngle; 
}

void AGMovable::rotateLocalAxis(const AGVec3& axis, float angle)
{
	AGMatrix rotMatrix; 
	rotMatrix.setRotate( axis, angle );
	p->localRotMatrix *= rotMatrix;
	handleChanges( LocalRot );
}

void AGMovable::rotateLocalX(float angle)
{
	p->updateLocalMatrix = true; 
	AGMatrix rotX; 
	rotX.setRotateX( angle );

	p->localAngle.x += angle;
	p->localRotMatrix = rotX * p->localRotMatrix; 

	handleChanges( LocalRot );
}

void AGMovable::rotateLocalY(float angle)
{
	p->updateLocalMatrix = true; 
	AGMatrix rotY; 
	rotY.setRotateY( angle );

	p->localAngle.y += angle;
	p->localRotMatrix = rotY * p->localRotMatrix; 
	handleChanges( LocalRot );
}

void AGMovable::rotateLocalZ(float angle)
{
	p->updateLocalMatrix = true; 
	AGMatrix rotZ; 
	rotZ.setRotateZ( angle );

	p->localAngle.z += angle;
	p->localRotMatrix = rotZ * p->localRotMatrix; 
	handleChanges( LocalRot );
}


void AGMovable::rotateLocal(float x, float y, float z)
{
	p->localAngle += const AGVec3&( x, y, z );
	setLocalAngle( p->localAngle );
}


void AGMovable::rotateWorldAxis(const AGVec3& axis, float angle)
{
	p->worldRotMatrix.setIdentity(); 
	p->worldRotMatrix.setRotate( axis, angle );
}

void AGMovable::rotateAroundWorldX(float angle)
{
	p->updateWorldMatrix = true; 
	AGMatrix rotX; 
	rotX.setRotate( AGVec3( 1.0f, 0.0f, 0.0f ), angle );

	p->worldAngle.x += angle;
	p->worldRotMatrix = p->worldRotMatrix * rotX; 

	handleChanges( WorldRot );
}

void AGMovable::rotateAroundWorldY(float angle)
{
	p->updateWorldMatrix = true; 
	AGMatrix rotY; 
	rotY.setRotate( AGVec3( 0.0f, 1.0f, 0.0f ), angle );

	p->worldAngle.y += angle;
	p->worldRotMatrix = p->worldRotMatrix * rotY; 

	handleChanges( WorldRot );
}

void AGMovable::rotateAroundWorldZ(float angle)
{
	p->updateWorldMatrix = true; 
	AGMatrix rotZ; 
	rotZ.setRotate( AGVec3( 0.0f, 0.0f, 1.0f ), angle );

	p->worldAngle.z += angle;
	p->worldRotMatrix = p->worldRotMatrix * rotZ; 

	handleChanges( WorldRot );
}

void AGMovable::rotateWorldX(float angle)
{
	p->updateWorldMatrix = true; 
	AGMatrix rotX; 
	rotX.setRotateX( angle );

	p->worldAngle.x += angle;
	p->worldRotMatrix = rotX * p->worldRotMatrix; 

	handleChanges( WorldRot );
}

void AGMovable::rotateWorldY(float angle)
{
	p->updateWorldMatrix = true; 
	AGMatrix rotY; 
	rotY.setRotateY( angle );

	p->worldAngle.y += angle;
	p->worldRotMatrix = rotY * p->worldRotMatrix; 

	handleChanges( WorldRot );
}

void AGMovable::rotateWorldZ(float angle)
{
	p->updateWorldMatrix = true; 
	AGMatrix rotZ; 
	rotZ.setRotateZ( angle );

	p->worldAngle.z += angle;
	p->worldRotMatrix = rotZ * p->worldRotMatrix; 

	handleChanges( WorldRot );
}

void AGMovable::rotateWorld(float x, float y, float z)
{
	p->worldAngle += const AGVec3&( x, y, z );
	setWorldAngle( p->worldAngle );
}

const AGVec3& AGMovable::getLocalAngle() const
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

void AGMovable::setLocalMatrix(AGMatrix world)
{
	p->local = world; 
	p->updateLocalMatrix = false; 
	handleChanges( Local );
}

AGMatrix AGMovable::getLocalMatrix()
{
	if( p->updateLocalMatrix )
	{
		p->local = p->localScaleMatrix * p->localRotMatrix * p->localTranslMatrix; 
	}
	return p->local;
}

void AGMovable::setLocalTranslMatrix(AGMatrix transl)
{
	p->localTranslMatrix = transl;
	handleChanges( LocalTrans );
}

AGMatrix AGMovable::getLocalTranslMatrix()
{
	return p->localTranslMatrix; 
}

void AGMovable::setLocalRotMatrix(AGMatrix rot)
{
	p->localRotMatrix = rot; 
	handleChanges( LocalRot );
}

AGMatrix AGMovable::getLocalRotMatrix()
{
	return p->localRotMatrix;
}

void AGMovable::setLocalScaleMatrix(AGMatrix scale)
{
	p->localScaleMatrix = scale; 
	handleChanges( LocalScale );
}

AGMatrix AGMovable::getLocalScaleMatrix()
{
	return p->localScaleMatrix;
}

void AGMovable::setWorldMatrix(AGMatrix world)
{
	p->world = world; 
	p->updateWorldMatrix = false; 
	handleChanges( World );
}

AGMatrix AGMovable::getWorldMatrix()
{
	if( p->updateWorldMatrix )
	{
		p->world = p->worldScaleMatrix * p->worldRotMatrix * p->worldTranslMatrix;
	}
	return p->world;
}

void AGMovable::setWorldTranslMatrix(AGMatrix transl)
{
	p->worldTranslMatrix = transl; 
	handleChanges( WorldTrans );
}

AGMatrix AGMovable::getWorldTranslMatrix()
{
	return p->worldTranslMatrix;
}	

void AGMovable::setWorldRotMatrix(AGMatrix rot)
{
	p->worldRotMatrix = rot; 
	handleChanges( WorldRot );
}

AGMatrix AGMovable::getWorldRotMatrix()
{
	return p->worldRotMatrix;
}

void AGMovable::setWorldScaleMatrix(AGMatrix scale)
{
	p->worldScaleMatrix = scale; 
	handleChanges( WorldScale );
}

AGMatrix AGMovable::getWorldScaleMatrix()
{
	return p->worldScaleMatrix; 
}

void AGMovable::setResultMatrix(AGMatrix world)
{
	p->world = world;
}

AGMatrix AGMovable::getResultMatrix()
{
	if( p->updateResMatrix )
		p->matrix = p->localScaleMatrix * p->localRotMatrix *  p->worldRotMatrix * p->worldScaleMatrix * p->localTranslMatrix * p->worldTranslMatrix; 

	return p->matrix; 
}

void AGMovable::handleChanges( Changes changes )
{

}

void AGMovable::setLookAt(const AGVec3& dir)
{
	float cosA = AGVec3::dot( dir, p->up ); 
	float angle = acos( cosA );

	AGVec3 axis = AGVec3::cross( dir, p->up );

	p->localRotMatrix.setIdentity(); 
	p->localRotMatrix.setRotate( axis, angle );

	/*float cosA = D3DXVec3Dot( &dir, &m_p->up ); 
	float angle = acos( cosA ); 

	AGVec3 axis;
	D3DXVec3Cross( &axis, &dir, &m_p->up ); 

	AGMatrixRotationAxis( &m_p->localRotMatrix, &axis, angle ); 

	m_p->up = dir; */
}







