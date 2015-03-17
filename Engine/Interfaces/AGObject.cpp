#include "AGObject.h"

AGObject::AGObject()
{

}

AGObject::~AGObject()
{

}

void AGObject::registerListener(AGObject* listener)
{
	m_listeners.push_back( listener );
}

void AGObject::unregisterListener(AGObject* listener)
{
	m_listeners.remove( listener );
}

void AGObject::notify()
{
	//none
}

void AGObject::sendNotifications()
{
	for( AGObject* listener : m_listeners )
	{
		listener->notify(); 
	}
}

void AGObject::setName(std::string name)
{
	m_name = name; 
}

std::string AGObject::getName()
{
	return m_name; 
}
