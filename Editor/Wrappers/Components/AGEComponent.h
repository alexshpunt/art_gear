#ifndef AGE_COMPONENT_H
#define AGE_COMPONENT_H

#include "QWidget"

#include "Engine/Objects/AGComponent.h"

class AGEGameObject; 

/*
	Этот класс является обёрткой для оригинального класса AGComponent
	Реализовывает специфичную для редактора функциональность
*/
class AGEComponent
{
	public:
		AGEComponent( AGEGameObject* object );
		~AGEComponent();

		virtual QWidget* getWidget() = 0; 

		AGEGameObject* getGameObject() const;

	private:
		AGEGameObject* m_gameObject;
		AGComponent* m_component; 
};

#endif 