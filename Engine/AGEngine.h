#ifndef AG_ENGINE_H
#define AG_ENGINE_H

#include <windows.h>

#include "Patterns/Singleton.h"
#include "Graphics/AGGraphics.h"

class AGGameScene; 

class AGEngine 
{
	DECLARE_SINGLETON_INIT( AGEngine )
	public:
		int run();
		void update(); 

		void setScene( AGGameScene* scene );
		AGGameScene* getScene() const; 

	private:
		void init(); 
		AGGameScene* m_scene; 
		
};

#endif 