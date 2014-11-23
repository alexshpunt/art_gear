#ifndef AG_SURFACE_H
#define AG_SURFACE_H

#include <d3d10.h>
#include <d3dx10.h>

#include "Math/AGMath.h"

class AGDXCamera; 

class AGDXSurface 
{
	public:
		AGDXSurface( float width, float height, HWND hwnd );
		virtual ~AGDXSurface();

		ID3D10Device* getDevice() const;
		IDXGISwapChain* getSwapChain() const;
		ID3D10RenderTargetView* getRenderTargetView() const; 
		ID3D10DepthStencilView* getDepthStencilView() const; 
		AGDXCamera* getCamera() const; 

		const AGSize& getSize() const;
		float getWidth() const;
		float getHeight() const; 

	protected:
		void resizeSurface( float width, float height ); 

		ID3D10Device* m_device; 
		IDXGISwapChain* m_swapChain; 
		ID3D10RenderTargetView* m_renderTargetView; 
		ID3D10DepthStencilView* m_depthStencilView; 
		ID3D10Texture2D* m_depthBuffer;
		AGDXCamera* m_camera; 
		HWND m_hwnd;
		AGSize m_size; 
};

#endif 