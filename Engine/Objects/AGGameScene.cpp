#include "AGGameScene.h"
#include "Managers/AGLogger.h"
#include "AGGameObject.h"

AGGameScene::AGGameScene(string name)
{
	m_name = name; 
	m_selectedObject = nullptr; 
	m_curValidId = 0;
}

AGGameScene::~AGGameScene()
{
	for( auto iter : m_objectsById )
	{
		m_objectsById.erase( iter.first );
	}
	for( auto iter : m_objectsByName )
	{
		m_objectsByName.erase( iter.first );
	}

	list< AGGameObject* >::iterator iter = m_objects.begin(); 
	for( iter; iter != m_objects.end(); iter++ )
	{
		m_objects.erase( iter );
	}	
}

void AGGameScene::init()
{
	for( AGGameObject* object : m_objects )
	{
		object->onSceneInit(); 
	}
}

void AGGameScene::update()
{
	for( AGGameObject* object : m_objects )
	{
		object->onSceneUpdate(); 
	}
}

void AGGameScene::fixedUpdate()
{
	for( AGGameObject* object : m_objects )
	{
		object->onSceneFixedUpdate(); 
	}
}

AGGameObject* AGGameScene::createObject(string name)
{
	AGGameObject* object = new AGGameObject( name, m_curValidId, this );

	m_objects.push_back( object );
	m_objectsByName[ name ] = object; 
	m_objectsById[ m_curValidId ] = object;

	m_curValidId++; 

	return object;
}

AGGameObject* AGGameScene::copyFrom(AGGameObject* object)
{
	AGGameObject* newObject = new AGGameObject( object->getName(), m_curValidId, this );
	return newObject;
}

bool AGGameScene::containsObjectWithName(const string& name)
{
	return ( m_objectsByName.find( name ) != m_objectsByName.end() );
}

bool AGGameScene::containsObjectWithId(unsigned int id)
{
	return ( m_objectsById.find( id ) != m_objectsById.end() );
}

bool AGGameScene::containsObject(AGGameObject* reqObject)
{
	for( AGGameObject* object : m_objects )
	{
		if( object == reqObject )
			return true; 
	}
	return false; 
}

void AGGameScene::removeObject(AGGameObject* object)
{
	if( !object )
		return; 
	string name = object->getName(); 
	unsigned int id = object->getId();

	unordered_map< unsigned int, AGGameObject* >::iterator idIter = m_objectsById.find( id );
	unordered_map< string, AGGameObject* >::iterator nameIter = m_objectsByName.find( name );

	if( idIter != m_objectsById.end() )
	{
		m_objectsById.erase( idIter );	
	}
	if( nameIter != m_objectsByName.end() )
	{
		m_objectsByName.erase( nameIter );
	}

	list< AGGameObject* >::iterator iter = m_objects.begin(); 
	for( iter; iter != m_objects.end(); iter++ )
	{
		if( (*iter) == object )
		{
			m_objects.erase( iter );
			break; 
		}
	}	
}

void AGGameScene::removeObjectByName(const string& name)
{
	unordered_map< string, AGGameObject* >::iterator nameIter = m_objectsByName.find( name );
	if( nameIter == m_objectsByName.end() )
		return; 
	AGGameObject* object = nameIter->second; 
	unsigned int id = object->getId();

	unordered_map< unsigned int, AGGameObject* >::iterator idIter = m_objectsById.find( id );

	if( idIter != m_objectsById.end() )
	{
		m_objectsById.erase( idIter );	
	}
	if( nameIter != m_objectsByName.end() )
	{
		m_objectsByName.erase( nameIter );
	}

	list< AGGameObject* >::iterator iter = m_objects.begin(); 
	for( iter; iter != m_objects.end(); iter++ )
	{
		if( (*iter) == object )
		{
			m_objects.erase( iter );
			break; 
		}
	}	
}

void AGGameScene::removeObjectById(unsigned int id)
{
	unordered_map< unsigned int, AGGameObject* >::iterator idIter = m_objectsById.find( id );
	
	if( idIter == m_objectsById.end() )
		return; 
	AGGameObject* object = idIter->second; 
	string name = object->getName(); 
	unordered_map< string, AGGameObject* >::iterator nameIter = m_objectsByName.find( name );
	

	if( idIter != m_objectsById.end() )
	{
		m_objectsById.erase( idIter );	
	}
	if( nameIter != m_objectsByName.end() )
	{
		m_objectsByName.erase( nameIter );
	}

	list< AGGameObject* >::iterator iter = m_objects.begin(); 
	for( iter; iter != m_objects.end(); iter++ )
	{
		if( (*iter) == object )
		{
			m_objects.erase( iter );
			break; 
		}
	}	
}

const string& AGGameScene::getName() const
{
	return m_name; 
}

void AGGameScene::selectObject(AGGameObject* object)
{
	m_selectedObject = object; 
}

AGGameObject* AGGameScene::getSelectedObject() const
{
	return m_selectedObject; 
}
