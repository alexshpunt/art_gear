#include "AGGraphics.h"

#include <d3dx10.h>
#include <d3d10.h>

#include "Managers/AGDXDebugDraw.h"
#include "Objects/AGDXMesh.h"
#include "Objects/AGDXCamera.h"
#include "Objects/Manipulators/Dragger/AGDXDragger.h"
#include "Objects/Manipulators/Rotater/AGDXRotater.h"
#include "Objects/Manipulators/Scaler/AGDXScaler.h"
#include "Objects/AGObject.h"
#include "Components/AGRenderer.h"
#include "Interfaces/AGSurface.h"
#include "Managers/AGLogger.h"
#include "Managers/AGGraphicsSettings.h"

void AGGraphics::init()
{
	m_mode = DirectX; 
	m_dragger = nullptr; 
	m_rotater = nullptr; 
	m_scaler = nullptr; 
}

void AGGraphics::update()
{
	m_toolBarState = AGStateManager::getInstance().getToolBarState(); 
	for( AGDXSurface* surface : m_surfaces )
	{
		float color[ 4 ] = { m_backgroundColor.x, m_backgroundColor.y, m_backgroundColor.z, 1.0f };
		surface->getDevice()->ClearRenderTargetView( surface->getRenderTargetView(), color );
		surface->getDevice()->ClearDepthStencilView( surface->getDepthStencilView(), D3D10_CLEAR_DEPTH, 1.0f, 0 );

		if( AGInput().isButtonDown( "MMB" ) )
		{
			AGSize winSize = AGGraphicsSettings::getInstance().getSize();  
			AGPoint2 mousePos( winSize.getWidth() / 2.0f, winSize.getHeight() / 2.0f ); 
			AGDXCamera* camera = getTopCamera(); 
			if( !camera )
			{
				return; 
			}
			D3DXMATRIX matProj = camera->getProjMatrix(); 

			D3DXVECTOR3 v; 
			v.x =  ( ( ( 2.0f * mousePos.x ) / winSize.getWidth() ) - 1 ) / matProj._11;
			v.y = -( ( ( 2.0f * mousePos.y ) / winSize.getHeight() ) - 1 ) / matProj._22;  
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

			float minDist = -1.0f; 
			AGRenderer* nearestObj = nullptr; 

			for( AGRenderer* renderer : m_renderers )
			{
				AGDXMesh* mesh = renderer->getMesh();
				D3DXMATRIX matWorld;
				if( !mesh )
				{
					D3DXMatrixIdentity( &matWorld );
				}
				else
				{
					matWorld = mesh->getLocalMatrix(); //Локальные координаты модели
				}
				AGObject* obj = renderer->getObject(); 
				AGVec3 pos = obj->getPos(); 
				D3DXMatrixTranslation( &matWorld, pos.x, pos.y, pos.z );

				D3DXMatrixInverse( &matInverce, NULL, &matWorld );

				D3DXVECTOR3 rayObjOrigin, rayObjDir; 

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
			}
		}
		surface->getCamera()->update();

		for( AGRenderer* renderer : m_renderers )
		{
			renderer->draw( surface );
		}

		if( m_dragger && m_toolBarState == AGStateManager::Dragger )
		{
			m_dragger->draw( surface );
		}
		if( m_rotater && m_toolBarState == AGStateManager::Rotater )
		{
			m_rotater->draw( surface );
		}
		if( m_scaler && m_toolBarState == AGStateManager::Scaler )
		{
			m_scaler->draw( surface );
		}
		surface->getSwapChain()->Present( 0, 0 );
	}
}

void AGGraphics::setMode(Modes mode)
{
}

AGGraphics::Modes AGGraphics::getMode() const
{
	return m_mode;
}

void AGGraphics::addSurface(AGDXSurface* surface)
{
	m_surfaces.push_back( surface );
	if( !m_dragger )
	{
		m_dragger = new AGDXDragger( surface->getDevice() );
	}
	if( !m_rotater )
	{
		m_rotater = new AGDXRotater( surface->getDevice() );
	}
	if( !m_scaler )
	{
		m_scaler = new AGDXScaler( surface->getDevice() );
	}
	AGDXDebugDraw::getInstance().initialize( surface->getDevice() );
}

void AGGraphics::removeSurface(AGDXSurface* surface)
{
	list< AGDXSurface* >::iterator iter = m_surfaces.begin(); 
	for( iter; iter != m_surfaces.end(); iter++ )
	{
		if( *iter == surface )
		{
			m_surfaces.erase( iter );
			return;
		}
	}
}

