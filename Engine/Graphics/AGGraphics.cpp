#include "AGGraphics.h"

#include "AGEngine.h"

#include "Engine/Graphics/Objects/AGManipulator.h"
#include "Engine/Graphics/Objects/AGMesh.h"
#include "Engine/Graphics/Objects/AGCamera.h"

#include "Engine/Objects/AGGameScene.h"
#include "Engine/Objects/AGGameObject.h"

#include "Engine/Graphics/Components/AGRenderer.h"

#include "Engine/Graphics/Interfaces/AGPureInterfaces.h"
#include "Engine/Graphics/Interfaces/AGSurface.h"

#include "Engine/Managers/AGLogger.h"
#include "Engine/Managers/AGGraphicsSettings.h"

#include "Managers/AGDebugManager.h"

void AGGraphics::init()
{
	m_console = nullptr;
	m_device = nullptr; 
	m_focusSurface = nullptr; 
	m_fps = 0; 
}

void AGGraphics::update()
{
	m_toolBarState = AGEStateManager::getInstance().getToolBarState(); 

	for( AGSurface* surface : m_surfaces )
	{
		if( m_focusSurface && m_focusSurface->isMaximizedMode() && surface != m_focusSurface )
		{
			continue;
		}

		surface->clearRenderTargets();
		surface->setRenderTargets();

		if( surface == m_focusSurface )
		{
			surface->getCamera()->update(); 
		} 

		if( AGInput().isButtonDown( "MMB" ) && surface == m_focusSurface )
		{
			//Deprecated for now
			/*AGSize winSize = AGGraphicsSettings::getInstance().getSize();  
			AGPoint2 mousePos( winSize.getWidth() / 2.0f, winSize.getHeight() / 2.0f ); 
			AGCamera* camera = getTopCamera(); 
			if( !camera )
			{
				return; 
			}
			AGMatrixmatProj = camera->getProjMatrix(); 

			AGVec3 v; 
			v.x =  ( ( ( 2.0f * mousePos.x ) / winSize.getWidth() ) - 1 ) / matProj._11;
			v.y = -( ( ( 2.0f * mousePos.y ) / winSize.getHeight() ) - 1 ) / matProj._22;  
			v.z = 1.0f; 

			AGMatrixmat; 
			AGMatrixmatView = camera->getViewMatrix(); 
			AGVec3 rayOrigin, rayDir; 

			D3DXMatrixInverse( &mat, NULL, &matView );

			rayDir.x = v.x * mat._11 + v.y * mat._21 + v.z * mat._31; 
			rayDir.y = v.x * mat._12 + v.y * mat._22 + v.z * mat._32; 
			rayDir.z = v.x * mat._13 + v.y * mat._23 + v.z * mat._33; 

			rayOrigin.x = mat._41;
			rayOrigin.y = mat._42;
			rayOrigin.z = mat._43; 

			AGMatrixmatInverce;

			float minDist = -1.0f; 
			AGRenderer* nearestObj = nullptr; 

			for( AGRenderer* renderer : m_renderers )
			{
				AGMesh* mesh = renderer->getMesh();
				AGMatrixmatWorld;
				if( !mesh )
				{
					D3DXMatrixIdentity( &matWorld );
				}
				else
				{
					matWorld = mesh->getLocalMatrix(); //Локальные координаты модели
				}
				AGGameObject* obj = renderer->getObject(); 
				AGVec3 pos = obj->getLocalPos(); 
				D3DXMatrixTranslation( &matWorld, pos.x, pos.y, pos.z );

				D3DXMatrixInverse( &matInverce, NULL, &matWorld );

				AGVec3 rayObjOrigin, rayObjDir; 

				D3DXVec3TransformCoord( &rayObjOrigin, &rayOrigin, &matInverce );
				D3DXVec3TransformNormal( &rayObjDir, &rayDir, &matInverce );

				D3DXVec3Normalize( &rayObjDir, &rayObjDir );

				float dist = renderer->intersect( rayObjOrigin, rayObjDir );
				renderer->setSelected( false );
				if( dist > 0 )
				{
					if( minDist < 0 || minDist > dist )
					{
						minDist = dist; 
						nearestObj = renderer;
					}
				}
			}

			if( nearestObj )
			{
				surface->getCamera()->setTargetDistance( minDist );
			}*/
		}

		for( AGRenderer* renderer : m_renderers )
		{
			renderer->draw( surface );
		}

		for( AGDrawable* drawable : m_drawables )
		{
			drawable->draw( surface );
		}

		for( AGClickable* clickable : m_clickableObjects )
		{
			clickable->draw( surface ); 
		}

		surface->present(); 

		surface->getDevice()->RSSetState( m_rasterizeStates[ surface->getDevice() ]->solid ); 
				
		for( AGManipulator* manipulator : m_manipulators )
		{
			manipulator->draw( surface );
		}
		
		if( surface == m_focusSurface )
			AGDebugManager::getInstance().drawText( AGRect( 0, 0, 100, 100 ), wstring( L"FPS: " ) + to_wstring( m_fps ), surface );

		surface->getDevice()->OMSetDepthStencilState( m_depthState.at( surface->getId() ), 0 );

		if( m_console && AGEStateManager::getInstance().isConsoleMode() )
		{
			m_console->draw( surface );
		}

		surface->swapChainPresent();
	}
}

