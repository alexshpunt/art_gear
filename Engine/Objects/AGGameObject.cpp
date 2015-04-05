#include "AGGameObject.h"

#include "AGComponent.h"
#include "Managers/AGLogger.h"
#include "Graphics/Components/AGRenderer.h"
#include "Graphics/AGGraphics.h"

#include "Functors/AGGameObjectNotifyFunctor.h"

AGGameObject::AGGameObject(const string& name, unsigned int id, AGGameScene* scene)
{
	m_name = name; 
	m_id = id;
	m_scene = scene; 

	m_renderer = new AGRenderer( this );

	setPivot( 0.0f, 0.0f, 0.0f );
	
	setLocalPos( 0.0f, 0.0f, 0.0f );
	setLocalRot( 0.0f, 0.0f, 0.0f );
	setLocalScale( 1.0f, 1.0f, 1.0f );

	setWorldPos( 0.0f, 0.0f, 0.0f );
	setWorldRot( 0.0f, 0.0f, 0.0f );
	setWorldScale( 1.0f, 1.0f, 1.0f );

	m_isSelected = false; 
}

AGGameObject::AGGameObject(const AGGameObject& object)
{
	//Этого не должно было произойти...
	//А вообще, я не разрешаю просто копирование двух объектов, ибо каждый объект должен иметь свой уникальный айди
}

AGGameObject::AGGameObject(const string& name, unsigned int id, AGGameScene* scene, const AGGameObject* object)
{
	m_name = name;
	m_id = id;
	m_scene = scene; 

	for( AGComponent* component : object->m_components )
	{
		addComponent( component );
	}
	for( AGGameObject* child : object->m_children )
	{
		addChild( child ); 
	}
	
	setPivot( object->m_pivot );
	setLocalPos( object->m_localPos );
	setLocalRot( object->m_localRot );
	setLocalScale( object->m_localScale );
	m_isSelected = false; 
}

AGGameObject::~AGGameObject()
{
	for( AGGameObject* child : m_children )
	{
		delete child;
	}
	for( AGComponent* component : m_components )
	{
		delete component; 
	}
	delete m_renderer; 
}

void AGGameObject::onSceneInit()
{
	for( AGComponent* component : m_components )
	{
		component->onSceneInit(); 
	}
}

void AGGameObject::onSceneUpdate()
{
	for( AGComponent* component : m_components )
	{
		component->onSceneUpdate();
	}
}

void AGGameObject::onSceneFixedUpdate()
{
	for( AGComponent* component : m_components )
	{
		component->onSceneFixedUpdate(); 
	}
}

void AGGameObject::setSelected(bool flag)
{
	if( m_isSelected == flag )
		return; 
	m_isSelected = flag; 
	if( flag )
		AGGraphics::getInstance().addSelectedObject( this );
	else 
		AGGraphics::getInstance().removeSelectedObject( this );
}

bool AGGameObject::isSelected() const
{
	return m_isSelected; 
}

void AGGameObject::setPivot(const AGVec3& pivot)
{
	m_pivot = pivot; 
}

void AGGameObject::setPivot(float posX, float posY, float posZ)
{
	setPivot( AGVec3( posX, posY, posZ ) );
	sendNotifications(); 
}

const AGVec3& AGGameObject::getPivot() const
{
	return m_pivot; 
}

////////////////////////////////////////////////////////
//Position
////////////////////////////////////////////////////////

void AGGameObject::setLocalXPos(float posX)
{
	setLocalPos( posX, m_localPos.y, m_localPos.z );
}

float AGGameObject::getLocalXPos() const
{
	return m_localPos.x; 
}

void AGGameObject::setLocalYPos(float posY)
{
	setLocalPos( m_localPos.x, posY, m_localPos.z );
}

float AGGameObject::getLocalYPos() const
{
	return m_localPos.y; 
}

void AGGameObject::setLocalZPos(float posZ)
{
	setLocalPos( m_localPos.x, m_localPos.y, posZ );
}

