#include "AGDXRotater.h"

#include "AGDXCircle.h"
#include "Graphics/Managers/AGDXDebugDraw.h"
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

	if( m_selectedObject )
	{
		m_v1 = m_selectedObject->getWorldPos();
		m_v2 = ( reinterpret_cast< AGDXCircle* >( m_selectedObject ) )->getTangent(); 

		D3DXVECTOR3 axis = m_selectedObject->getAxis();

		D3DXVECTOR3 pos = m_selectedObject->getWorldPos();

		D3DXMATRIX world;
		D3DXMatrixIdentity( &world );
		D3DXMATRIX transl;
		D3DXMatrixIdentity( &transl );
		D3DXMATRIX rot;
		D3DXMatrixIdentity( &rot );

		D3DXMatrixTranslation( &transl, pos.x, pos.y, pos.z );

		float pi4 = D3DXToRadian( 90.0f );

		D3DXMatrixRotationYawPitchRoll( &rot,
			axis.x * pi4 + axis.y * pi4 + axis.z * pi4,
			axis.x * pi4,
			axis.z * pi4  );

		world *= rot * transl; 

		D3DXVec3TransformCoord( &m_v1, &m_v1, &world );
		D3DXVec3TransformCoord( &m_v2, &m_v2, &world );

		m_tangent = m_v2 - m_v1; 

		D3DXVec3Normalize( &m_tangent, &m_tangent );
	}
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

		D3DXVECTOR3 axis = m_selectedObject->getAxis();

		D3DXVECTOR3 cameraEye = surface->getCamera()->getEye();

		//m_tangent = D3DXVECTOR3( m_tangent.x * axis.x, m_tangent.y * axis.y, m_tangent.z * axis.z );

		if( m_object )
		{
			AGDebug() << m_tangent.x << " " << m_tangent.y << " " << m_tangent.z;

			float angle = m_tangent.y * vec2.y + m_tangent.x * vec2.x + m_tangent.z * vec2.z;

			m_object->rotate( angle * axis.x, angle * axis.y, angle * axis.z );
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

	AGDXDebugDraw::getInstance().drawLine( surface, m_v1, m_v2, D3DXVECTOR4( 0.0f, 0.0f, 0.0f, 1.0f ) );
}