void AGGraphics::addSurface(AGSurface* surface)
{
	m_surfaces.push_back( surface );
	if( !m_device )
		m_device = surface->getDevice(); 

	HRESULT hr = S_OK; 

	D3D10_INPUT_ELEMENT_DESC vertexLayout[] = 
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D10_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D10_INPUT_PER_VERTEX_DATA, 0 },
		{ "BINORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 24, D3D10_INPUT_PER_VERTEX_DATA, 0 },
		{ "TANGENT",  0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 36, D3D10_INPUT_PER_VERTEX_DATA, 0 },
		{ "UV",       0, DXGI_FORMAT_R32G32_FLOAT,    0, 48, D3D10_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT vertexLayoutNum = 5; 

	D3D10_INPUT_ELEMENT_DESC colorVertexLayout[] = 
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D10_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",   0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D10_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT colorVertexLayoutNum = 2; 

	D3D10_INPUT_ELEMENT_DESC textureVertexLayout[] = 
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D10_INPUT_PER_VERTEX_DATA, 0 },
		{ "UV",   0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D10_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT textureVertexLayoutNum = 2; 

	D3D10_INPUT_ELEMENT_DESC simpleVertexLayout[] = 
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D10_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT simpleVertexLayoutNum = 1; 

	D3D10_INPUT_ELEMENT_DESC billboardVertexLayout[] = 
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D10_INPUT_PER_VERTEX_DATA, 0 },
		{ "SIZE", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12,  D3D10_INPUT_PER_VERTEX_DATA, 0 },
	};

	UINT billboardVertexLayoutNum = 2; 

	AGInputLayout* inputLayout = new AGInputLayout; 

	ID3D10Effect* dxEffect; 
	ID3D10Device* device = surface->getDevice();

	handleDXShaderError( D3DX10CreateEffectFromFile( 
		L"data/shaders/dif.fx", NULL, NULL, "fx_4_0", D3D10_SHADER_ENABLE_STRICTNESS,
		NULL, device, NULL, NULL, &dxEffect, NULL, NULL 
		) );  

	D3D10_PASS_DESC passDesc; 
	ID3D10EffectTechnique* technique = dxEffect->GetTechniqueByName( "Render" );
	handleDXError( technique->GetPassByIndex( 0 )->GetDesc( &passDesc ) );

	handleDXError( device->CreateInputLayout( vertexLayout, vertexLayoutNum, passDesc.pIAInputSignature, 
		passDesc.IAInputSignatureSize, &inputLayout->vertexInputLayout ) );
	
	dxEffect->Release(); 

	handleDXShaderError( D3DX10CreateEffectFromFile( L"data/shaders/console.fx", NULL, NULL, "fx_4_0", D3D10_SHADER_ENABLE_STRICTNESS, 
		NULL, device, NULL, NULL, &dxEffect, NULL, NULL ) ); 

	technique = dxEffect->GetTechniqueByName( "Render" );
	handleDXError( technique->GetPassByIndex( 0 )->GetDesc( &passDesc ) );

	handleDXError( device->CreateInputLayout( simpleVertexLayout, simpleVertexLayoutNum, passDesc.pIAInputSignature, 
		passDesc.IAInputSignatureSize, &inputLayout->simpleVertexInputLayout ) );

	dxEffect->Release();

	handleDXShaderError( D3DX10CreateEffectFromFile( L"data/shaders/shape.fx", NULL, NULL, "fx_4_0", D3D10_SHADER_ENABLE_STRICTNESS, 
		NULL, device, NULL, NULL, &dxEffect, NULL, NULL ) ); 

	technique = dxEffect->GetTechniqueByName( "Render" );
	handleDXError( technique->GetPassByIndex( 0 )->GetDesc( &passDesc ) );

	handleDXError( device->CreateInputLayout( colorVertexLayout, colorVertexLayoutNum, passDesc.pIAInputSignature, 
		passDesc.IAInputSignatureSize, &inputLayout->colorVertexInputLayout ) );

	dxEffect->Release();

	//TODO: Change shader to something like diffuse.fx 
	/*handleDXShaderError( D3DX10CreateEffectFromFile( L"data/shaders/deferredSimple.fx", NULL, NULL, "fx_4_0", D3D10_SHADER_ENABLE_STRICTNESS, 
		NULL, device, NULL, NULL, &dxEffect, NULL, NULL ) ); 

	technique = dxEffect->GetTechniqueByName( "Render" );
	handleDXError( technique->GetPassByIndex( 0 )->GetDesc( &passDesc ) );

	handleDXError( device->CreateInputLayout( textureVertexLayout, textureVertexLayoutNum, passDesc.pIAInputSignature, 
		passDesc.IAInputSignatureSize, &inputLayout->textureVertexInputLayout ) );

	dxEffect->Release();*/

	handleDXShaderError( D3DX10CreateEffectFromFile( L"data/shaders/billboard.fx", NULL, NULL, "fx_4_0", D3D10_SHADER_ENABLE_STRICTNESS, 
		NULL, device, NULL, NULL, &dxEffect, &blob, NULL ) ); 

	technique = dxEffect->GetTechniqueByName( "Render" );
	handleDXError( technique->GetPassByIndex( 0 )->GetDesc( &passDesc ) );

	handleDXError( device->CreateInputLayout( billboardVertexLayout, billboardVertexLayoutNum, passDesc.pIAInputSignature, 
		passDesc.IAInputSignatureSize, &inputLayout->billboardVertexInputLayout ) );

	dxEffect->Release();

	m_inputLayouts[ device ] = inputLayout; 

	D3D10_DEPTH_STENCIL_DESC dsDesc; 

	dsDesc.DepthEnable = true; 
	dsDesc.DepthFunc = D3D10_COMPARISON_LESS; 
	dsDesc.DepthWriteMask = D3D10_DEPTH_WRITE_MASK_ALL; 

	dsDesc.StencilEnable = false;
	dsDesc.StencilReadMask = D3D10_DEFAULT_STENCIL_READ_MASK;
	dsDesc.StencilWriteMask = D3D10_DEFAULT_STENCIL_WRITE_MASK;

	// Stencil operations if pixel is front-facing
	dsDesc.FrontFace.StencilFailOp = D3D10_STENCIL_OP_KEEP;
	dsDesc.FrontFace.StencilDepthFailOp = D3D10_STENCIL_OP_INCR;
	dsDesc.FrontFace.StencilPassOp = D3D10_STENCIL_OP_KEEP;
	dsDesc.FrontFace.StencilFunc = D3D10_COMPARISON_ALWAYS;

	// Stencil operations if pixel is back-facing
	dsDesc.BackFace.StencilFailOp = D3D10_STENCIL_OP_KEEP;
	dsDesc.BackFace.StencilDepthFailOp = D3D10_STENCIL_OP_DECR;
	dsDesc.BackFace.StencilPassOp = D3D10_STENCIL_OP_KEEP;
	dsDesc.BackFace.StencilFunc = D3D10_COMPARISON_ALWAYS;

	ID3D10DepthStencilState* state; 

	handleDXError( device->CreateDepthStencilState( &dsDesc, &state ) );
	
	m_depthState.push_back( state ); 
}

