#ifndef AG_GAMESCENE_H
#define AG_GAMESCENE_H

#include <list>
#include <unordered_map>
#include <string>

#include "Math/AGMath.h"

using namespace std;

class AGGameObject; 

class AGGameScene 
{
	public:
		AGGameScene( string name );
		~AGGameScene();

		void init(); 
		void update(); 
		void fixedUpdate(); 

		AGGameObject* createObject( string name );
		AGGameObject* copyFrom( AGGameObject* object );
		bool containsObjectWithName( const string& name );
		bool containsObjectWithId( unsigned int id );
		bool containsObject( AGGameObject* object );

		//Удаляет объект со сцены и освобождает память, все указатели на этот объект станут невалидными! 
		void removeObject( AGGameObject* object );
		void removeObjectByName( const string& name );
		void removeObjectById( unsigned int id ); 

		void selectObject( AGGameObject* object );
		AGGameObject* getSelectedObject() const; 

		const string& getName() const; 

	private: 
		unsigned int m_curValidId; 

		unordered_map< string, AGGameObject* > m_objectsByName;
		unordered_map< unsigned int, AGGameObject* > m_objectsById; 
		list< AGGameObject* > m_objects; 

		AGGameObject* m_selectedObject; 

		string m_name; 

};

#endif 