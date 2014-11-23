#ifndef AG_ENGINE_H
#define AG_ENGINE_H

#include <windows.h>

#include "Patterns/Singleton.h"
#include "Graphics/AGGraphics.h"

class AGScene; 

class AGEngine 
{
	DECLARE_SINGLETON_INIT( AGEngine )
	public:
		int run();
		void update(); 

		void setScene( AGScene* scene );
		AGScene* getScene() const; 

	private:
		void init(); 
		AGScene* m_scene; 
		
};

#endif 