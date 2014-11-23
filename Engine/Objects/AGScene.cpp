#include "AGScene.h"

#include "AGObject.h"

AGScene::AGScene(string name)
{
	m_name = name; 

	m_curValidId = 0;
}

AGScene::~AGScene()
{
	for( auto iter : m_objectsById )
	{
		m_objectsById.erase( iter.first );
	}
	for( auto iter : m_objectsByName )
	{
		m_objectsByName.erase( iter.first );
	}

	list< AGObject* >::iterator iter = m_objects.begin(); 
	for( iter; iter != m_objects.end(); iter++ )
	{
		m_objects.erase( iter );
	}	
}

void AGScene::init()
{
	for( AGObject* object : m_objects )
	{
		object->onSceneInit(); 
	}
}

void AGScene::update()
{
	for( AGObject* object : m_objects )
	{
		object->onSceneUpdate(); 
	}
}

void AGScene::fixedUpdate()
{
	for( AGObject* object : m_objects )
	{
		object->onSceneFixedUpdate(); 
	}
}

AGObject* AGScene::createObject(string name)
{
	AGObject* object = new AGObject( name, m_curValidId, this );

	m_objects.push_back( object );
	m_objectsByName[ name ] = object; 
	m_objectsById[ m_curValidId ] = object;

	m_curValidId++; 

	return object;
}

AGObject* AGScene::copyFrom(AGObject* object)
{
	AGObject* newObject = new AGObject( object->getName(), m_curValidId, this );
	return newObject;
}

bool AGScene::containsObjectWithName(const string& name)
{
	return ( m_objectsByName.find( name ) != m_objectsByName.end() );
}

bool AGScene::containsObjectWithId(unsigned int id)
{
	return ( m_objectsById.find( id ) != m_objectsById.end() );
}

bool AGScene::containsObject(AGObject* reqObject)
{
	for( AGObject* object : m_objects )
	{
		if( object == reqObject )
			return true; 
	}
	return false; 
}

void AGScene::removeObject(AGObject* object)
{
	if( !object )
		return; 
	string name = object->getName(); 
	unsigned int id = object->getId();

	unordered_map< unsigned int, AGObject* >::iterator idIter = m_objectsById.find( id );
	unordered_map< string, AGObject* >::iterator nameIter = m_objectsByName.find( name );

	if( idIter != m_objectsById.end() )
	{
		m_objectsById.erase( idIter );	
	}
	if( nameIter != m_objectsByName.end() )
	{
		m_objectsByName.erase( nameIter );
	}

	list< AGObject* >::iterator iter = m_objects.begin(); 
	for( iter; iter != m_objects.end(); iter++ )
	{
		if( (*iter) == object )
		{
			m_objects.erase( iter );
			break; 
		}
	}	
}

void AGScene::removeObjectByName(const string& name)
{
	unordered_map< string, AGObject* >::iterator nameIter = m_objectsByName.find( name );
	if( nameIter == m_objectsByName.end() )
		return; 
	AGObject* object = nameIter->second; 
	unsigned int id = object->getId();

	unordered_map< unsigned int, AGObject* >::iterator idIter = m_objectsById.find( id );

	if( idIter != m_objectsById.end() )
	{
		m_objectsById.erase( idIter );	
	}
	if( nameIter != m_objectsByName.end() )
	{
		m_objectsByName.erase( nameIter );
	}

	list< AGObject* >::iterator iter = m_objects.begin(); 
	for( iter; iter != m_objects.end(); iter++ )
	{
		if( (*iter) == object )
		{
			m_objects.erase( iter );
			break; 
		}
	}	
}

void AGScene::removeObjectById(unsigned int id)
{
	unordered_map< unsigned int, AGObject* >::iterator idIter = m_objectsById.find( id );
	
	if( idIter == m_objectsById.end() )
		return; 
	AGObject* object = idIter->second; 
	string name = object->getName(); 
	unordered_map< string, AGObject* >::iterator nameIter = m_objectsByName.find( name );
	

	if( idIter != m_objectsById.end() )
	{
		m_objectsById.erase( idIter );	
	}
	if( nameIter != m_objectsByName.end() )
	{
		m_objectsByName.erase( nameIter );
	}

	list< AGObject* >::iterator iter = m_objects.begin(); 
	for( iter; iter != m_objects.end(); iter++ )
	{
		if( (*iter) == object )
		{
			m_objects.erase( iter );
			break; 
		}
	}	
}

const string& AGScene::getName() const
{
	return m_name; 
}