float AGGameObject::getLocalZPos() const
{
	return m_localPos.z; 
}

void AGGameObject::setLocalPos(const AGVec3& pos)
{
	m_localPos = pos; 
	m_renderer->setLocalPos( m_localPos );
	for( AGGameObjectNotifyFunctor* func : m_notifyFunctors )
	{
		(*func)( Change::LocalPos ); 
	}
}

void AGGameObject::setLocalPos(float posX, float posY, float posZ)
{
	setLocalPos( AGVec3( posX, posY, posZ ) );
}

const AGVec3& AGGameObject::getLocalPos() const
{
	return m_localPos;
}

void AGGameObject::translateLocalX(float dX)
{
	setLocalPos( m_localPos.x + dX, m_localPos.y, m_localPos.z );
}

void AGGameObject::translateLocalY(float dY)
{
	setLocalPos( m_localPos.x, m_localPos.y + dY, m_localPos.z );
}

void AGGameObject::translateLocalZ(float dZ)
{
	setLocalPos( m_localPos.x, m_localPos.y, m_localPos.z + dZ );
}

void AGGameObject::translateLocal(const AGVec3& dir)
{
	setLocalPos( m_localPos + dir );
}

void AGGameObject::translateLocal(float dX, float dY, float dZ)
{
	translateLocal( AGVec3( dX, dY, dZ ) );
}

void AGGameObject::setWorldXPos(float posX)
{
	setWorldPos( posX, m_worldPos.y, m_worldPos.z );
}

float AGGameObject::getWorldXPos() const
{
	return m_worldPos.x; 
}

void AGGameObject::setWorldYPos(float posY)
{
	setWorldPos( m_worldPos.x, posY, m_worldPos.z );
}

float AGGameObject::getWorldYPos() const
{
	return m_worldPos.y; 
}

void AGGameObject::setWorldZPos( float posZ )
{
	setWorldPos( m_worldPos.x, m_worldPos.y, posZ );
}

float AGGameObject::getWorldZPos() const
{
	return m_worldPos.z; 
}


void AGGameObject::setWorldPos(const AGVec3& pos)
{
	m_worldPos = pos; 
	m_renderer->setWorldPos( m_worldPos );
	for( AGGameObjectNotifyFunctor* func : m_notifyFunctors )
	{
		(*func)( Change::WorldPos ); 
	}
}

void AGGameObject::setWorldPos(float posX, float posY, float posZ)
{
	setWorldPos( AGVec3( posX, posY, posZ ) );
}

const AGVec3& AGGameObject::getWorldPos() const
{
	return m_worldPos; 
}

void AGGameObject::translateWorldX(float dX)
{
	setWorldPos( m_worldPos.x + dX, m_worldPos.y, m_worldPos.z );
}

void AGGameObject::translateWorldY(float dY)
{
	setWorldPos( m_worldPos.x, m_worldPos.y + dY, m_worldPos.z );
}

void AGGameObject::translateWorldZ(float dZ)
{
	setWorldPos( m_worldPos.x, m_worldPos.y, m_worldPos.z + dZ );
}

void AGGameObject::translateWorld(const AGVec3& dir)
{
	setWorldPos( m_worldPos + dir );
}

void AGGameObject::translateWorld(float dX, float dY, float dZ)
{
	setWorldPos( m_worldPos + AGVec3( dX, dY, dZ ) );
}

////////////////////////////////////////////////////////
//Rotation
////////////////////////////////////////////////////////

void AGGameObject::setLocalXRot(float angleX)
{
	setLocalRot( angleX, m_localRot.y, m_localRot.z );
}

float AGGameObject::getLocalXRot() const
{
	return m_localRot.x; 
}

void AGGameObject::setLocalYRot(float angleY)
{
	setLocalRot( m_localRot.x, angleY, m_localRot.z );
}

float AGGameObject::getLocalYRot() const
{
	return m_localRot.y; 
}

