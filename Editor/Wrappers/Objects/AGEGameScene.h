#ifndef AGE_GAMESCENE_H
#define AGE_GAMESCENE_H

#include <string>
#include <list> 
#include <map>

#include "Engine/Objects/AGGameScene.h"

class AGEGameObject; 

/*
	Этот класс используется как обёртка вокруг оригинального AGGameScene
	Реализовывает специфичную для редактора функциональность
*/
class AGEGameScene 
{
	public:
		AGEGameScene( const std::string& name );
		~AGEGameScene();

		AGEGameObject* createObject( const std::string& name );
		AGEGameObject* copyFrom( AGEGameObject* object );
		
		void removeObject( AGEGameObject* object );
		void removeObject( const std::string& name );
		
		void selectObject( AGEGameObject* object );
		AGEGameObject* getSelectedObject() const;
		
		void setName( const std::string& name );
		const std::string& getName() const;  
	private:
		std::string m_name; 

		std::map< std::string, AGEGameObject* > m_objectsByName; 
		std::list< AGEGameObject* > m_objects; 

		AGEGameObject* m_selectedObject; 
		AGGameScene* m_scene; 
};

#endif 