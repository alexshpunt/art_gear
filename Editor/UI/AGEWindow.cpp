#include "AGEWindow.h"

#include <QDebug>
#include <DxErr.h>
#include <QResizeEvent>

#include <vector>
#include <math.h>
#include <windows.h>

#include "Managers/AGInputManager.h"
#include "Graphics/Subsystems/DirectX10/Objects/AGDX10BoundingBox.h"
#include "Graphics/Subsystems/DirectX10/Objects/AGDX10Camera.h"
#include "Graphics/Subsystems/DirectX10/Objects/AGDX10Scene.h"
#include "Graphics/Subsystems/DirectX10/Objects/AGDX10Mesh.h"
#include "Managers/AGLogger.h"

using namespace std;

AGEWindow::AGEWindow()
{
	m_scene = nullptr;
	setMinimumSize( 800, 600 );
	setAttribute( Qt::WA_PaintOnScreen );
	setAttribute( Qt::WA_NativeWindow );
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
	swapChainDesc.OutputWindow = (HWND)winId(); 
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
	hr = m_swapChain->GetBuffer( 0, __uuidof( backBuffer ), ( LPVOID* )&backBuffer );

	if( FAILED( hr ) )
	{
		AGError() << "Cannot get buffer from swap chain for back buffer, error: " << DXGetErrorDescription( hr );
		return; 
	}
	AGSucces() << "Back buffer was created";

	D3D10_TEXTURE2D_DESC descDepth; 
	descDepth.Width = 800;
	descDepth.Height = 600;
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
	AGSucces() << "Render target view was created";

	m_device->OMSetRenderTargets( 1, &m_renderTargetView, m_depthStencilView );

	D3D10_VIEWPORT viewport; 
	viewport.Height = 800;
	viewport.Width = 600; 
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.MaxDepth = 1.0f;
	viewport.MinDepth = 0.0f; 
	m_device->RSSetViewports( 1, &viewport ); 
	AGSucces() << "DX10SubSystem was initialized";

	m_mesh = new AGDX10Mesh; 
	m_mesh->loadFrom( "data/meshes/irish.agmsh", m_device );
}

AGEWindow::~AGEWindow()
{

}

void AGEWindow::resizeEvent(QResizeEvent* event)
{
	m_renderTargetView->Release();
	m_depthBuffer->Release();
	m_depthStencilView->Release();

	m_swapChain->ResizeBuffers( 2, event->size().width(), event->size().height(),
		DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH );

	ID3D10Texture2D* backBuffer; 
	HRESULT hr = m_swapChain->GetBuffer( 0, __uuidof( backBuffer ), ( LPVOID* )&backBuffer );

	if( FAILED( hr ) )
	{
		AGError() << "Cannot get buffer from swap chain for back buffer, error: " << DXGetErrorDescription( hr );
		return; 
	}
	AGSucces() << "Back buffer was created";

	hr = m_device->CreateRenderTargetView( backBuffer, NULL, &m_renderTargetView );
	backBuffer->Release(); 
	
	D3D10_TEXTURE2D_DESC descDepth; 
	descDepth.Width = event->size().width();
	descDepth.Height = event->size().height();
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
	viewPort.Width = event->size().width();
	viewPort.Height = event->size().height();
	viewPort.MaxDepth = 1.0f;
	viewPort.MinDepth = 0.0f;
	viewPort.TopLeftX = 0;
	viewPort.TopLeftY = 0;

	m_device->RSSetViewports( 1, &viewPort );

	m_device->OMSetRenderTargets( 1, &m_renderTargetView, m_depthStencilView );

	if( m_scene )
	{
		vector< AGDX10Camera* > cameras = m_scene->getCameras(); 
		QSize size = event->size(); 
		float aspectRatio = size.width() / size.height(); 
		for( AGDX10Camera* camera : cameras )
		{
			camera->setAspectRatio( aspectRatio );
		}
	}
}

void AGEWindow::setScene( AGDX10Scene* scene )
{
	m_scene = scene; 
	m_scene->draw( m_device );
}

void AGEWindow::paintEvent(QPaintEvent* event)
{
	if( !m_device ) 
		return; 

	float clearColor[ 4 ] = { 0.22f, 0.22f, 0.22f, 1.0f };
	m_device->ClearRenderTargetView( m_renderTargetView, clearColor );
	m_device->ClearDepthStencilView( m_depthStencilView, D3D10_CLEAR_DEPTH, 1.0f, 0 );

	if( m_scene )
		m_scene->draw( m_device );

	m_swapChain->Present( 0, 0 );
}

