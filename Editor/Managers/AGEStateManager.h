#ifndef AGE_STATEMANAGER_H
#define AGE_STATEMANAGER_H

#include "Engine/Patterns/Singleton.h"

class AGEStateManager 
{
	DECLARE_SINGLETON_INIT( AGEStateManager )
	public:
		enum CoordSystem { Local, World, View };
		enum ToolBarState{ Axis, Dragger, Rotater, Scaler };

		void setRotating( bool value );
		bool isRotating() const; 

		void setCoordystem( CoordSystem system ); 
		CoordSystem getCoordSystem() const; 

		void setToolBarState( ToolBarState state );
		ToolBarState getToolBarState() const; 

		void setShowingAxis( bool value );
		bool isShowingAxis() const; 

		void setConsoleMode( bool value );
		bool isConsoleMode() const; 

		void setShowingMouseArrow( bool value );
		bool isShowingMouseArrow() const; 

		void setCameraFov( int fov );
		int getCameraFov(); 
		bool isCameraFovChanged() const; 

		void setPlayMode( bool value );
		bool isPlayMode() const; 

	private:
		void init(); 

		ToolBarState m_toolBarState; 
		CoordSystem m_coordSystem; 
		bool m_isRotating; 
		bool m_isShowingAxis; 
		bool m_isConsoleMode; 
		bool m_isShowingMouseArrow; 
		bool m_isPlayMode; 

		int m_cameraFov;
		bool m_isCameraFovChanged; 
};

#endif 