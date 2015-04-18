#include "AGEGameScene.h"

#include "AGEGameObject.h"

AGEGameScene::AGEGameScene(const std::string& name) 
: m_scene( new AGGameScene( name ) ),
  m_name( name )
{}

AGEGameScene::~AGEGameScene(){}

AGEGameObject* AGEGameScene::createObject(const std::string& name)
{
	AGEGameObject* gameObject = new AGEGameObject( m_scene->createObject( name ) );
	m_objects.push_back( gameObject );
	m_objectsByName[ name ] = gameObject; 
	return gameObject; 
}

AGEGameObject* AGEGameScene::copyFrom(AGEGameObject* object)
{
	return nullptr;
}

void AGEGameScene::removeObject(AGEGameObject* object)
{
	m_objects.remove( object ); 
	m_objectsByName.erase( object->getName() );
}

void AGEGameScene::removeObject(const std::string& name)
{
	auto iter = m_objectsByName.find( name );
	m_objects.remove( (*iter).second );
	m_objectsByName.erase( name );
}

void AGEGameScene::selectObject(AGEGameObject* object)
{
	object->setSelected( true );
	m_selectedObject = object; 
}

AGEGameObject* AGEGameScene::getSelectedObject() const
{
	return m_selectedObject; 
}

void AGEGameScene::setName(const std::string& name)
{
	m_name = name;
}

const std::string& AGEGameScene::getName() const
{
	return m_name; 
}

