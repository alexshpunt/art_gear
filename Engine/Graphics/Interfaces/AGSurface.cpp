#include "AGSurface.h"

#include <d3dx10.h>
#include <d3d10.h>
#include <dxgi.h>
#include <DxErr.h>

#include "Managers/AGLogger.h"
#include "Managers/AGGraphicsSettings.h"
#include "Graphics/Objects/AGCamera.h"
#include "Graphics/AGGraphics.h"


#include <Engine/Graphics/Objects/AGLight.h>

struct SurfaceVertex
{
	D3DXVECTOR3 pos;
	D3DXVECTOR2 uv; 
};

AGSurface::AGSurface()
{
	m_camera = nullptr; 
	m_surfaceCameraMode = AGSurfaceCameraMode::Perspective; 
	m_surfaceMode = AGSurfaceMode::Shaded;
	m_isMaximized = false; 
	setCamera( AGGraphics::getInstance().createCamera() );
}

AGSurface::~AGSurface()
{

}

void AGSurface::setSurfaceMode(AGSurfaceMode surfaceMode)
{
	m_surfaceMode = surfaceMode; 

	m_effect->Release();

	if( m_surfaceMode == Shaded )
	{
		DWORD dwShaderFlags = D3D10_SHADER_ENABLE_STRICTNESS;
		ID3D10Blob* blob; 

		HRESULT hr = D3DX10CreateEffectFromFile( L"data/shaders/deferred.fx", NULL, NULL, "fx_4_0", dwShaderFlags, 0,
			m_device, NULL, NULL, &m_effect, &blob, NULL );
		if( FAILED( hr ) )
		{
			MessageBoxA( NULL,
				(char*)blob->GetBufferPointer(), "Error", MB_OK );
			return;
		}

		// Obtain the technique
		m_technique = m_effect->GetTechniqueByName( "Render" );
		m_diffuseVar = m_effect->GetVariableByName( "txDiffuse" )->AsShaderResource();
		m_normalVar = m_effect->GetVariableByName( "txNormal" )->AsShaderResource();
		m_posVar = m_effect->GetVariableByName( "txPos" )->AsShaderResource();
		m_glossVar = m_effect->GetVariableByName( "txGloss" )->AsShaderResource();
		m_specVar = m_effect->GetVariableByName( "txSpec" )->AsShaderResource();
		m_lightVar = m_effect->GetVariableByName( "light" );
		m_camPosVar = m_effect->GetVariableByName( "camPos" ); 
	}
	else 
	{
		DWORD dwShaderFlags = D3D10_SHADER_ENABLE_STRICTNESS;
		ID3D10Blob* blob; 

		HRESULT hr = D3DX10CreateEffectFromFile( L"data/shaders/deferredSimple.fx", NULL, NULL, "fx_4_0", dwShaderFlags, 0,
			m_device, NULL, NULL, &m_effect, &blob, NULL );
		if( FAILED( hr ) )
		{
			MessageBoxA( NULL,
				(char*)blob->GetBufferPointer(), "Error", MB_OK );
			return;
		}

		m_technique = m_effect->GetTechniqueByName( "Render" );

		m_diffuseVar = m_effect->GetVariableByName( "txDiffuse" )->AsShaderResource();
		m_posVar = m_effect->GetVariableByName( "txPos" )->AsShaderResource();
	}

}

AGSurface::AGSurfaceMode AGSurface::getSurfaceMode() const
{
	return m_surfaceMode; 
}

void AGSurface::setCameraMode(AGSurfaceCameraMode cameraMode)
{
	m_surfaceCameraMode = cameraMode; 

	if( !m_camera )
		return; 

	if( m_surfaceCameraMode == Perspective )
	{
		m_camera->setType( AGCamera::Perspective );
		return; 
	}
	else if( m_surfaceCameraMode == Orthographics )
	{
		m_camera->setType( AGCamera::Ortho );
		return;
	}

	m_camera->setType( AGCamera::Ortho ); 
	m_camera->setAt( D3DXVECTOR3( 0.0f, 0.0f, 1.0f ) );
	m_camera->setEye( D3DXVECTOR3( 0.0f, 0.0f, 0.0f ) );

	switch( m_surfaceCameraMode )
	{
		case Back:
			m_camera->rotate( 0, 180 );
		break; 
		case Front:
			m_camera->rotate( 0, 0 );
		break;
		case Left:
			m_camera->rotate( 0, 90 );
		break;
		case Right:
			m_camera->rotate( 0, -90 );
		break;
		case Top:
			m_camera->rotate( 90, 0 );
		break;
		case Bottom:
			m_camera->rotate( -90, 0 );
		break; 
	}

	m_camera->translateInDirection( -1000 ); 
	m_camera->update(); 
}

