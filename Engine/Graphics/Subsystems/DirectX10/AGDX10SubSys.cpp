#include "AGDX10SubSys.h"

#include <DxErr.h>
#include "Managers/AGLogger.h"

AGDX10SubSys::AGDX10SubSys( AGWindow* window ) : AGAbstractSubsystem( window )
{
}

AGDX10SubSys::~AGDX10SubSys()
{

}

void AGDX10SubSys::initialize()
{
	HRESULT hr = S_OK; 

	UINT createDeviceFlags = 0; 
#ifdef _DEBUG
	createDeviceFlags |= D3D10_CREATE_DEVICE_DEBUG;
#endif 

	DXGI_SWAP_CHAIN_DESC swapChainDesc; 
	ZeroMemory( &swapChainDesc, sizeof( swapChainDesc ) ); 
	swapChainDesc.BufferCount = 2; 
	swapChainDesc.BufferDesc.Height = m_window->getSize().getHeight(); 
	swapChainDesc.BufferDesc.Width = m_window->getSize().getWidth();
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60; 
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1; 
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; 
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; 
	swapChainDesc.OutputWindow = m_window->asHwnd(); 
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
	AGSucces() << "Device and swap chain was created";

	ID3D10Texture2D* backBuffer; 
	hr = m_swapChain->GetBuffer( 0, __uuidof( ID3D10Texture2D ), ( LPVOID* )&backBuffer );

	if( FAILED( hr ) )
	{
		AGDebug() << "Cannot get buffer from swap chain for back buffer, error: " << DXGetErrorDescription( hr );
		return; 
	}
	AGSucces() << "Back buffer was created";

	hr = m_device->CreateRenderTargetView( backBuffer, NULL, &m_renderTargetView );
	backBuffer->Release(); 
	if( FAILED( hr ) )
	{
		AGDebug() << "Cannot create render target view, error code, error: " << DXGetErrorDescription( hr );
		return; 
	}
	AGSucces() << "Render target view was created";

	m_device->OMSetRenderTargets( 1, &m_renderTargetView, NULL );

	D3D10_VIEWPORT viewport; 
	viewport.Height = m_window->getSize().getHeight();
	viewport.Width = m_window->getSize().getWidth(); 
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.MaxDepth = 1.0f;
	viewport.MinDepth = 0.0f; 
	m_device->RSSetViewports( 1, &viewport ); 
	AGSucces() << "DX10SubSystem was initialized";
}

void AGDX10SubSys::update()
{
	if( !m_device ) 
		return; 
	float clearColor[ 4 ] = { 0.3f, 0.3f, 0.3f, 1.0f };
	m_device->ClearRenderTargetView( m_renderTargetView, clearColor );
	m_swapChain->Present( 0, 0 );
}

