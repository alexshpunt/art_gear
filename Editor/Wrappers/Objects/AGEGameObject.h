#ifndef AGE_GAMEOBJECT_H
#define AGE_GAMEOBJECT_H

#include <string>

#include "Engine/Objects/AGGameObject.h"

#include "Editor/UI/AGESceneView.h"

/*
	Данный класс - это обёртка вокруг оригинального AGGameObject
	Реализовывает специфичную для редактора функциональность
*/
class AGEGameObject 
{
	public:
		AGEGameObject( AGGameObject* object );
		~AGEGameObject();

		const std::string& getName() const;

		void setSelected( bool value );
		bool isSelected() const; 

		AGESceneViewItem* getItem() const; 

	private:
		AGGameObject* m_gameObject; 

		AGESceneViewItem* m_item; 

		std::string m_name; 
		bool m_isSelected; 
};

#endif 