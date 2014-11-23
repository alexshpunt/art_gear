#include "AGDXRotater.h"

#include "AGDXCircle.h"
#include "Graphics/Objects/AGDXLine.h"
#include "Graphics/Objects/AGDXCamera.h"
#include "Objects/AGObject.h"
#include "Graphics/Interfaces/AGSurface.h"
#include "Managers/AGInputManager.h"
#include "Managers/AGGraphicsSettings.h"
#include "Managers/AGLogger.h"
#include "Math/AGMath.h"

AGDXRotater::AGDXRotater(ID3D10Device* device)
{
	m_xCircle = new AGDXCircle( device, AGDXCircle::X_AXIS );
	m_yCircle = new AGDXCircle( device, AGDXCircle::Y_AXIS );
	m_zCircle = new AGDXCircle( device, AGDXCircle::Z_AXIS );

	m_object = nullptr; 
	m_selectedObject = nullptr;

	m_tangentLine = new AGDXLine( device, 0.2f, D3DXVECTOR4( 0.0f, 0.0f, 0.0f, 1.0f ) );
}

AGDXRotater::~AGDXRotater()
{

}

void AGDXRotater::setObject(AGObject* object)
{
	m_object = object;
}

AGObject* AGDXRotater::getObject() const
{
	return m_object;
}

void AGDXRotater::mouseClickEvent(const string& btn, AGDXSurface* surface)
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
		m_xCircle, m_yCircle, m_zCircle
	};

	AGDXGizmo* closestPrimitive = nullptr; 
	float minDist = -1.0f; 

	for( int i = 0; i < 3; i++ )
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
	}
	m_selectedObject = closestPrimitive;
}

void AGDXRotater::mouseMoveEvent(AGDXSurface* surface)
{
	AGDXGizmo* gizmos[] = 
	{
		m_xCircle, m_yCircle, m_zCircle,
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

		//AGDXIntersectedTriangle triangle = m_selectedObject->getIntersectedTriangle( rayOrigin, rayDir );

		/*D3DXVECTOR3 tangent = maxCoords - minCoords; 

		m_tangentLine->setAngle( m_selectedObject->getAngle() );
		m_tangentLine->setPos( triangle.v1 );*/

		float dist = m_selectedObject->intersect( rayOrigin, rayDir );
		AGDebug() << dist; 

		//AGDebug() << "Triangle v1: " << triangle.v1.x << " " << triangle.v1.y << " " << triangle.v1.z; 
		/*AGDebug() << "Triangle v2: " << triangle.v2.x << " " << triangle.v2.y << " " << triangle.v2.z; 
		AGDebug() << "Triangle v3: " << triangle.v3.x << " " << triangle.v3.y << " " << triangle.v3.z; 
		AGDebug() << "Min coords: " << minCoords.x << " " << minCoords.y << " " << minCoords.z; 
		AGDebug() << "Max coords: " << maxCoords.x << " " << maxCoords.y << " " << maxCoords.z; */

		D3DXVECTOR3 axis;

		D3DXVECTOR3 cameraEye = surface->getCamera()->getEye();

		/*for( int i = 0; i < 3; i++ )
		{
			D3DXVECTOR3 worldPos = gizmos[ i ]->getWorldPos(); 
			D3DXVECTOR3 lookDir = worldPos - cameraEye; 

			float len = D3DXVec3Length( &lookDir );
			gizmos[ i ]->translateWorldPos( D3DXVECTOR3( vec2.x * axis.x, vec2.y * axis.y, vec2.z * axis.z ) * len );
		}

		D3DXVECTOR3 worldPos = gizmos[ 0 ]->getWorldPos();*/

		if( m_object )
		{
			float cosA = D3DXVec3Dot( &vec, &axis );
			//m_object->rotate( vec2.x * axis.x, vec2.y * axis.y, vec2.z * axis.z );
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

	AGDXGizmo* closestPrimitive = nullptr; 
	float minDist = -1.0f; 

	for( int i = 0; i < 3; i++ )
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

				AGDXIntersectedTriangle triangle = gizmo->getIntersectedTriangle( rayObjOrigin, rayObjDir );

				D3DXVECTOR3 tanget = triangle.v1 - triangle.v2; 

			}
		}
	}	

	if( !closestPrimitive && m_selectedObject )
		closestPrimitive = m_selectedObject;

	if( closestPrimitive )
	{
		closestPrimitive->setSelected( true );
	}
}

void AGDXRotater::draw(AGDXSurface* surface)
{
	m_xCircle->draw( surface );
	m_yCircle->draw( surface );
	m_zCircle->draw( surface );

	m_tangentLine->draw( surface );
}

