#ifndef AGE_STATEMANAGER_H
#define AGE_STATEMANAGER_H

#include "Engine/Patterns/Singleton.h"

class AGStateManager 
{
	DECLARE_SINGLETON_INIT( AGStateManager )
	public:
		void setRotating( bool value );
		bool isRotating() const; 
	private:
		void init(); 

		bool m_isRotating; 
};

#endif 