void AGGraphics::removeSurface(AGSurface* surface)
{
	list< AGSurface* >::iterator iter = m_surfaces.begin(); 
	for( iter; iter != m_surfaces.end(); iter++ )
	{
		if( *iter == surface )
		{
			m_surfaces.erase( iter );
			return;
		}
	}
}

const list< AGSurface* >& AGGraphics::getSurfaces() const
{
	return m_surfaces;
}

void AGGraphics::setBackgroundColor(const AGPoint3& color)
{
	m_backgroundColor = color; 
}

void AGGraphics::setBackgroundColor(float r, float g, float b)
{
	m_backgroundColor = AGPoint3( r, g , b );
}

const AGPoint3& AGGraphics::getBackgroundColor() const
{
	return m_backgroundColor;
}

void AGGraphics::addSelectedObject(AGGameObject* object)
{
	m_selectedObject.push_front( object );
}

void AGGraphics::removeSelectedObject(AGGameObject* object)
{
	list< AGGameObject* >::iterator iter = m_selectedObject.begin();

	for( iter; iter != m_selectedObject.end(); iter++ )
	{
		if( *iter == object )
		{
			m_selectedObject.erase( iter ); 
			return; 
		}
	}
}

void AGGraphics::mouseClickEvent( AGMouseButton btn )
{
	if( !m_focusSurface )
		return; 

	for( AGClickable* clickable : m_clickableObjects )
	{
		if( clickable->mouseClickEvent( btn, m_focusSurface ) )
		{
			return; 
		}
	}

	for( AGManipulator* manipulator : m_manipulators )
	{
		if( manipulator->mouseClickEvent( btn, m_focusSurface ) )
		{
			return; 
		}
	}

	if( btn != AGMouseButton::LMB )
		return; 

	AGPoint2 mousePos = AGInput().getMousePos(); 
	AGSize winSize = m_focusSurface->getSize();  
	AGCamera* camera = m_focusSurface->getCamera();
	assert( camera );

	AGMatrix matProj = camera->getProjMatrix(); 
	AGMatrix matView = camera->getViewMatrix(); 

	float minDist = -1.0f; 
	AGRenderer* nearestObj = nullptr; 

	D3D10_VIEWPORT viewport; 
	viewport.Height = winSize.getHeight();
	viewport.Width = winSize.getWidth();
	viewport.MaxDepth = 1.0f; 
	viewport.MinDepth = 0.0f;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0; 

	AGVec3 nearPoint( mousePos.x, mousePos.y, 0.0f );
	AGVec3 farPoint( mousePos.x, mousePos.y, 1.0f );

	for( AGRenderer* renderer : m_renderers )
	{
		AGMesh* mesh = renderer->getMesh();
		AGMatrix matWorld;
		if( mesh )
		{
			matWorld = mesh->getResultMatrix(); //Локальные координаты модели
		}
		AGGameObject* obj = renderer->getObject(); 

		AGVec3 np = AGVec3::unproject( nearPoint, AGRect( 0, 0, winSize.getWidth(), winSize.getHeight() ), matWorld, matView, matProj ); 
		AGVec3 fp = AGVec3::unproject( farPoint, AGRect( 0, 0, winSize.getWidth(), winSize.getHeight() ), matWorld, matView, matProj ); 

		AGVec3 dir = (fp - np); 
		
		float dist = renderer->intersect( np, dir );
		renderer->setSelected( false );
		if( dist > 0 )
		{
			if( minDist < 0 || minDist > dist )
			{
				minDist = dist; 
				nearestObj = renderer;
			}
		}
	}

	if( nearestObj )
	{
		nearestObj->setSelected( true );
	}

	if( AGGameScene* scene = AGEngine::getInstance().getScene() )
	{
		scene->selectObject( nearestObj ? nearestObj->getObject() : nullptr );
	}

	for( AGManipulator* manipulator : m_manipulators )
	{
		manipulator->setObject( nearestObj ? nearestObj->getObject() : nullptr );
	}
}


