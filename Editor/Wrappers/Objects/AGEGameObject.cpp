#include "AGEGameObject.h"

AGEGameObject::AGEGameObject( AGGameObject* object ) 
: m_gameObject( object ),
  m_item( new AGESceneViewItem( this ) ),
  m_name( object->getName() )
{}

AGEGameObject::~AGEGameObject(){}

const std::string& AGEGameObject::getName() const
{
	return m_name;
}

void AGEGameObject::setSelected(bool value)
{
	m_isSelected = value;
}

bool AGEGameObject::isSelected() const
{
	return m_isSelected; 
}

AGESceneViewItem* AGEGameObject::getItem() const
{
	return m_item; 
}

