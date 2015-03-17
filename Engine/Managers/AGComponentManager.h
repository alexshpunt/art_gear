#ifndef AG_COMPONENTMANAGER_H
#define AG_COMPONENTMANAGER_H

#include <unordered_map>
#include <string>
#include "Patterns/Singleton.h"

class AGComponent; 
class AGGameObject; 

typedef AGComponent* (*CreationFunction )( AGGameObject* object );

using namespace std;

#define REGISTER_CREATE_FUNCTION( className, func ) AGComponentManager::getInstance().registerFunction( "##className##", &func );

class AGComponentManager 
{
	DECLARE_SINGLETON( AGComponentManager )
	public:
		void registerFunction( const string& componentName, CreationFunction func );
		AGComponent* createComponent( const string& componentName, AGGameObject* object );

	private:
		unordered_map< string, CreationFunction > m_creationFunctions; 
};

#endif 