void AGGameObject::setLocalZRot(float angleZ)
{
	setLocalRot( m_localRot.x, m_localRot.y, angleZ );
}

float AGGameObject::getLocalZRot() const
{
	return m_localRot.z; 
}


void AGGameObject::setLocalRot(const AGVec3& angles)
{
	m_localRot = angles; 
	m_renderer->setLocalAngle( AGEulerAngles( AGRadians( m_localRot.x ), AGRadians(  m_localRot.y ), AGRadians( m_localRot.z ) ) );
	for( AGGameObjectNotifyFunctor* func : m_notifyFunctors )
	{
		(*func)( Change::LocalRot ); 
	}
}

void AGGameObject::setLocalRot(float angleX, float angleY, float angleZ)
{
	setLocalRot( AGVec3( angleX, angleY, angleZ ) );
}

const AGVec3& AGGameObject::getLocalRot() const
{
	return m_localRot; 
}

void AGGameObject::rotateLocalAxis(const AGVec3& axis, float angle)
{

}

void AGGameObject::rotateLocalX(float angleX)
{
	m_localRot.x += angleX; 
	m_renderer->rotateLocalX( AGRadians( angleX ) );
}

void AGGameObject::rotateLocalY(float angleY)
{
	m_localRot.y += angleY; 
	m_renderer->rotateLocalY( AGRadians( angleY ) );
}

void AGGameObject::rotateLocalZ(float angleZ)
{
	m_localRot.z += angleZ; 
	m_renderer->rotateLocalZ( AGRadians( angleZ ) );
}

void AGGameObject::rotateLocal(const AGVec3& angles)
{
	setLocalRot( m_localRot + angles );
}

void AGGameObject::rotateLocal(float angleX, float angleY, float angleZ)
{
	setLocalRot( m_localRot + AGVec3( angleX, angleY, angleZ ) );
}

void AGGameObject::setWorldXRot(float angleX)
{
	setWorldRot( angleX, m_worldRot.y, m_worldRot.z );
}

float AGGameObject::getWorldXRot() const
{
	return m_worldRot.x; 
}

void AGGameObject::setWorldYRot(float angleY)
{
	setWorldRot( m_worldRot.x, angleY, m_worldRot.z );
}

float AGGameObject::getWorldYRot() const
{
	return m_worldRot.y; 
}

void AGGameObject::setWorldZRot(float angleZ)
{
	setWorldRot( m_worldRot.z, m_worldRot.y, angleZ );
}

float AGGameObject::getWorldZRot() const
{
	return m_worldRot.z; 
}

void AGGameObject::setWorldRot(const AGVec3& angles)
{
	m_worldRot = angles; 
	m_renderer->setWorldAngle( AGRadians( angles.x ), AGRadians( angles.y ), AGRadians( angles.z ) );
	for( AGGameObjectNotifyFunctor* func : m_notifyFunctors )
	{
		(*func)( Change::WorldRot ); 
	}
}

void AGGameObject::setWorldRot(float angleX, float angleY, float angleZ)
{
	setWorldRot( AGVec3( angleX, angleY, angleZ ) );
}

const AGVec3& AGGameObject::getWorldRot() const
{
	return m_worldRot; 
}

void AGGameObject::rotateWorldAxis(const AGVec3& axis, float angle)
{

}

void AGGameObject::rotateAroundWorldX(float angleX)
{
	m_worldRot.x += angleX; 
	m_renderer->rotateAroundWorldX( AGRadians( angleX ) );
}

void AGGameObject::rotateAroundWorldY(float angleY)
{
	m_worldRot.y += angleY;
	m_renderer->rotateAroundWorldY( AGRadians( angleY ) );
}

void AGGameObject::rotateAroundWorldZ(float angleZ)
{
	m_worldRot.z += angleZ; 
	m_renderer->rotateAroundWorldZ( AGRadians( angleZ ) );
}

