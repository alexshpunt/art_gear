#ifndef AG_OBJECT_H
#define AG_OBJECT_H

#include <string>
#include <list>
#include <map>
#include <unordered_map>
#include "Math/AGMath.h"

using namespace std;

class AGRenderer; 
class AGScene; 
class AGComponent;

/*
 * КЉласс объекта, его можно создавать только через метод AGScene, ибо только сцена должна иметь контроль 
 * над созданием и удалением объекта, во избежания утечек памяти. 
 **/
class AGObject
{
	friend class AGScene; 

	public:
		void setPivot( const AGVec3& pivot );
		void setPivot( float posX, float posY, float posZ );
		const AGVec3& getPivot() const;

		void setPos( const AGVec3& pos );
		void setPos( float posX, float posY, float posZ );
		const AGVec3& getPos() const;

		void setRotation( const AGVec3& angles );
		void setRotation( float angleX, float angleY, float angleZ );
		const AGVec3& getRotation() const;

		void setScale( const AGVec3& scale );
		void setScale( float scaleX, float scaleY, float scaleZ );
		const AGVec3& getScale() const;

		void translate( const AGVec3& dir );
		void translate( float dX, float dY, float dZ );

		void rotateX( float angleX );
		void rotateY( float angleY );
		void rotateZ( float angleZ );
		void rotate( float angleX, float angleY, float angleZ );

		void scale( const AGVec3& scale );
		void scale( float dsX, float dsY, float dsZ );

		void setName( const string& name );
		const string& getName() const;

		unsigned int getId() const;

		AGScene* getScene() const; 

		void addComponent( AGComponent* component );
		void addComponentByName( const string& name );
		bool containsComponent( const string& name );
		void removeComponent( const string& name );
		void removeAllComponents();
		AGComponent* getComponent( const string& name );
		const list< AGComponent* >& getComponents() const;  

		void addChild( AGObject* object );
		void removeChild( AGObject* object );
		AGObject* getChild( const string& name );
		const list< AGObject* >& getChildren() const; 

		void setSelected( bool flag );
		bool isSelected() const;

		AGRenderer* getRenderer() const; 

	private:
		AGObject( const string& name, unsigned int id, AGScene* scene );
		AGObject( const string& name, unsigned int id, AGScene* scene, const AGObject* object ); 
		AGObject( const AGObject& object );
		~AGObject();

		//Пересылаются компонентам данного объекта
		void onSceneInit(); 
		void onSceneUpdate();
		void onSceneFixedUpdate(); 

		string m_name; 
		unsigned int m_id; 
		AGScene* m_scene; 
		AGObject* m_parent; 
		list< AGObject* > m_children;
		unordered_map< string, AGObject* > m_childrenByName; 
		list< AGComponent* > m_components;
		unordered_map< string, AGComponent* > m_componentsByName; 

		bool m_isSelected; 

		AGVec3 m_pivot;
		AGVec3 m_pos;
		AGVec3 m_rotation;
		AGVec3 m_scale; 

		AGRenderer* m_renderer; 
};

#endif 