QPaintEngine* AGEWindow::paintEngine() const
{
	return nullptr;
}

bool AGEWindow::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
	MSG* msg = (MSG*)message; 
	int key = ( int )msg->wParam; 
	switch( msg->message )
	{
		case WM_LBUTTONDOWN:
			AGInput().setButtonPressed( "LMB", true );
			mouseClickEvent( "LMB" ); 
		break;
		case WM_LBUTTONUP: 
			AGInput().setButtonPressed( "LMB", false );
		break;
		case WM_LBUTTONDBLCLK:

		break;
		case WM_RBUTTONDOWN:
			AGInput().setButtonPressed( "RMB", true );
			mouseClickEvent( "RMB" ); 
		break;
		case WM_RBUTTONUP:
			AGInput().setButtonPressed( "RMB", false );
		break;
		case WM_RBUTTONDBLCLK:

		break;
		case WM_MBUTTONDOWN:
			AGInput().setButtonPressed( "MMB", true );
			mouseClickEvent( "MMB" ); 
		break;
		case WM_MBUTTONUP:
			AGInput().setButtonPressed( "MMB", false );
		break;
		case WM_MBUTTONDBLCLK:

		break; 
		case WM_MOUSEMOVE:
			AGPoint2 mousePos;
			POINT point; 
			GetCursorPos( &point );
			ScreenToClient( (HWND)winId(), &point );
			mousePos.x = point.x;
			mousePos.y = point.y; 
			AGInput().setMousePos( mousePos );
		break;
	}
	return false; 
}

ID3D10Device* AGEWindow::getDevice() const
{
	return m_device; 
}

void AGEWindow::mouseClickEvent( QString btn )
{
	if( !m_scene || btn != "LMB" )
		return; 

	AGPoint2 mousePos = AGInput().getMousePos(); 
	QSize winSize = size(); 
	AGDX10Camera* camera = m_scene->getTopCamera(); 
	D3DXMATRIX matProj = camera->getProjMatrix(); 

	D3DXVECTOR3 v; 
	v.x =  ( ( ( 2.0f * mousePos.x ) / winSize.width() ) - 1 ) / matProj._11;
	v.y = -( ( ( 2.0f * mousePos.y ) / winSize.height() ) - 1 ) / matProj._22;  
	v.z = 1.0f; 

	D3DXMATRIX mat; 
	D3DXMATRIX matView = camera->getViewMatrix(); 
	D3DXVECTOR3 rayOrigin, rayDir; 

	D3DXMatrixInverse( &mat, NULL, &matView );

	rayDir.x = v.x * mat._11 + v.y * mat._21 + v.z * mat._31; 
	rayDir.y = v.x * mat._12 + v.y * mat._22 + v.z * mat._32; 
	rayDir.z = v.x * mat._13 + v.y * mat._23 + v.z * mat._33; 

	rayOrigin.x = mat._41;
	rayOrigin.y = mat._42;
	rayOrigin.z = mat._43; 

	D3DXMATRIX matInverce;

	vector< AGDX10Mesh* > meshes = m_scene->getMeshes(); 

	float minDist = -1.0f; 
	AGDX10Mesh* nearestMesh = nullptr; 

	for( AGDX10Mesh* mesh : meshes )
	{
		D3DXMATRIX matWorld = mesh->getWorldMatrix(); 
		D3DXMatrixInverse( &matInverce, NULL, &matWorld );

		D3DXVECTOR3 rayObjOrigin, rayObjDir; 

		D3DXVec3TransformCoord( &rayObjOrigin, &rayOrigin, &matInverce );
		D3DXVec3TransformCoord( &rayObjDir, &rayDir, &matInverce );

		D3DXVec3Normalize( &rayObjDir, &rayObjDir );

		float dist = mesh->intersect( rayObjOrigin, rayObjDir );
		mesh->setSelected( false );
		if( dist > 0 )
		{
			if( minDist < 0 )
			{
				minDist = dist; 
				nearestMesh = mesh; 
			}
			else 
			{
				minDist = min( minDist, dist );
				nearestMesh = mesh; 
			}
		}
	}
	AGDebug() << minDist << nearestMesh;
	if( nearestMesh )
	{
		nearestMesh->setSelected( true );
	}
	
}







