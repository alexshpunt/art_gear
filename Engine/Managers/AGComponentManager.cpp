#include "AGComponentManager.h"

#include "Objects/AGComponent.h"
#include "Objects/AGGameObject.h"

void AGComponentManager::registerFunction(const string& componentName, CreationFunction func)
{
	m_creationFunctions[ componentName ] = func; 
}

AGComponent* AGComponentManager::createComponent(const string& componentName, AGGameObject* object)
{
	unordered_map< string, CreationFunction >::iterator iter = m_creationFunctions.find( componentName );
	AGComponent* component = nullptr;

	if( iter != m_creationFunctions.end() )
	{
		CreationFunction func = (*iter).second;
		component = (*func)( object );
	}
	return component; 
}

