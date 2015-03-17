#ifndef AG_GAMEOBJECTNOTIFYFUNCTOR_H
#define AG_GAMEOBJECTNOTIFYFUNCTOR_H

#include "Objects/AGGameObject.h"

class AGGameObjectNotifyFunctor
{
	public:
		virtual void operator()( AGGameObject::Change change ) = 0; 
};

#endif 