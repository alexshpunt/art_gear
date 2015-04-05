#include "AGComponent.h"

#include "AGGameObject.h"

AGComponent::AGComponent(AGGameObject* object) : m_object( object )
{
	m_name = ""; 
}

AGComponent::~AGComponent()
{
	m_object->removeComponent( m_name );
}

AGGameObject* AGComponent::getObject() const
{
	return m_object; 
}

const string& AGComponent::getName() const
{
	return m_name;
}

void AGComponent::onSceneInit()
{

}

void AGComponent::onSceneUpdate()
{

}

void AGComponent::onSceneFixedUpdate()
{

}

