#include "AGDXRotater.h"

#include "AGDXCircle.h"
#include "Managers/AGStateManager.h"
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

	m_selectedObject = nullptr;
	m_object = nullptr;
}

AGDXRotater::~AGDXRotater()
{

}

void AGDXRotater::mouseClickEvent( MouseButton btn, AGDXSurface* surface)
{
	if( btn != MouseButton::LMB )
		return; 

	AGStateManager::CoordSystem system = AGStateManager::getInstance().getCoordSystem(); 

	AGDXGizmo* gizmos[] = 
	{
		m_xCircle, m_yCircle, m_zCircle
	};

	AGDXGizmo* closestPrimitive = nullptr; 
	float minDist = -1.0f; 

	for( int i = 0; i < 3; i++ )
	{
		AGDXGizmo* gizmo = gizmos[ i ];

		calculateObjRays( system == AGStateManager::World ? gizmo->getLocalMatrix() : gizmo->getResultMatrix()  );

		float dist = gizmo->intersect( m_rayObjOrigin, m_rayObjDir );
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

		D3DXMatrixRotationYawPitchRoll( 
			&rot,
			axis.x * pi4 + axis.y * pi4 + axis.z * pi4,
			axis.x * pi4,
			axis.z * pi4  
		);

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

	AGStateManager::CoordSystem system = AGStateManager::getInstance().getCoordSystem(); 
	calculateRays( surface );

	if( AGInput().isButtonPressed( "LMB" ) && m_selectedObject )
	{
		

		D3DXVECTOR3 axis = m_selectedObject->getAxis();

		D3DXVECTOR3 cameraEye = surface->getCamera()->getEye();

		if( m_object )
		{
			float angle = m_tangent.y * m_rayDelta.y + m_tangent.x * m_rayDelta.x + m_tangent.z * m_rayDelta.z;
			m_object->rotate( angle * axis.x, angle * axis.y, angle * axis.z );
			AGStateManager::getInstance().setRotating( true );
		}
		else
		{
			for( AGObject* object : m_objects )
			{
				float angle = m_tangent.y * m_rayDelta.y + m_tangent.x * m_rayDelta.x + m_tangent.z * m_rayDelta.z;
				object->rotate( angle * axis.x, angle * axis.y, angle * axis.z );
				AGStateManager::getInstance().setRotating( true );
			}
		}

		return;
	}
	AGStateManager::getInstance().setRotating( false );

	AGDXGizmo* closestPrimitive = nullptr; 
	float minDist = -1.0f; 

	for( int i = 0; i < 3; i++ )
	{
		D3DXMATRIX matInverce;

		AGDXGizmo* gizmo = gizmos[ i ];

		calculateObjRays( system == AGStateManager::World ? gizmo->getLocalMatrix() : gizmo->getResultMatrix()  );

		float dist = gizmo->intersect( m_rayObjOrigin, m_rayObjDir );
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
	AGDXGizmo* gizmos[] = 
	{
		m_xCircle, m_yCircle, m_zCircle,
	};

	D3DXVECTOR3 gizmoPos; 
	D3DXVECTOR3 gizmoAngles; 

	if( m_object )
	{
		AGVec3 pos = m_object->getPos();
		AGVec3 angles = m_object->getRotation(); 
		gizmoPos = D3DXVECTOR3( pos.x, pos.y, pos.z );
		gizmoAngles = D3DXVECTOR3( angles.x, angles.y, angles.z );
	}
	else 
	{
		//TODO: Вычисление центра координат множества объектов 
	}

	for( int i = 0; i < 3; i++ )
	{
		gizmos[ i ]->setWorldAngle( gizmoAngles );
		gizmos[ i ]->setWorldPos( gizmoPos );
		gizmos[ i ]->draw( surface );
	}

	//AGDXDebugDraw::getInstance().drawLine( surface, m_v1, m_v2, D3DXVECTOR4( 0.0f, 0.0f, 0.0f, 1.0f ) );
}

