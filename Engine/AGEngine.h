#ifndef AG_ENGINE_H
#define AG_ENGINE_H

#include <windows.h>
#include <vector>

#include "Patterns/Singleton.h"
#include "Graphics/AGGraphics.h"
#include "Interfaces/AGAbstractSystem.h" 

using namespace std;

typedef vector< AGAbstractSystem* > AGAbstractSystems; 

class AGEngine 
{
	public:
		AGEngine();
		~AGEngine();

		void initialize(); 
		int run();
		void processEvents(); 

		AGGraphics& getGraphicsSystem();

	private:
		void update(); 
		void shutdown();

		AGGraphics m_graphics; 
};

#endif 