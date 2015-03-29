#include "AGRenderer.h"

#include "Engine/Graphics/AGGraphics.h"
#include "Engine/Graphics/Objects/AGMesh.h"
#include "Engine/Graphics/Interfaces/AGSurface.h"
#include "Managers/AGEStateManager.h"

#include "Engine/Objects/AGGameObject.h"

AGRenderer::AGRenderer(AGGameObject* object) : AGComponent( object )
{
	m_boundingBox = new AGBoundingBox( AGVec3( 1.0f, 1.0f, 1.0f ), AGVec3( 0.0f, 0.0f, 0.0f ) );
	m_isSelected = false; 
	AGGraphics::getInstance().addRenderer( this ); 
}

AGRenderer::~AGRenderer()
{
	delete m_boundingBox; 
	AGGraphics::getInstance().removeRenderer( this ); 
}

void AGRenderer::notify(AGGameObject::Change change)
{

}

void AGRenderer::onSceneInit()
{

}

void AGRenderer::onSceneUpdate()
{

}

void AGRenderer::onSceneFixedUpdate()
{

}

void AGRenderer::setMesh(AGMesh* mesh)
{
	m_mesh = mesh; 
}

AGMesh* AGRenderer::getMesh() const
{
	return (AGMesh*)m_mesh.getData(); 
}

float AGRenderer::intersect( const AGVec3& rayOrigin, const AGVec3& rayDir)
{
	AGMesh* mesh = (AGMesh*)m_mesh.getData();

	if( mesh )
		return mesh->intersect( rayOrigin, rayDir );
	else 
		return m_boundingBox->intersect( rayOrigin, rayDir );
}

void AGRenderer::setSelected(bool value)
{
	m_isSelected = value;
	m_object->setSelected( value );
}

bool AGRenderer::isSelected() const
{
	return m_isSelected;
}

void AGRenderer::draw( AGSurface* surface )
{
	AGMesh* mesh = (AGMesh*)m_mesh.getData();

	if( mesh )
	{
		mesh->draw( surface );
	}
	else 
	{
		m_boundingBox->draw( surface ); 
	}

	if( m_isSelected )
	{
		if( mesh )
		{
			mesh->getBoundingBox()->draw( surface );	
		}

	}

}

void AGRenderer::handleChanges(Changes changes)
{
	switch( changes )
	{
		case World:
			m_boundingBox->setWorldMatrix( getWorldMatrix() );
		break;
		case WorldTrans:
			m_boundingBox->setWorldTranslMatrix( getWorldTranslMatrix() );
		break;
		case WorldRot:
			m_boundingBox->setWorldRotMatrix( getWorldRotMatrix() );
		break;
		case Local:
			m_boundingBox->setLocalMatrix( getLocalMatrix() );
		break;
		case LocalTrans:
			m_boundingBox->setLocalTranslMatrix( getLocalTranslMatrix() );
		break;
		case LocalRot:
			m_boundingBox->setLocalRotMatrix( getLocalRotMatrix() );
		break;
	}

	AGMesh* mesh = (AGMesh*)m_mesh.getData();

	if( !mesh )
		return; 
	switch( changes )
	{
		case World:
			mesh->setWorldMatrix( getWorldMatrix() );
		break;
		case WorldTrans:
			mesh->setWorldTranslMatrix( getWorldTranslMatrix() );
		break;
		case WorldRot:
			mesh->setWorldRotMatrix( getWorldRotMatrix() );
		break;
		case WorldScale:
			mesh->setWorldScaleMatrix( getWorldScaleMatrix() );
		break;
		case Local:
			mesh->setLocalMatrix( getLocalMatrix() );
		break;
		case LocalTrans:
			mesh->setLocalTranslMatrix( getLocalTranslMatrix() );
		break;
		case LocalRot:
			mesh->setLocalRotMatrix( getLocalRotMatrix() );
		break;
		case LocalScale:
			mesh->setLocalScaleMatrix( getLocalScaleMatrix() );
		break;
	}
}

