#include "AGObject.h"

#include "AGComponent.h"
#include "Managers/AGLogger.h"
#include "Graphics/Components/AGRenderer.h"
#include "Graphics/AGGraphics.h"

AGObject::AGObject(const string& name, unsigned int id, AGScene* scene)
{
	m_name = name; 
	m_id = id;
	m_scene = scene; 

	setPivot( 0.0f, 0.0f, 0.0f );
	setPos( 0.0f, 0.0f, 0.0f );
	setRotation( 0.0f, 0.0f, 0.0f );
	setScale( 1.0f, 1.0f, 1.0f );
	m_isSelected = false; 

	m_renderer = new AGRenderer( this );
}

AGObject::AGObject(const AGObject& object)
{
	//Этого не должно было произойти...
	//А вообще, я не разрешаю просто копирование двух объектов, ибо каждый объект должен иметь свой уникальный айди
}

AGObject::AGObject(const string& name, unsigned int id, AGScene* scene, const AGObject* object)
{
	m_name = name;
	m_id = id;
	m_scene = scene; 

	for( AGComponent* component : object->m_components )
	{
		addComponent( component );
	}
	for( AGObject* child : object->m_children )
	{
		addChild( child ); 
	}
	
	setPivot( object->m_pivot );
	setPos( object->m_pos );
	setRotation( object->m_rotation );
	setScale( object->m_scale );
	m_isSelected = false; 
}

AGObject::~AGObject()
{
	for( AGObject* child : m_children )
	{
		delete child;
	}
	for( AGComponent* component : m_components )
	{
		delete component; 
	}
	delete m_renderer; 
}

void AGObject::onSceneInit()
{
	for( AGComponent* component : m_components )
	{
		component->onSceneInit(); 
	}
}

void AGObject::onSceneUpdate()
{
	for( AGComponent* component : m_components )
	{
		component->onSceneUpdate();
	}
}

void AGObject::onSceneFixedUpdate()
{
	for( AGComponent* component : m_components )
	{
		component->onSceneFixedUpdate(); 
	}
}

void AGObject::setSelected(bool flag)
{
	if( m_isSelected == flag )
		return; 
	m_isSelected = flag; 
	if( flag )
		AGGraphics::getInstance().addSelectedObject( this );
	else 
		AGGraphics::getInstance().removeSelectedObject( this );
}

bool AGObject::isSelected() const
{
	return m_isSelected; 
}

void AGObject::setPivot(const AGVec3& pivot)
{
	m_pivot = pivot; 
}

void AGObject::setPivot(float posX, float posY, float posZ)
{
	setPivot( AGVec3( posX, posY, posZ ) );
}

const AGVec3& AGObject::getPivot() const
{
	return m_pivot; 
}

void AGObject::setPos(const AGVec3& pos)
{
	m_pos = pos; 
	AGDebug() << pos.x << " " << pos.y << " " << pos.z;
}

void AGObject::setPos(float posX, float posY, float posZ)
{
	setPos( AGVec3( posX, posY, posZ ) );
}

const AGVec3& AGObject::getPos() const
{
	return m_pos;
}

void AGObject::setRotation(const AGVec3& angles)
{
	m_rotation = angles; 
}

void AGObject::setRotation(float angleX, float angleY, float angleZ)
{
	setRotation( AGVec3( angleX, angleY, angleZ ) );
}

const AGVec3& AGObject::getRotation() const
{
	return m_rotation; 
}

void AGObject::setScale(const AGVec3& scale)
{
	m_scale = scale; 
}

void AGObject::setScale(float scaleX, float scaleY, float scaleZ)
{
	setScale( AGVec3( scaleX, scaleY, scaleZ ) );
}

const AGVec3& AGObject::getScale() const
{
	return m_scale; 
}

void AGObject::translate(const AGVec3& dir)
{
	setPos( m_pos + dir );
}

void AGObject::translate(float dX, float dY, float dZ)
{
	translate( AGVec3( dX, dY, dZ ) );
}

void AGObject::rotateX(float angleX)
{
	rotate( angleX, 0.0f, 0.0f );
}

void AGObject::rotateY(float angleY)
{
	rotate( 0.0f, angleY, 0.0f );
}

void AGObject::rotateZ(float angleZ)
{
	rotate( 0.0f, 0.0f, angleZ );
}

void AGObject::rotate(float angleX, float angleY, float angleZ)
{
	setRotation( m_rotation + AGVec3( angleX, angleY, angleZ ) );
}

void AGObject::scale(const AGVec3& scale)
{
	setScale( m_scale + scale );
}

void AGObject::scale(float dsX, float dsY, float dsZ)
{
	scale( AGVec3( dsX, dsY, dsZ ) );
}

void AGObject::setName(const string& name)
{
	m_name = name; 
}

const string& AGObject::getName() const
{
	return m_name; 
}

unsigned int AGObject::getId() const
{
	return m_id;
}

AGScene* AGObject::getScene() const
{
	return m_scene; 
}

void AGObject::addComponent(AGComponent* component)
{
	m_components.push_back( component );
	m_componentsByName[ component->getName() ] = component; 
}

void AGObject::addComponentByName(const string& name)
{
	//TODO: Добавить создание объектов через менеджер компонентов 
}

bool AGObject::containsComponent(const string& name)
{
	return ( m_componentsByName.find( name ) != m_componentsByName.end() );
}

void AGObject::removeComponent(const string& name)
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

void AGObject::removeAllComponents()
{
	for( AGComponent* component : m_components )
	{
		delete component; 
	}
	m_components.clear(); 
	m_componentsByName.clear(); 
}

AGComponent* AGObject::getComponent(const string& name)
{
	unordered_map< string, AGComponent* >::iterator iter = m_componentsByName.find( name );
	if( iter != m_componentsByName.end() )
	{
		return (*iter).second; 
	}
	return nullptr;
}

const list< AGComponent* >& AGObject::getComponents() const
{
	return m_components;
}

void AGObject::addChild(AGObject* object)
{
	m_children.push_back( object );
	m_childrenByName[ object->getName() ] = object; 
}

void AGObject::removeChild(AGObject* object)
{
	unordered_map< string, AGObject* >::iterator iter = m_childrenByName.begin();
	if( iter == m_childrenByName.end() )
	{
		return; 
	}
	list< AGObject* >::iterator childIter = m_children.begin(); 
	for( childIter; childIter != m_children.end(); childIter++ )
	{
		AGObject* child = *childIter;
		if( child == object )
		{
			m_children.erase( childIter );
			m_childrenByName.erase( iter );
			delete child;
			return;
		}
	}
}

AGObject* AGObject::getChild(const string& name)
{
	unordered_map< string, AGObject* >::iterator iter = m_childrenByName.begin();
	if( iter != m_childrenByName.end() )
	{
		return (*iter).second; 
	}
	return nullptr;
}

const list< AGObject* >& AGObject::getChildren() const
{
	return m_children;
}

AGRenderer* AGObject::getRenderer() const
{
	return m_renderer; 
}