AGSurface::AGSurfaceCameraMode AGSurface::getCameraMode() const
{
	return m_surfaceCameraMode; 
}

void AGSurface::setCamera(AGCamera* camera)
{
	m_camera = camera; 
}

AGCamera* AGSurface::getCamera() const
{
	return m_camera; 
}

ID3D10Device* AGSurface::getDevice() const
{
	return m_device;
}

void AGSurface::resizeSurface(float width, float height )
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

	releaseRenderTargets();
	createRenderTargets( width, height );

	m_device->OMSetRenderTargets( 1, &m_renderTargetView, m_depthStencilView );

	AGGraphicsSettings::getInstance().setScreenWidth( width );
	AGGraphicsSettings::getInstance().setScreenHeight( height ); 

	if( m_camera )
		m_camera->setAspectRatio( width / height );

	m_size = AGSize( width, height );

	//AGGraphics::getInstance().update();
}

const AGSize& AGSurface::getSize() const
{
	return m_size; 
}

float AGSurface::getWidth() const
{
	return m_size.getWidth();
}

float AGSurface::getHeight() const
{
	return m_size.getHeight();
}

void AGSurface::setup(float width, float height, HWND hwnd)
{
	m_hwnd = hwnd; 

	HRESULT hr = S_OK; 

	UINT createDeviceFlags = 0; 
#ifdef _DEBUG
	//createDeviceFlags |= D3D10_CREATE_DEVICE_DEBUG;
#endif 

	DXGI_SWAP_CHAIN_DESC swapChainDesc; 
	ZeroMemory( &swapChainDesc, sizeof( swapChainDesc ) ); 
	swapChainDesc.BufferCount = 2; 
	swapChainDesc.BufferDesc.Height = width;
	swapChainDesc.BufferDesc.Width = height;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 0; 
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
	hr = m_device->CreateRenderTargetView( backBuffer, NULL, &m_renderTargetView );
	backBuffer->Release(); 

	SurfaceVertex vertices[] =
	{
		D3DXVECTOR3( -1.0f, 1.0f, 1.0f ), D3DXVECTOR2( 0.0f, 0.0f ), //1
		D3DXVECTOR3( 1.0f, 1.0f, 1.0f ), D3DXVECTOR2( 1.0f, 0.0f ),  //2
		D3DXVECTOR3( -1.0f, -1.0f, 1.0f ), D3DXVECTOR2( 0.0f, 1.0f ),//3

		D3DXVECTOR3( 1.0f, 1.0f, 1.0f ), D3DXVECTOR2( 1.0f, 0.0f ),  //4
		D3DXVECTOR3( 1.0f, -1.0f, 1.0f ), D3DXVECTOR2( 1.0f, 1.0f ), //5
		D3DXVECTOR3( -1.0f, -1.0f, 1.0f ), D3DXVECTOR2( 0.0f, 1.0f ),//6
	};

	D3D10_BUFFER_DESC bufferDesc;
	bufferDesc.Usage = D3D10_USAGE_DEFAULT;
	bufferDesc.ByteWidth = sizeof( vertices );
	bufferDesc.BindFlags = D3D10_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	D3D10_SUBRESOURCE_DATA initData;
	initData.pSysMem = vertices;
	m_device->CreateBuffer( &bufferDesc, &initData, &m_vertexBuffer );

	DWORD dwShaderFlags = D3D10_SHADER_ENABLE_STRICTNESS;
	ID3D10Blob* blob; 

	hr = D3DX10CreateEffectFromFile( L"data/shaders/deferred.fx", NULL, NULL, "fx_4_0", dwShaderFlags, 0,
		m_device, NULL, NULL, &m_effect, &blob, NULL );
	if( FAILED( hr ) )
	{
		MessageBoxA( NULL,
			(char*)blob->GetBufferPointer(), "Error", MB_OK );
		return;
	}

	// Obtain the technique
	m_technique = m_effect->GetTechniqueByName( "Render" );
	m_diffuseVar = m_effect->GetVariableByName( "txDiffuse" )->AsShaderResource();
	m_normalVar = m_effect->GetVariableByName( "txNormal" )->AsShaderResource();
	m_posVar = m_effect->GetVariableByName( "txPos" )->AsShaderResource();
	m_glossVar = m_effect->GetVariableByName( "txGloss" )->AsShaderResource();
	m_specVar = m_effect->GetVariableByName( "txSpec" )->AsShaderResource();
	m_lightVar = m_effect->GetVariableByName( "light" );
	m_camPosVar = m_effect->GetVariableByName( "camPos" ); 

	D3D10_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D10_INPUT_PER_VERTEX_DATA, 0 }, 

	};

	UINT numElements = sizeof( layout ) / sizeof( layout[0] );

	// Create the input layout
	D3D10_PASS_DESC passDesc;
	m_technique->GetPassByIndex( 0 )->GetDesc( &passDesc );
	hr = m_device->CreateInputLayout( layout, numElements, passDesc.pIAInputSignature, passDesc.IAInputSignatureSize, &m_vertexLayout );

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

	D3D10_VIEWPORT viewport; 
	viewport.Height = 800;
	viewport.Width = 600; 
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.MaxDepth = 1.0f;
	viewport.MinDepth = 0.0f; 
	m_device->RSSetViewports( 1, &viewport ); 

	createRenderTargets( 800, 600 );

	m_size = AGSize( width, height );

	m_id = AGGraphics::getInstance().getCurrentSurfaceID(); 
	AGGraphics::getInstance().addSurface( this );
}

