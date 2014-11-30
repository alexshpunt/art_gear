#include "AGDXScaler.h"

#include "AGDXCubeArrow.h"
#include "AGDXIntersectTriangle.h"
#include "Graphics/Objects/AGDXCamera.h"
#include "Objects/AGObject.h"
#include "Graphics/Interfaces/AGSurface.h"
#include "Managers/AGInputManager.h"
#include "Managers/AGGraphicsSettings.h"
#include "Managers/AGLogger.h"
#include "Math/AGMath.h"

AGDXScaler::AGDXScaler(ID3D10Device* device)
{
	m_xArrow = new AGDXCubeArrow( device, AGDXCubeArrow::X_AXIS );
	m_yArrow = new AGDXCubeArrow( device, AGDXCubeArrow::Y_AXIS );
	m_zArrow = new AGDXCubeArrow( device, AGDXCubeArrow::Z_AXIS );

	m_xyPlane = new AGDXIntersectTriangle( device, AGDXIntersectTriangle::XY_AXIS );
	m_xzPlane = new AGDXIntersectTriangle( device, AGDXIntersectTriangle::XZ_AXIS );
	m_yzPlane = new AGDXIntersectTriangle( device, AGDXIntersectTriangle::YZ_AXIS );
	m_xyzPlane = new AGDXIntersectTriangle( device, AGDXIntersectTriangle::XYZ_AXIS );

	m_object = nullptr; 
	m_selectedObject = nullptr;
}

AGDXScaler::~AGDXScaler()
{
	delete m_xArrow;
	delete m_yArrow;
	delete m_zArrow;

	delete m_xyPlane;
	delete m_xzPlane;
	delete m_yzPlane;
	delete m_xyzPlane; 
}

void AGDXScaler::setObject(AGObject* object)
{
	m_object = object; 
}

AGObject* AGDXScaler::getObject() const
{
	return m_object;
}

void AGDXScaler::mouseClickEvent(const string& btn, AGDXSurface* surface)
{
	if( btn != "LMB" )
		return; 

	AGPoint2 mousePos = AGInput().getMousePos(); 
	AGSize winSize = AGGraphicsSettings::getInstance().getSize();  
	AGDXCamera* camera = surface->getCamera(); 
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

	AGDXGizmo* gizmos[] = 
	{
		m_xArrow, m_yArrow, m_zArrow,
		m_xyzPlane, m_xyPlane, m_xzPlane, m_yzPlane
	};

	AGDXGizmo* closestPrimitive = nullptr; 
	float minDist = -1.0f; 

	for( int i = 0; i < 7; i++ )
	{
		D3DXMATRIX matInverce;

		AGDXGizmo* gizmo = gizmos[ i ];

		D3DXMATRIX matWorld = gizmo->getWorld();
		D3DXMatrixInverse( &matInverce, NULL, &matWorld );

		D3DXVECTOR3 rayObjOrigin, rayObjDir; 

		D3DXVec3TransformCoord( &rayObjOrigin, &rayOrigin, &matInverce );
		D3DXVec3TransformNormal( &rayObjDir, &rayDir, &matInverce );

		D3DXVec3Normalize( &rayObjDir, &rayObjDir );

		float dist = gizmo->intersect( rayObjOrigin, rayObjDir );
		gizmo->setSelected( false );
		if( dist > 0 )
		{
			if( minDist < 0 || minDist > dist )
			{
				minDist = dist;
				closestPrimitive = gizmo;
			}
		}
	}	

	if( closestPrimitive )
	{
		closestPrimitive->setSelected( true );
		if( closestPrimitive == m_xyPlane )
		{
			m_xArrow->setSelected( true );
			m_yArrow->setSelected( true );
		}
		else if( closestPrimitive == m_xzPlane )
		{
			m_xArrow->setSelected( true );
			m_zArrow->setSelected( true );
		}
		else if( closestPrimitive == m_yzPlane )
		{
			m_yArrow->setSelected( true );
			m_zArrow->setSelected( true );
		}
	}
	m_selectedObject = closestPrimitive;
}