const list< AGDXSurface* >& AGGraphics::getSurfaces() const
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

void AGGraphics::addSelectedObject(AGObject* object)
{
	m_selectedObject.push_front( object );
}

void AGGraphics::removeSelectedObject(AGObject* object)
{
	list< AGObject* >::iterator iter = m_selectedObject.begin();

	for( iter; iter != m_selectedObject.end(); iter++ )
	{
		if( *iter == object )
		{
			m_selectedObject.erase( iter ); 
			return; 
		}
	}
}

void AGGraphics::mouseClickEvent( MouseButton btn )
{
	if( m_dragger )
	{
		for( AGDXSurface* surface : m_surfaces )
		{
			m_dragger->mouseClickEvent( btn, surface ); 	
		}
	}
	if( m_rotater )
	{
		for( AGDXSurface* surface : m_surfaces )
		{
			m_rotater->mouseClickEvent( btn, surface ); 	
		}
	}
	if( m_scaler )
	{
		for( AGDXSurface* surface : m_surfaces )
		{
			m_scaler->mouseClickEvent( btn, surface ); 	
		}
	}

	if( btn != MouseButton::LMB )
		return; 

	AGPoint2 mousePos = AGInput().getMousePos(); 
	AGSize winSize = AGGraphicsSettings::getInstance().getSize();  
	AGDXCamera* camera = getTopCamera(); 
	if( !camera )
	{
		return; 
	}
	D3DXMATRIX matProj = camera->getProjMatrix(); 

	D3DXVECTOR3 v; 
	v.x =  ( ( ( 2.0f * mousePos.x ) / winSize.getWidth() ) - 1 ) / matProj._11;
	v.y = -( ( ( 2.0f * mousePos.y ) / winSize.getHeight() ) - 1 ) / matProj._22;  
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

	float minDist = -1.0f; 
	AGRenderer* nearestObj = nullptr; 

	for( AGRenderer* renderer : m_renderers )
	{
		AGDXMesh* mesh = renderer->getMesh();
		D3DXMATRIX matWorld;
		if( !mesh )
		{
			D3DXMatrixIdentity( &matWorld );
		}
		else
		{
			matWorld = mesh->getLocalMatrix(); //Локальные координаты модели
		}
		AGObject* obj = renderer->getObject(); 
		AGVec3 pos = obj->getPos(); 
		D3DXMatrixTranslation( &matWorld, pos.x, pos.y, pos.z );

		D3DXMatrixInverse( &matInverce, NULL, &matWorld );

		D3DXVECTOR3 rayObjOrigin, rayObjDir; 

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
		nearestObj->setSelected( true );
		if( m_dragger && m_rotater && m_scaler )
		{
			m_dragger->setObject( nearestObj->getObject() );
			m_rotater->setObject( nearestObj->getObject() );
			m_scaler->setObject( nearestObj->getObject() );
		}
	}	
}

void AGGraphics::mouseMoveEvent()
{
	if( m_dragger && m_toolBarState == AGStateManager::Dragger )
	{
		for( AGDXSurface* surface : m_surfaces )
		{
			m_dragger->mouseMoveEvent( surface ); 	
		}
	}
	if( m_rotater && m_toolBarState == AGStateManager::Rotater )
	{
		for( AGDXSurface* surface : m_surfaces )
		{
			m_rotater->mouseMoveEvent( surface ); 	
		}
	}
	if( m_scaler && m_toolBarState == AGStateManager::Scaler )
	{
		for( AGDXSurface* surface : m_surfaces )
		{
			m_scaler->mouseMoveEvent( surface ); 	
		}
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

AGDXCamera* AGGraphics::createCamera()
{
	AGDXCamera* camera = new AGDXCamera; 
	m_cameras.push_back( camera );
	return camera; 
}

void AGGraphics::removeCamera(AGDXCamera* camera)
{

}

AGDXCamera* AGGraphics::getTopCamera() const
{
	int layer = m_cameras[ 0 ]->getLayer();
	AGDXCamera* topCamera = m_cameras[ 0 ];

	for( AGDXCamera* camera : m_cameras )
	{
		if( camera->getLayer() > layer )
		{
			topCamera = camera;
			layer = camera->getLayer();
		}
	} 
	return topCamera; 
}

vector< AGDXCamera* > AGGraphics::getCameras() const
{
	return m_cameras; 
}


