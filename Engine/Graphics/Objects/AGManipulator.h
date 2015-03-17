#ifndef AG_MANIPULATOR_H
#define AG_MANIPULATOR_H

#include <d3dx10.h>
#include <d3d10.h>
#include <string>
#include <list>

#include "Engine/Graphics/Interfaces/AGPureInterfaces.h"
#include "Managers/AGInputManager.h"

class AGSurface; 
class AGGameObject; 

using namespace std; 

class AGManipulator : public AGClickable
{
	public:
		AGManipulator();
		virtual ~AGManipulator(); 

		void setObjects( list< AGGameObject* > objects );
		list< AGGameObject* > getObjects() const; 

		void setObject( AGGameObject* object );
		AGGameObject* getObject() const; 

	protected:
		list< AGGameObject* > m_objects;
		AGGameObject* m_object; 
};

#endif 