void AGDXScaler::mouseMoveEvent(AGDXSurface* surface)
{
	AGDXGizmo* gizmos[] = 
	{
		m_xArrow, m_yArrow, m_zArrow,
		m_xyzPlane, m_xyPlane, m_xzPlane, m_yzPlane
	};
	if( AGInput().isButtonPressed( "LMB" ) && m_selectedObject )
	{
		AGPoint2 mousePos = AGInput().getMousePos(); 
		AGPoint2 point2 = mousePos + AGInput().getMouseDeltaPos();
		AGSize winSize = AGGraphicsSettings::getInstance().getSize();  
		AGDXCamera* camera = surface->getCamera();
		if( !camera )
		{
			return; 
		}
		D3DXMATRIX matProj = camera->getProjMatrix(); 

		D3DXVECTOR3 v; 
		v.x =  ( ( ( 2.0f * mousePos.x ) / winSize.getWidth() ) - 1 ) / matProj._11;
		v.y = -( ( ( 2.0f * mousePos.y ) / winSize.getHeight() ) - 1 ) / matProj._22;  
		v.z = 1.0f; 

		D3DXVECTOR3 v1; 
		v1.x =  ( ( ( 2.0f * point2.x ) / winSize.getWidth() ) - 1 ) / matProj._11;
		v1.y = -( ( ( 2.0f * point2.y ) / winSize.getHeight() ) - 1 ) / matProj._22;  
		v1.z = 1.0f; 

		D3DXMATRIX mat; 
		D3DXMATRIX matView = camera->getViewMatrix(); 
		D3DXVECTOR3 rayOrigin, rayDir; 
		D3DXVECTOR3 rayOrigin1, rayDir1;

		D3DXMatrixInverse( &mat, NULL, &matView );

		rayDir.x = v.x * mat._11 + v.y * mat._21 + v.z * mat._31; 
		rayDir.y = v.x * mat._12 + v.y * mat._22 + v.z * mat._32; 
		rayDir.z = v.x * mat._13 + v.y * mat._23 + v.z * mat._33; 

		rayOrigin.x = mat._41;
		rayOrigin.y = mat._42;
		rayOrigin.z = mat._43; 

		rayDir1.x = v1.x * mat._11 + v1.y * mat._21 + v1.z * mat._31; 
		rayDir1.y = v1.x * mat._12 + v1.y * mat._22 + v1.z * mat._32; 
		rayDir1.z = v1.x * mat._13 + v1.y * mat._23 + v1.z * mat._33; 

		rayOrigin1.x = mat._41;
		rayOrigin1.y = mat._42;
		rayOrigin1.z = mat._43; 

		D3DXVECTOR3 point3d1 = rayOrigin + rayDir;
		D3DXVECTOR3 point3d2 = rayOrigin1 + rayDir1;

		D3DXVECTOR3 vec = point3d2 - point3d1;
		D3DXVECTOR3 vec2 = vec;

		D3DXVec3Normalize( &vec, &vec );

		D3DXVECTOR3 axis = m_selectedObject->getAxis();

		D3DXVECTOR3 cameraEye = surface->getCamera()->getEye();

		for( int i = 0; i < 7; i++ )
		{
			D3DXVECTOR3 worldPos = gizmos[ i ]->getWorldPos(); 
			D3DXVECTOR3 lookDir = worldPos - cameraEye; 

			float len = D3DXVec3Length( &lookDir );
			gizmos[ i ]->translateWorldPos( D3DXVECTOR3( vec2.x * axis.x, vec2.y * axis.y, vec2.z * axis.z ) * len );
		}

		D3DXVECTOR3 worldPos = gizmos[ 0 ]->getWorldPos();

		if( m_object )
		{
			m_object->setPos( worldPos.x, worldPos.y, worldPos.z );
		}

		return;
	}

	AGPoint2 mousePos = AGInput().getMousePos(); 
	AGPoint2 dMousePos = AGInput().getMouseDeltaPos(); 
	AGSize winSize = AGGraphicsSettings::getInstance().getSize();  
	AGDXCamera* camera = surface->getCamera(); 
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

	D3DXVECTOR3 dir; 
	dir.x =  ( ( ( 2.0f * mousePos.x ) / winSize.getWidth() ) - 1 ) / matProj._11;
	dir.y = -( ( ( 2.0f * mousePos.y ) / winSize.getHeight() ) - 1 ) / matProj._22;  
	dir.z = 1.0f; 

	//AGDebug() << dir.x << " " << dir.y << " " << dir.z;

	AGDXGizmo* closestPrimitive = nullptr; 
	float minDist = -1.0f; 

	for( int i = 0; i < 7; i++ )
	{
		D3DXMATRIX matInverce;

		AGDXGizmo* gizmo = gizmos[ i ];

		D3DXMATRIX matWorld = gizmo->getWorld();
		D3DXMatrixInverse( &matInverce, NULL, &matWorld );

		D3DXVECTOR3 rayObjOrigin, rayObjDir; 

		D3DXVec3TransformCoord( &rayObjOrigin, &rayOrigin, &matInverce );
		D3DXVec3TransformNormal( &rayObjDir, &rayDir, &matInverce );

		D3DXVec3Normalize( &rayObjDir, &rayObjDir );

		float dist = gizmo->intersect( rayObjOrigin, rayObjDir );
		gizmo->setSelected( false );
		if( dist > 0 )
		{
			if( minDist < 0 || minDist > dist )
			{
				minDist = dist;
				closestPrimitive = gizmo;
			}
		}
	}	

	if( !closestPrimitive && m_selectedObject )
		closestPrimitive = m_selectedObject;

	if( closestPrimitive )
	{
		closestPrimitive->setSelected( true );
		if( closestPrimitive == m_xyPlane )
		{
			m_xArrow->setSelected( true );
			m_yArrow->setSelected( true );
		}
		else if( closestPrimitive == m_xzPlane )
		{
			m_xArrow->setSelected( true );
			m_zArrow->setSelected( true );
		}
		else if( closestPrimitive == m_yzPlane )
		{
			m_yArrow->setSelected( true );
			m_zArrow->setSelected( true );
		}
		else if( closestPrimitive == m_xyzPlane )
		{
			m_xArrow->setSelected( true );
			m_yArrow->setSelected( true );
			m_zArrow->setSelected( true );
		}
	}
}

void AGDXScaler::draw(AGDXSurface* surface)
{
	m_xArrow->draw( surface );
	m_yArrow->draw( surface );
	m_zArrow->draw( surface );

	m_xyPlane->draw( surface );
	m_xzPlane->draw( surface );
	m_yzPlane->draw( surface );
	m_xyzPlane->draw( surface );
}

float AGDXScaler::intersect(AGDXPrimitive* primitive, D3DXVECTOR3 rayOrigin, D3DXVECTOR3 rayDir)
{
	return -1.0f; 
}