void AGGameObject::rotateWorldX(float angleX)
{
	m_worldRot.x += angleX; 
	m_renderer->rotateWorldX( AGRadians( angleX ) );
}

void AGGameObject::rotateWorldY(float angleY)
{
	m_worldRot.y += angleY; 
	m_renderer->rotateWorldY( AGRadians( angleY ) );
}

void AGGameObject::rotateWorldZ(float angleZ)
{
	m_worldRot.z += angleZ; 
	m_renderer->rotateWorldZ( AGRadians( angleZ ) );
}

void AGGameObject::rotateWorld(const AGVec3& angles)
{
	setWorldRot( m_worldRot + angles );
}

void AGGameObject::rotateWorld(float angleX, float angleY, float angleZ)
{
	setWorldRot( m_worldRot + AGVec3( angleX, angleY, angleZ ) );
}

////////////////////////////////////////////////////////
//Scale
////////////////////////////////////////////////////////

void AGGameObject::setLocalXScale(float scaleX)
{
	setLocalScale( scaleX, m_localScale.y, m_localScale.z );
}

float AGGameObject::getLocalXScale() const
{
	return m_localScale.x; 
}

void AGGameObject::setLocalYScale(float scaleY)
{
	setLocalScale( m_localScale.x, scaleY, m_localScale.z );
}

float AGGameObject::getLocalYScale() const
{
	return m_localScale.y; 
}

void AGGameObject::setLocalZScale(float scaleZ)
{
	setLocalScale( m_localScale.x, m_localScale.y, scaleZ );
}

float AGGameObject::getLocalZScale() const
{
	return m_localScale.z; 
}

void AGGameObject::setLocalScale(const AGVec3& scale)
{
	m_localScale = scale; 
	m_renderer->setLocalScale( m_localScale );
	for( AGGameObjectNotifyFunctor* func : m_notifyFunctors )
	{
		(*func)( Change::LocalScale); 
	}
}

void AGGameObject::setLocalScale(float scaleX, float scaleY, float scaleZ)
{
	setLocalScale( AGVec3( scaleX, scaleY, scaleZ ) );
}

const AGVec3& AGGameObject::getLocalScale() const
{
	return m_localScale; 
}

void AGGameObject::scaleLocal(const AGVec3& scale)
{
	setLocalScale( m_localScale + scale );
}

void AGGameObject::scaleLocal(float dsX, float dsY, float dsZ)
{
	scaleLocal( AGVec3( dsX, dsY, dsZ ) );
}

void AGGameObject::setWorldXScale(float scaleX)
{
	setWorldScale( scaleX, m_worldScale.y, m_worldScale.z );
}

float AGGameObject::getWorldXScale() const
{
	return m_worldScale.x; 
}

void AGGameObject::setWorldYScale(float scaleY)
{
	setWorldScale( m_worldScale.x, scaleY, m_worldScale.z );
}

float AGGameObject::getWorldYScale() const
{
	return m_worldScale.y; 
}

void AGGameObject::setWorldZScale(float scaleZ)
{
	setWorldScale( m_worldScale.x, m_worldScale.y, scaleZ );
}

float AGGameObject::getWorldZScale() const
{
	return m_worldScale.z; 
}

void AGGameObject::setWorldScale(const AGVec3& scale)
{
	m_worldScale = scale; 
	m_renderer->setWorldScale( m_worldScale );
	for( AGGameObjectNotifyFunctor* func : m_notifyFunctors )
	{
		(*func)( Change::WorldScale ); 
	}
}

void AGGameObject::setWorldScale(float scaleX, float scaleY, float scaleZ)
{
	setWorldScale( AGVec3( scaleX, scaleY, scaleZ ) );
}

const AGVec3& AGGameObject::getWorldScale() const
{
	return m_worldScale; 
}

void AGGameObject::scaleWorld(const AGVec3& scale)
{
	setWorldScale( m_worldScale + scale );
}