void AGGraphics::mouseReleaseEvent(AGMouseButton btn)
{
	for( AGClickable* clickable : m_clickableObjects )
	{
		clickable->mouseReleaseEvent( btn ); 
	}
	for( AGManipulator* manipulator : m_manipulators )
	{
		manipulator->mouseReleaseEvent( btn );
	}
}

void AGGraphics::mouseMoveEvent()
{
	if( !m_focusSurface )
		return; 

	for( AGClickable* clickable : m_clickableObjects )
	{
		clickable->mouseMoveEvent( m_focusSurface );
	}

	for( AGManipulator* manipulator : m_manipulators )
	{
		manipulator->mouseMoveEvent( m_focusSurface );
	}
}

void AGGraphics::addRenderer(AGRenderer* renderer)
{
	m_renderers.push_back( renderer );
}

void AGGraphics::removeRenderer(AGRenderer* renderer)
{

}

vector< AGRenderer* > AGGraphics::getRenderers() const
{
	return m_renderers; 
}

AGCamera* AGGraphics::createCamera()
{
	AGCamera* camera = new AGCamera; 
	m_cameras.push_back( camera );
	return camera; 
}

void AGGraphics::removeCamera(AGCamera* camera)
{

}

AGCamera* AGGraphics::getTopCamera() const
{
	AGCamera* topCamera = m_cameras[ 0 ];
	return topCamera; 
}

vector< AGCamera* > AGGraphics::getCameras() const
{
	return m_cameras; 
}

void AGGraphics::addClickableObject(AGClickable* object)
{
	m_clickableObjects.push_back( object );
}

void AGGraphics::removeClickableObject(AGClickable* object)
{
	for( list< AGClickable* >::iterator iter = m_clickableObjects.begin(); iter != m_clickableObjects.end(); iter++ )
	{
		if( (*iter) == object )
		{
			m_clickableObjects.erase( iter );
			return; 
		}
	}
}

