#ifndef AG_DIRECTX10SUBSYS_H
#define AG_DIRECTX10SUBSYS_H

#include <d3d10.h>
#include <d3dx10.h>

#include "Objects/AGDX10Mesh.h"
#include "Patterns/Singleton.h"
#include "Graphics/Subsystems/AGAbstractSubSystem.h"

class AGDX10SubSys
{
	public:
		AGDX10SubSys();
		~AGDX10SubSys();
		void initialize( AGWindow* window ); 
		void update();  

		ID3D10Device* getDevice();
	private:
		ID3D10Device* m_device; 
		IDXGISwapChain* m_swapChain; 
		ID3D10RenderTargetView* m_renderTargetView; 
		ID3D10DepthStencilView* m_depthStencilView; 
		ID3D10InputLayout* m_vertexLayout; 
		ID3D10Buffer* m_buffer; 
		ID3D10Texture2D* m_depthBuffer; 

		AGWindow* m_window; 
		AGDX10Mesh* m_mesh; 
};

#endif 