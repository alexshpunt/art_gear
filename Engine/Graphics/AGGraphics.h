#ifndef AG_GRAPHICS_H
#define AG_GRAPHICS_H

#include <list>
#include <string>
#include <vector>
#include <map>
#include "Math/AGMath.h"
#include "Patterns/Singleton.h"

class AGObject; 
class AGDXSurface; 
class AGDXDragger; 
class AGDXRotater; 
class AGDXArrow; 
class AGDXCamera; 
class AGDXLight; 
class AGRenderer; 

using namespace std;

class AGGraphics
{
	DECLARE_SINGLETON_INIT( AGGraphics )
	public:
		enum Modes{ DirectX, OpenGL };

		void update();

		void setMode( Modes mode );
		Modes getMode() const; 

		void setBackgroundColor( const AGPoint3& color );
		void setBackgroundColor( float r, float g, float b );
		const AGPoint3& getBackgroundColor() const; 

		void addSurface( AGDXSurface* surface );
		void removeSurface( AGDXSurface* surface );
		const list< AGDXSurface* >& getSurfaces() const;  

		//При добавлении объекта, отрисовывается его оси, если не выбран способ манипулирования
		void addSelectedObject( AGObject* object );
		void removeSelectedObject( AGObject* object );

		void addRenderer( AGRenderer* renderer );
		void removeRenderer( AGRenderer* renderer );
		vector< AGRenderer* > getRenderers() const; 

		AGDXCamera* createCamera();
		void removeCamera( AGDXCamera* camera );
		AGDXCamera* getTopCamera() const; 
		vector< AGDXCamera* > getCameras() const; 

		void mouseClickEvent( const string& btn ); 
		void mouseMoveEvent(); 

	private:
		void init();

		Modes m_mode; 
		AGPoint3 m_backgroundColor; 
		list< AGDXSurface* > m_surfaces; 
		list< AGObject* > m_selectedObject; 

		vector< AGRenderer* > m_renderers;
		vector< AGDXCamera* > m_cameras; 
		map< int, AGDXCamera* > m_camerasByLayer; 

		AGDXDragger* m_dragger;
		AGDXRotater* m_rotater; 
};

#endif 