void AGGameObject::scaleWorld(float dsX, float dsY, float dsZ)
{
	setWorldScale( m_worldScale + AGVec3( dsX, dsY, dsZ ) );
}

////////////////////////////////////////////////////////
//Properties
////////////////////////////////////////////////////////

void AGGameObject::setName(const string& name)
{
	m_name = name; 
	for( AGGameObjectNotifyFunctor* func : m_notifyFunctors )
	{
		(*func)( Change::Name ); 
	}
}

const string& AGGameObject::getName() const
{
	return m_name; 
}

unsigned int AGGameObject::getId() const
{
	return m_id;
}

AGGameScene* AGGameObject::getScene() const
{
	return m_scene; 
}

void AGGameObject::addComponent(AGComponent* component)
{
	m_components.push_back( component );
	m_componentsByName[ component->getName() ] = component; 
}

void AGGameObject::addComponentByName(const string& name)
{
	//TODO: Добавить создание объектов через менеджер компонентов 
}

bool AGGameObject::containsComponent(const string& name)
{
	return ( m_componentsByName.find( name ) != m_componentsByName.end() );
}

void AGGameObject::removeComponent(const string& name)
{
	unordered_map< string, AGComponent* >::iterator iter = m_componentsByName.find( name );
	if( iter == m_componentsByName.end() )
	{
		return; 
	}
	list< AGComponent* >::iterator compIter = m_components.begin(); 

	for( compIter; compIter != m_components.end(); compIter++ )
	{
		AGComponent* component = *compIter; 
		if( component == (*iter).second )
		{
			m_components.erase( compIter );
			m_componentsByName.erase( name );
			delete component;
			return; 
		}
	}
	
}

void AGGameObject::removeAllComponents()
{
	for( AGComponent* component : m_components )
	{
		delete component; 
	}
	m_components.clear(); 
	m_componentsByName.clear(); 
}

AGComponent* AGGameObject::getComponent(const string& name)
{
	unordered_map< string, AGComponent* >::iterator iter = m_componentsByName.find( name );
	if( iter != m_componentsByName.end() )
	{
		return (*iter).second; 
	}
	return nullptr;
}

const list< AGComponent* >& AGGameObject::getComponents() const
{
	return m_components;
}

void AGGameObject::addChild(AGGameObject* object)
{
	m_children.push_back( object );
	m_childrenByName[ object->getName() ] = object; 
}

void AGGameObject::removeChild(AGGameObject* object)
{
	unordered_map< string, AGGameObject* >::iterator iter = m_childrenByName.begin();
	if( iter == m_childrenByName.end() )
	{
		return; 
	}
	list< AGGameObject* >::iterator childIter = m_children.begin(); 
	for( childIter; childIter != m_children.end(); childIter++ )
	{
		AGGameObject* child = *childIter;
		if( child == object )
		{
			m_children.erase( childIter );
			m_childrenByName.erase( iter );
			delete child;
			return;
		}
	}
}

AGGameObject* AGGameObject::getChild(const string& name)
{
	unordered_map< string, AGGameObject* >::iterator iter = m_childrenByName.begin();
	if( iter != m_childrenByName.end() )
	{
		return (*iter).second; 
	}
	return nullptr;
}

const list< AGGameObject* >& AGGameObject::getChildren() const
{
	return m_children;
}

AGRenderer* AGGameObject::getRenderer() const
{
	return m_renderer; 
}

void AGGameObject::registerNotifyFunctor(AGGameObjectNotifyFunctor* func)
{
	m_notifyFunctors.push_back( func );
}

void AGGameObject::unregisterNotifyFunctor(AGGameObjectNotifyFunctor* needFunc )
{		
	list< AGGameObjectNotifyFunctor* >::iterator iter = m_notifyFunctors.begin(); 
	for( iter; iter != m_notifyFunctors.end(); iter++ )
	{
		if( (*iter) == needFunc )
		{
			m_notifyFunctors.erase( iter );
			return; 
		}
	}
}
