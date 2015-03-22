#ifndef AG_COMPONENT_H
#define AG_COMPONENT_H

#include <string>

#include "Engine/Objects/AGGameObject.h"

using namespace std;

class AGGameScene; 

class AGComponent 
{
	public:
		AGComponent( AGGameObject* object );
		virtual ~AGComponent(); 
		
		virtual void notify( AGGameObject::Change ) = 0; 

		virtual void onSceneInit(); 
		virtual void onSceneUpdate();
		virtual void onSceneFixedUpdate();

		AGGameObject* getObject() const; 
		const string& getName() const; 

	protected:
		AGGameObject* m_object; 
		string m_name; 
};

#endif 