#ifndef AG_GRAPHICS_H
#define AG_GRAPHICS_H

#include <d3dx10.h>
#include <d3d10.h>
#include <dxgi.h>

#include <list>
#include <string>
#include <vector>
#include <map>

#include "Math/AGMath.h"

#include "Patterns/Singleton.h"

#include "Managers/AGEStateManager.h"
#include "Managers/AGInputManager.h"

#include "Objects/System/AGConsole.h"

#include "Interfaces/AGPrimitive.h"
#include "Interfaces/AGPureInterfaces.h"

#include "AGInputLayouts.h"

#include "AGGraphicsHelper.h"

class AGGameObject; 
class AGSurface; 
class AGManipulator;
class AGCamera; 
class AGLight; 
class AGRenderer; 
class AGClickable;

struct AGLightDesc; 

using namespace std;

struct AGRasterizeState 
{
	ID3D10RasterizerState* wireframe; 
	ID3D10RasterizerState* solid; 
};

class AGGraphics
{
	DECLARE_SINGLETON_INIT( AGGraphics )
	public:
		enum AGVertexType{ Vertex, ColorVertex, SimpleVertex, TextureVertex };

		void update();

		void createRasterizeStates(); 

		void setBackgroundColor( const AGPoint3& color );
		void setBackgroundColor( float r, float g, float b );
		const AGPoint3& getBackgroundColor() const; 

		void addSurface( AGSurface* surface );
		void removeSurface( AGSurface* surface );
		const list< AGSurface* >& getSurfaces() const;  

		//При добавлении объекта, отрисовывается его оси, если не выбран способ манипулирования
		void addSelectedObject( AGGameObject* object );
		void removeSelectedObject( AGGameObject* object );

		void addClickableObject( AGClickable* object ); 
		void removeClickableObject( AGClickable* object) ;
		
		void addManipulator( AGManipulator* manipulator );
		void removeManipulator( AGManipulator* manipulator ); 

		void addDrawable( AGDrawable* drawable );

		void addRenderer( AGRenderer* renderer );
		void removeRenderer( AGRenderer* renderer );
		vector< AGRenderer* > getRenderers() const; 

		AGCamera* createCamera();
		void removeCamera( AGCamera* camera );
		AGCamera* getTopCamera() const; 
		vector< AGCamera* > getCameras() const; 

		void mouseClickEvent( AGMouseButton btn ); 
		void mouseReleaseEvent( AGMouseButton btn );
		void mouseMoveEvent();
		void keyDownEvent( int keyCode );
		void keyUpEvent( int keyCode );
		void mouseWheelMove( int wheelDelta ); 

		void setFocusSurface( AGSurface* surface ); 

		IDXGIFactory* getDXGIFactory() const;
		ID3D10Device* getDevice() const;  

		AGInputLayout* getInputLayout( ID3D10Device* device );  

		AGRasterizeState* getRasterizeState( ID3D10Device* device ); 
		void switchTo( AGVertexType type ); 

		void addLight( AGLight* light ); 
		void removeLight( AGLight* light );
		list< AGLight* > getLights() const; 

		unsigned int getCurrentSurfaceID(); 

		void setFPS( int fps );
	private:
		void init();

		IDXGIFactory* m_dxgiFactory; 
		ID3D10Device* m_device; 

		AGSurface* m_focusSurface; 

		AGEStateManager::ToolBarState m_toolBarState; 
		AGPoint3 m_backgroundColor; 
		list< AGClickable* > m_clickableObjects; 
		list< AGManipulator* > m_manipulators; 
		list< AGSurface* > m_surfaces; 
		list< AGGameObject* > m_selectedObject; 
		list< AGLight* > m_lights; 
		list< AGDrawable* > m_drawables; 

		map< ID3D10Device*, AGInputLayout* > m_inputLayouts; 
		map< ID3D10Device*, AGRasterizeState* > m_rasterizeStates;  

		vector< ID3D10DepthStencilState* > m_depthState; 

		vector< AGRenderer* > m_renderers;
		vector< AGCamera* > m_cameras; 
		map< int, AGCamera* > m_camerasByLayer; 

		int m_fps; 

		AGConsole* m_console; 
};

#endif 