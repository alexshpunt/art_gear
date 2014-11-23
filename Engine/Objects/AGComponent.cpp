#include "AGComponent.h"

#include "AGObject.h"

AGComponent::AGComponent(AGObject* object) : m_object( object )
{
	m_name = ""; 
}

AGComponent::~AGComponent()
{
	m_object->removeComponent( m_name );
}

AGObject* AGComponent::getObject() const
{
	return m_object; 
}

const string& AGComponent::getName() const
{
	return m_name;
}