void AGGraphics::addManipulator(AGManipulator* manipulator)
{
	m_manipulators.push_back( manipulator );
}

void AGGraphics::removeManipulator(AGManipulator* manipulator)
{
	for( list< AGManipulator* >::iterator iter = m_manipulators.begin(); iter != m_manipulators.end(); iter++ )
	{
		if( (*iter) == manipulator )
		{
			m_manipulators.erase( iter );
			return; 
		}
	}
}

IDXGIFactory* AGGraphics::getDXGIFactory() const
{
	return m_dxgiFactory; 
}

ID3D10Device* AGGraphics::getDevice() const
{
	return m_device; 
}

AGInputLayout* AGGraphics::getInputLayout(ID3D10Device* device )
{
	map< ID3D10Device*, AGInputLayout* >::iterator iter = m_inputLayouts.find( device ); 
	if( iter == m_inputLayouts.end() )
		return nullptr; 
	
	return iter->second; 
}

void AGGraphics::setFocusSurface(AGSurface* surface)
{
	m_focusSurface = surface; 
}

void AGGraphics::keyDownEvent(int keyCode)
{
	if( !m_focusSurface )
		return; 

}

void AGGraphics::keyUpEvent(int keyCode)
{
	if( !m_focusSurface )
		return; 

}

void AGGraphics::mouseWheelMove(int wheelDelta)
{
	if( !m_focusSurface )
		return; 

}

void AGGraphics::createRasterizeStates()
{
	D3D10_RASTERIZER_DESC desc; 

	desc.AntialiasedLineEnable = true;
	desc.CullMode = D3D10_CULL_BACK; 
	desc.DepthClipEnable = true; 
	desc.FrontCounterClockwise = false;
	desc.MultisampleEnable = false;
	desc.ScissorEnable = false;
	

	for( AGSurface* surface : m_surfaces )
	{
		AGRasterizeState* rastState = new AGRasterizeState; 
		desc.DepthBias = -1;
		desc.DepthBiasClamp = -0.01f;
		desc.SlopeScaledDepthBias = -0.01f; 
		desc.FillMode = D3D10_FILL_WIREFRAME; 
		surface->getDevice()->CreateRasterizerState( &desc, &rastState->wireframe );
		desc.DepthBias = 1;
		desc.DepthBiasClamp = 0.0f;
		desc.SlopeScaledDepthBias = 0.0f; 
		desc.FillMode = D3D10_FILL_SOLID; 
		surface->getDevice()->CreateRasterizerState( &desc, &rastState->solid );

		m_rasterizeStates[ surface->getDevice() ] = rastState; 
	}
}

AGRasterizeState* AGGraphics::getRasterizeState(ID3D10Device* device)
{
	return m_rasterizeStates.at( device ); 
}

void AGGraphics::switchTo(AGVertexType type)
{
	for( AGSurface* surface : m_surfaces )
	{
		if( type == ColorVertex )
		{
			for( auto iter : m_inputLayouts )
			{
				AGInputLayout* ip = iter.second; 
				surface->getDevice()->IASetInputLayout( ip->colorVertexInputLayout );
			}	
		}
		else if( type == SimpleVertex )
		{
			for( auto iter : m_inputLayouts )
			{
				AGInputLayout* ip = iter.second; 
				surface->getDevice()->IASetInputLayout( ip->simpleVertexInputLayout );
			}	
		}
		else if( type == TextureVertex )
		{
			for( auto iter : m_inputLayouts )
			{
				AGInputLayout* ip = iter.second; 
				surface->getDevice()->IASetInputLayout( ip->textureVertexInputLayout );
			}	
		}
		else if( type == Vertex )
		{
			for( auto iter : m_inputLayouts )
			{
				AGInputLayout* ip = iter.second; 
				surface->getDevice()->IASetInputLayout( ip->vertexInputLayout );
			}	
		}
	}
}

void AGGraphics::addLight(AGLight* light)
{
	m_lights.push_back( light );
}

void AGGraphics::removeLight( AGLight* light )
{
	m_lights.remove( light );
}

list< AGLight* > AGGraphics::getLights() const
{
	return m_lights; 
}

unsigned int AGGraphics::getCurrentSurfaceID()
{
	return m_surfaces.size();  
}

void AGGraphics::addDrawable(AGDrawable* drawable)
{
	m_drawables.push_back( drawable );
}

void AGGraphics::setFPS(int fps)
{
	m_fps = fps; 
}