void AGSurface::createRenderTargets(int width, int height)
{
	D3D10_TEXTURE2D_DESC desc;
	ZeroMemory( &desc, sizeof(desc) );
	desc.Width = width;
	desc.Height = height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	desc.SampleDesc.Count = 1;
	desc.Usage = D3D10_USAGE_DEFAULT;
	desc.BindFlags = D3D10_BIND_RENDER_TARGET | D3D10_BIND_SHADER_RESOURCE;

	ID3D10Texture2D* diffuseTexture; 
	ID3D10Texture2D* normalTexture; 
	ID3D10Texture2D* posTexture; 
	ID3D10Texture2D* glossTexture; 
	ID3D10Texture2D* specTexture; 

	m_device->CreateTexture2D( &desc, NULL, &diffuseTexture );
	m_device->CreateTexture2D( &desc, NULL, &normalTexture );
	m_device->CreateTexture2D( &desc, NULL, &posTexture );
	m_device->CreateTexture2D( &desc, NULL, &glossTexture );
	m_device->CreateTexture2D( &desc, NULL, &specTexture );

	D3D10_RENDER_TARGET_VIEW_DESC rtvDesc;
	rtvDesc.Format = desc.Format;
	rtvDesc.ViewDimension = D3D10_RTV_DIMENSION_TEXTURE2D;
	rtvDesc.Texture2D.MipSlice = 0;

	m_device->CreateRenderTargetView( diffuseTexture, &rtvDesc, &m_diffuseRTV );
	m_device->CreateRenderTargetView( normalTexture, &rtvDesc, &m_normalRTV );
	m_device->CreateRenderTargetView( posTexture, &rtvDesc, &m_posRTV );
	m_device->CreateRenderTargetView( glossTexture, &rtvDesc, &m_glossRTV );
	m_device->CreateRenderTargetView( specTexture, &rtvDesc, &m_specRTV );

	// Create the shader-resource view
	D3D10_SHADER_RESOURCE_VIEW_DESC srDesc;
	srDesc.Format = desc.Format;
	srDesc.ViewDimension = D3D10_SRV_DIMENSION_TEXTURE2D;
	srDesc.Texture2D.MostDetailedMip = 0;
	srDesc.Texture2D.MipLevels = 1;

	m_device->CreateShaderResourceView( diffuseTexture, &srDesc, &m_diffuseResource );
	m_device->CreateShaderResourceView( normalTexture, &srDesc, &m_normalResource );
	m_device->CreateShaderResourceView( posTexture, &srDesc, &m_posResource );
	m_device->CreateShaderResourceView( glossTexture, &srDesc, &m_glossResource );
	m_device->CreateShaderResourceView( specTexture, &srDesc, &m_specResource );

	diffuseTexture->Release();
	normalTexture->Release();
	posTexture->Release();
	glossTexture->Release();
	specTexture->Release();
}

