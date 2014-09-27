#ifndef AG_DIRECTX10SUBSYS_H
#define AG_DIRECTX10SUBSYS_H

#include <d3d10.h>
#include <d3dx10.h>

#include "Graphics/Subsystems/AGAbstractSubSystem.h"

class AGDX10SubSys : public AGAbstractSubsystem 
{
	public:
		AGDX10SubSys( AGWindow* window );
		~AGDX10SubSys();

		void initialize(); 
		void update();  

	private:
		ID3D10Device* m_device; 
		IDXGISwapChain* m_swapChain; 
		ID3D10RenderTargetView* m_renderTargetView; 
};

#endif 