#ifndef AG_GAMEOBJECT_H
#define AG_GAMEOBJECT_H

#include <string>
#include <list>
#include <map>
#include <unordered_map>

#include "Interfaces/AGObject.h"
#include "Math/AGMath.h"


using namespace std;

class AGRenderer; 
class AGGameScene; 
class AGComponent;
class AGGameObjectNotifyFunctor; 

/*
 * Класс объекта, его можно создавать только через метод AGScene, ибо только сцена должна иметь контроль 
 * над созданием и удалением объекта, во избежания утечек памяти. 
 **/
class AGGameObject : public AGObject
{
	friend class AGGameScene; 
	public:
		enum Change{ LocalPos, LocalRot, LocalScale, WorldPos, WorldRot, WorldScale, Visiable, Name };

		void setPivot( const AGVec3& pivot );
		void setPivot( float posX, float posY, float posZ );
		const AGVec3& getPivot() const;

		void setLocalXPos( float posX );
		float getLocalXPos() const;

		void setLocalYPos( float posY );
		float getLocalYPos() const; 

		void setLocalZPos( float posZ );
		float getLocalZPos() const; 

		void setLocalPos( const AGVec3& pos );
		void setLocalPos( float posX, float posY, float posZ );
		const AGVec3& getLocalPos() const;

		void translateLocalX( float dX );
		void translateLocalY( float dY );
		void translateLocalZ( float dZ );

		void translateLocal( const AGVec3& dir );
		void translateLocal( float dX, float dY, float dZ );

		void setWorldXPos( float posX );
		float getWorldXPos() const;

		void setWorldYPos( float posY );
		float getWorldYPos() const; 

		void setWorldZPos( float posZ );
		float getWorldZPos() const; 

		void setWorldPos( const AGVec3& pos );
		void setWorldPos( float posX, float posY, float posZ );
		const AGVec3& getWorldPos() const;

		void translateWorldX( float dX );
		void translateWorldY( float dY );
		void translateWorldZ( float dZ );

		void translateWorld( const AGVec3& dir );
		void translateWorld( float dX, float dY, float dZ );

		void setLocalXRot( float angleX ); 
		float getLocalXRot() const;

		void setLocalYRot( float angleY );
		float getLocalYRot() const; 

		void setLocalZRot( float angleZ );
		float getLocalZRot() const;

		void setLocalRot( const AGVec3& angles );
		void setLocalRot( float angleX, float angleY, float angleZ );
		const AGVec3& getLocalRot() const;

		void rotateLocalAxis( const AGVec3& axis, float angle );
		void rotateLocalX( float angleX );
		void rotateLocalY( float angleY );
		void rotateLocalZ( float angleZ );
		void rotateLocal( const AGVec3& angles );
		void rotateLocal( float angleX, float angleY, float angleZ );

		void setWorldXRot( float angleX );
		float getWorldXRot() const;

		void setWorldYRot( float angleY );
		float getWorldYRot() const; 

		void setWorldZRot( float angleZ );
		float getWorldZRot() const; 

		void setWorldRot( const AGVec3& angles );
		void setWorldRot( float angleX, float angleY, float angleZ );
		const AGVec3& getWorldRot() const;

		void rotateWorldAxis( const AGVec3& axis, float angle );

		void rotateAroundWorldX( float angleX );
		void rotateAroundWorldY( float angleY );
		void rotateAroundWorldZ( float angleZ );

		void rotateWorldX( float angleX );
		void rotateWorldY( float angleY );
		void rotateWorldZ( float angleZ );
		void rotateWorld( const AGVec3& angles );
		void rotateWorld( float angleX, float angleY, float angleZ );

		void setLocalXScale( float scaleX );
		float getLocalXScale() const;
		
		void setLocalYScale( float scaleY );
		float getLocalYScale() const;

		void setLocalZScale( float scaleZ );
		float getLocalZScale() const; 

		void setLocalScale( const AGVec3& scale );
		void setLocalScale( float scaleX, float scaleY, float scaleZ );
		const AGVec3& getLocalScale() const;

		void scaleLocal( const AGVec3& scale );
		void scaleLocal( float dsX, float dsY, float dsZ );

		void setWorldXScale( float scaleX );
		float getWorldXScale() const;

		void setWorldYScale( float scaleY );
		float getWorldYScale() const;

		void setWorldZScale( float scaleZ );
		float getWorldZScale() const; 

		void setWorldScale( const AGVec3& scale );
		void setWorldScale( float scaleX, float scaleY, float scaleZ );
		const AGVec3& getWorldScale() const;

		void scaleWorld( const AGVec3& scale );
		void scaleWorld( float dsX, float dsY, float dsZ );		

		void setName( const string& name );
		const string& getName() const;

		unsigned int getId() const;

		AGGameScene* getScene() const; 

		void addComponent( AGComponent* component );
		void addComponentByName( const string& name );
		bool containsComponent( const string& name );
		void removeComponent( const string& name );
		void removeAllComponents();
		AGComponent* getComponent( const string& name );
		const list< AGComponent* >& getComponents() const;  

		void addChild( AGGameObject* object );
		void removeChild( AGGameObject* object );
		AGGameObject* getChild( const string& name );
		const list< AGGameObject* >& getChildren() const; 

		void setSelected( bool flag );
		bool isSelected() const;

		AGRenderer* getRenderer() const; 

		void registerNotifyFunctor( AGGameObjectNotifyFunctor* func );
		void unregisterNotifyFunctor( AGGameObjectNotifyFunctor* func );

	private:
		AGGameObject( const string& name, unsigned int id, AGGameScene* scene );
		AGGameObject( const string& name, unsigned int id, AGGameScene* scene, const AGGameObject* object ); 
		AGGameObject( const AGGameObject& object );
		~AGGameObject();

		//Пересылаются компонентам данного объекта
		void onSceneInit(); 
		void onSceneUpdate();
		void onSceneFixedUpdate(); 

		list< AGGameObjectNotifyFunctor* > m_notifyFunctors; 

		string m_name; 
		unsigned int m_id; 
		AGGameScene* m_scene; 
		AGGameObject* m_parent; 
		list< AGGameObject* > m_children;
		unordered_map< string, AGGameObject* > m_childrenByName; 
		list< AGComponent* > m_components;
		unordered_map< string, AGComponent* > m_componentsByName; 

		bool m_isSelected; 

		AGVec3 m_pivot;
		AGVec3 m_localPos;
		AGVec3 m_localRot;
		AGVec3 m_localScale; 

		AGVec3 m_worldPos;
		AGVec3 m_worldRot;
		AGVec3 m_worldScale; 

		AGRenderer* m_renderer; 
};

class AGGameObjectTransformEvent 
{
	
};

#endif 