void AGSurface::releaseRenderTargets()
{
	m_diffuseRTV->Release();
	m_normalRTV->Release();
	m_posRTV->Release();
	m_glossRTV->Release();
	m_specRTV->Release();

	m_diffuseResource->Release();
	m_normalResource->Release();
	m_posResource->Release();
	m_glossResource->Release();
	m_specResource->Release();
}

void AGSurface::setRenderTargets()
{
	ID3D10RenderTargetView* views[] = { m_diffuseRTV, m_normalRTV, m_posRTV, m_glossRTV, m_specRTV }; 

	m_device->OMSetRenderTargets( 5, views, m_depthStencilView );
}

void AGSurface::clearRenderTargets()
{
	AGPoint3 color = AGGraphicsSettings::getInstance().getBackgroundColor();

	float clr[4] = { color.x, color.y, color.z, 1.0f };

	m_device->ClearRenderTargetView( m_posRTV, clr );
	m_device->ClearRenderTargetView( m_renderTargetView, clr );	
	m_device->ClearRenderTargetView( m_diffuseRTV, clr );
	m_device->ClearDepthStencilView( m_depthStencilView, D3D10_CLEAR_DEPTH, 1.0f, 0);
}

void AGSurface::present()
{
	UINT stride = sizeof( SurfaceVertex );
	UINT offset = 0;
	
	m_device->OMSetRenderTargets( 1, &m_renderTargetView, NULL );
	
	m_device->IASetInputLayout( m_vertexLayout );
	m_device->IASetVertexBuffers( 0, 1, &m_vertexBuffer, &stride, &offset );
	m_device->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

	m_diffuseVar->SetResource( m_diffuseResource );
	m_posVar->SetResource( m_posResource );

	if( m_surfaceMode == Shaded )
	{
		m_normalVar->SetResource( m_normalResource );
		m_glossVar->SetResource( m_glossResource );
		m_specVar->SetResource( m_specResource );
	}

	list< AGLight* > lights = AGGraphics::getInstance().getLights(); 

	D3D10_TECHNIQUE_DESC techDesc;
	m_technique->GetDesc( &techDesc );

	if( m_surfaceMode == Shaded )
	{
		D3DXVECTOR3 camPos = m_camera->getEye(); 
		HRESULT hr = m_camPosVar->SetRawValue( &camPos, 0, sizeof( D3DXVECTOR3 ) );
		if( FAILED( hr ) )
		{
			AGDebug() << DXGetErrorDescription( hr );
		}
		for( AGLight* light : lights )
		{
			HRESULT hr = m_lightVar->SetRawValue( &light->getDesc(), 0, sizeof( AGLightDesc ) );
			if( FAILED( hr ) )
			{
				AGDebug() << DXGetErrorDescription( hr );
			}
			for( UINT p = 0; p < techDesc.Passes; ++p )
			{
				m_technique->GetPassByIndex( p )->Apply( 0 );
				m_device->Draw( 6, 0 );
			}
		}
	}
	else 
	{
		for( UINT p = 0; p < techDesc.Passes; ++p )
		{
			m_technique->GetPassByIndex( p )->Apply( 0 );
			m_device->Draw( 6, 0 );
		}
	}
}

void AGSurface::swapChainPresent()
{
	m_swapChain->Present( 0, 0 );
}

void AGSurface::setMaximizedMode(bool value)
{
	m_isMaximized = value;
}

bool AGSurface::isMaximizedMode() const
{
	return m_isMaximized; 
}

unsigned AGSurface::getId() const
{
	return m_id; 
}
