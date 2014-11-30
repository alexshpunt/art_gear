#include "AGSurface.h"

#include <DxErr.h>

#include "Managers/AGLogger.h"
#include "Managers/AGGraphicsSettings.h"
#include "Graphics/Objects/AGDXCamera.h"
#include "Graphics/AGGraphics.h"

AGDXSurface::AGDXSurface( float width, float height, HWND hwnd )
{
	m_camera = AGGraphics::getInstance().createCamera(); 
	m_hwnd = hwnd; 

	HRESULT hr = S_OK; 

	UINT createDeviceFlags = 0; 
#ifdef _DEBUG
	createDeviceFlags |= D3D10_CREATE_DEVICE_DEBUG;
#endif 

	DXGI_SWAP_CHAIN_DESC swapChainDesc; 
	ZeroMemory( &swapChainDesc, sizeof( swapChainDesc ) ); 
	swapChainDesc.BufferCount = 2; 
	swapChainDesc.BufferDesc.Height = width;
	swapChainDesc.BufferDesc.Width = height;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60; 
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1; 
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; 
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; 
	swapChainDesc.OutputWindow = m_hwnd; 
	swapChainDesc.SampleDesc.Count = 1; 
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.Windowed = TRUE; 

	hr = D3D10CreateDeviceAndSwapChain( NULL, D3D10_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, 
		D3D10_SDK_VERSION, &swapChainDesc, &m_swapChain, &m_device );

	if( FAILED( hr ) )
	{
		AGError() << "Cannot create device or swap chain, error: " << DXGetErrorDescriptionA( hr );
		return; 
	}

	ID3D10Texture2D* backBuffer; 
	hr = m_swapChain->GetBuffer( 0, __uuidof( backBuffer ), ( LPVOID* )&backBuffer );

	if( FAILED( hr ) )
	{
		AGError() << "Cannot get buffer from swap chain for back buffer, error: " << DXGetErrorDescription( hr );
		return; 
	}

	D3D10_TEXTURE2D_DESC descDepth; 
	descDepth.Width = width;
	descDepth.Height = height;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1; 
	descDepth.Format = DXGI_FORMAT_D32_FLOAT; 
	descDepth.SampleDesc.Count = 1; 
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D10_USAGE_DEFAULT;
	descDepth.BindFlags = D3D10_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0; 

	hr = m_device->CreateTexture2D( &descDepth, NULL, &m_depthBuffer );

	if( FAILED( hr ) )
	{
		AGError() << "Couldn't create depth stencil buffer, error: " << DXGetErrorDescription( hr );
		return; 
	}

	D3D10_DEPTH_STENCIL_VIEW_DESC descDSV;
	descDSV.Format = descDepth.Format; 
	descDSV.ViewDimension = D3D10_DSV_DIMENSION_TEXTURE2D; 
	descDSV.Texture2D.MipSlice = 0; 

	hr = m_device->CreateDepthStencilView( m_depthBuffer, &descDSV, &m_depthStencilView );

	if( FAILED( hr ) )
	{
		AGError() << "Couldn't create depth stencil view, error: " << DXGetErrorDescription( hr );
		return; 
	}

	hr = m_device->CreateRenderTargetView( backBuffer, NULL, &m_renderTargetView );
	backBuffer->Release(); 
	if( FAILED( hr ) )
	{
		AGError() << "Cannot create render target view, error code, error: " << DXGetErrorDescription( hr );
		return; 
	}

	m_device->OMSetRenderTargets( 1, &m_renderTargetView, m_depthStencilView );

	D3D10_VIEWPORT viewport; 
	viewport.Height = 800;
	viewport.Width = 600; 
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.MaxDepth = 1.0f;
	viewport.MinDepth = 0.0f; 
	m_device->RSSetViewports( 1, &viewport ); 

	m_size = AGSize( width, height );
}

AGDXSurface::~AGDXSurface()
{

}


ID3D10Device* AGDXSurface::getDevice() const
{
	return m_device;
}

IDXGISwapChain* AGDXSurface::getSwapChain() const
{
	return m_swapChain;
}

ID3D10RenderTargetView* AGDXSurface::getRenderTargetView() const
{
	return m_renderTargetView;
}

ID3D10DepthStencilView* AGDXSurface::getDepthStencilView() const
{
	return m_depthStencilView; 
}

AGDXCamera* AGDXSurface::getCamera() const
{
	return m_camera; 
}

void AGDXSurface::resizeSurface(float width, float height )
{
		m_renderTargetView->Release();
	m_depthBuffer->Release();
	m_depthStencilView->Release();

	m_swapChain->ResizeBuffers( 2, width, height,
		DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH );

	ID3D10Texture2D* backBuffer; 
	HRESULT hr = m_swapChain->GetBuffer( 0, __uuidof( backBuffer ), ( LPVOID* )&backBuffer );

	if( FAILED( hr ) )
	{
		AGError() << "Cannot get buffer from swap chain for back buffer, error: " << DXGetErrorDescription( hr );
		return; 
	}

	hr = m_device->CreateRenderTargetView( backBuffer, NULL, &m_renderTargetView );
	backBuffer->Release(); 
	
	D3D10_TEXTURE2D_DESC descDepth; 
	descDepth.Width = width;
	descDepth.Height = height;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1; 
	descDepth.Format = DXGI_FORMAT_D32_FLOAT; 
	descDepth.SampleDesc.Count = 1; 
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D10_USAGE_DEFAULT;
	descDepth.BindFlags = D3D10_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0; 

	hr = m_device->CreateTexture2D( &descDepth, NULL, &m_depthBuffer );

	if( FAILED( hr ) )
	{
		AGError() << "Couldn't create depth stencil buffer, error: " << DXGetErrorDescription( hr );
		return; 
	}

	D3D10_DEPTH_STENCIL_VIEW_DESC descDSV;
	descDSV.Format = descDepth.Format; 
	descDSV.ViewDimension = D3D10_DSV_DIMENSION_TEXTURE2D; 
	descDSV.Texture2D.MipSlice = 0; 

	hr = m_device->CreateDepthStencilView( m_depthBuffer, &descDSV, &m_depthStencilView );

	if( FAILED( hr ) )
	{
		AGError() << "Couldn't create depth stencil view, error: " << DXGetErrorDescription( hr );
		return; 
	}

	D3D10_VIEWPORT viewPort; 
	viewPort.Width = width;
	viewPort.Height = height;
	viewPort.MaxDepth = 1.0f;
	viewPort.MinDepth = 0.0f;
	viewPort.TopLeftX = 0;
	viewPort.TopLeftY = 0;

	m_device->RSSetViewports( 1, &viewPort );

	m_device->OMSetRenderTargets( 1, &m_renderTargetView, m_depthStencilView );

	AGGraphicsSettings::getInstance().setScreenWidth( width );
	AGGraphicsSettings::getInstance().setScreenHeight( height );

	m_camera->setAspectRatio( width / height );

	m_size = AGSize( width, height );

	AGGraphics::getInstance().update();
}

const AGSize& AGDXSurface::getSize() const
{
	return m_size; 
}

float AGDXSurface::getWidth() const
{
	return m_size.getWidth();
}

float AGDXSurface::getHeight() const
{
	return m_size.getHeight();
}
