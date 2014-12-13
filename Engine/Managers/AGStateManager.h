#ifndef AGE_STATEMANAGER_H
#define AGE_STATEMANAGER_H

#include "Engine/Patterns/Singleton.h"

class AGStateManager 
{
	DECLARE_SINGLETON_INIT( AGStateManager )
	public:
		enum CoordSystem { Local, World, View };
		enum ToolBarState{ Axis, Dragger, Rotater, Scaler };

		void setRotating( bool value );
		bool isRotating() const; 

		void setCoordystem( CoordSystem system ); 
		CoordSystem getCoordSystem() const; 

		void setToolBarState( ToolBarState state );
		ToolBarState getToolBarState() const; 

	private:
		void init(); 

		ToolBarState m_toolBarState; 
		CoordSystem m_coordSystem; 
		bool m_isRotating; 
};

#endif 