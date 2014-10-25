#include "AGDX10SubSys.h"

#include <DxErr.h>
#include "Managers/AGLogger.h"

AGDX10SubSys::AGDX10SubSys()
{

}

AGDX10SubSys::~AGDX10SubSys()
{

}

void AGDX10SubSys::initialize( AGWindow* window )
{
	m_window = window; 
	HRESULT hr = S_OK; 

	UINT createDeviceFlags = 0; 
#ifdef _DEBUG
	createDeviceFlags |= D3D10_CREATE_DEVICE_DEBUG;
#endif 

	DXGI_SWAP_CHAIN_DESC swapChainDesc; 
	ZeroMemory( &swapChainDesc, sizeof( swapChainDesc ) ); 
	swapChainDesc.BufferCount = 2; 
	swapChainDesc.BufferDesc.Height = 800;//m_window->getSize().getHeight(); 
	swapChainDesc.BufferDesc.Width = 600;//m_window->getSize().getWidth();
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


	hr = D3D10CreateDevice( NULL, D3D10_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, D3D10_SDK_VERSION, &m_device );

	if( FAILED( hr ) )
	{
		AGError() << "Cannot create device or swap chain, error: " << DXGetErrorDescriptionA( hr );
		return; 
	}
	AGSucces() << "Device and swap chain was created";

	ID3D10Texture2D* backBuffer; 
	hr = m_swapChain->GetBuffer( 0, __uuidof( backBuffer ), ( LPVOID* )&backBuffer );

	if( FAILED( hr ) )
	{
		AGError() << "Cannot get buffer from swap chain for back buffer, error: " << DXGetErrorDescription( hr );
		return; 
	}
	AGSucces() << "Back buffer was created";

	D3D10_TEXTURE2D_DESC descDepth; 
	descDepth.Width = m_window->getSize().getWidth();
	descDepth.Height = m_window->getSize().getHeight();
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

	IDXGISurface* surface; 
	hr = m_swapChain->GetBuffer( 0, __uuidof( IDXGISurface ), (void**)&surface ); 

	if( FAILED( hr ) )
	{
		AGError() << "Cannot query surface, error: " << DXGetErrorDescription( hr );
		return; 
	}
	AGSucces() << "Surface was quered";

	hr = m_device->CreateRenderTargetView( backBuffer, NULL, &m_renderTargetView );
	backBuffer->Release(); 
	if( FAILED( hr ) )
	{
		AGError() << "Cannot create render target view, error code, error: " << DXGetErrorDescription( hr );
		return; 
	}
	AGSucces() << "Render target view was created";

	m_device->OMSetRenderTargets( 1, &m_renderTargetView, m_depthStencilView );

	D3D10_VIEWPORT viewport; 
	viewport.Height = m_window->getSize().getHeight();
	viewport.Width = m_window->getSize().getWidth(); 
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.MaxDepth = 1.0f;
	viewport.MinDepth = 0.0f; 
	m_device->RSSetViewports( 1, &viewport ); 
	AGSucces() << "DX10SubSystem was initialized";

	m_mesh = new AGDX10Mesh; 
	m_mesh->loadFrom( "data/meshes/irish.agmsh", m_device );
}

void AGDX10SubSys::update()
{
	if( !m_device ) 
		return; 
	float clearColor[ 4 ] = { 0.3f, 0.3f, 0.3f, 1.0f };
	m_device->ClearRenderTargetView( m_renderTargetView, clearColor );
	m_device->ClearDepthStencilView( m_depthStencilView, D3D10_CLEAR_DEPTH, 1.0f, 0 );


	m_swapChain->Present( 0, 0 );
}

ID3D10Device* AGDX10SubSys::getDevice()
{
	return m_device; 
}



