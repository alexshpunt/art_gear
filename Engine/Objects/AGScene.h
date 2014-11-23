#ifndef AG_SCENE_H
#define AG_SCENE_H

#include <list>
#include <unordered_map>
#include <string>

#include "Math/AGMath.h"

using namespace std;

class AGObject; 

class AGScene 
{
	public:
		AGScene( string name );
		~AGScene();

		void init(); 
		void update(); 
		void fixedUpdate(); 

		AGObject* createObject( string name );
		AGObject* copyFrom( AGObject* object );
		bool containsObjectWithName( const string& name );
		bool containsObjectWithId( unsigned int id );
		bool containsObject( AGObject* object );

		//Удаляет объект со сцены и освобождает память, все указатели на этот объект станут невалидными! 
		void removeObject( AGObject* object );
		void removeObjectByName( const string& name );
		void removeObjectById( unsigned int id ); 

		const string& getName() const; 

	private: 
		unsigned int m_curValidId; 

		unordered_map< string, AGObject* > m_objectsByName;
		unordered_map< unsigned int, AGObject* > m_objectsById; 
		list< AGObject* > m_objects; 

		string m_name; 

};

#endif 