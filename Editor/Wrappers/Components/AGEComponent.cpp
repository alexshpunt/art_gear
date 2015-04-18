#include "AGEComponent.h"

#include "Editor/Wrappers/Components/AGEComponent.h"

AGEComponent::AGEComponent( AGEGameObject* object ) 
: m_gameObject( object )
{}

AGEComponent::~AGEComponent()
{}

AGEGameObject* AGEComponent::getGameObject() const
{
	return m_gameObject; 
}
