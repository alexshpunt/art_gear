#ifndef AG_ENGINE_H
#define AG_ENGINE_H

#include <windows.h>
#include <vector>

#include "Interfaces/AGAbstractSystem.h" 

using namespace std;

typedef vector< AGAbstractSystem* > AGAbstractSystems; 

class AGEngine 
{
	public:
		AGEngine();
		~AGEngine();

		int run();

	private:
		void update(); 
		void shutdown();

		AGAbstractSystems m_systems; 
};

#endif 