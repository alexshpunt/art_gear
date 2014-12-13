#include "AGDXDragger.h"

#include "AGDXArrow.h"
#include "Graphics/Objects/AGDXCamera.h"
#include "Objects/AGObject.h"
#include "Graphics/Interfaces/AGSurface.h"
#include "Managers/AGInputManager.h"
#include "Graphics/Managers/AGDXDebugDraw.h"
#include "Managers/AGGraphicsSettings.h"
#include "Managers/AGLogger.h"
#include "Math/AGMath.h"
#include "AGDXIntersectPlane.h"

AGDXDragger::AGDXDragger(ID3D10Device* device)
{
	m_xArrow = new AGDXArrow( device, AGDXArrow::X_AXIS );
	m_yArrow = new AGDXArrow( device, AGDXArrow::Y_AXIS );
	m_zArrow = new AGDXArrow( device, AGDXArrow::Z_AXIS );

	m_xyPlane = new AGDXIntersectPlane( device, AGDXIntersectPlane::XY_AXIS );
	m_xzPlane = new AGDXIntersectPlane( device, AGDXIntersectPlane::XZ_AXIS );
	m_yzPlane = new AGDXIntersectPlane( device, AGDXIntersectPlane::YZ_AXIS );

	m_selectedObject = nullptr;
	m_object = nullptr;
}

AGDXDragger::~AGDXDragger()
{
	delete m_xArrow;
	delete m_yArrow;
	delete m_zArrow;
	delete m_xyPlane;
	delete m_xzPlane;
	delete m_yzPlane;
}

void AGDXDragger::mouseClickEvent( MouseButton btn, AGDXSurface* surface )
{ 
	if( btn != MouseButton::LMB )
		return; 

	AGStateManager::CoordSystem system = AGStateManager::getInstance().getCoordSystem(); 
	calculateRays( surface );

	AGDXGizmo* gizmos[] = 
	{
		m_xArrow, m_yArrow, m_zArrow,
		m_xyPlane, m_xzPlane, m_yzPlane
	};

	AGDXGizmo* closestPrimitive = nullptr; 
	float minDist = -1.0f; 

	for( int i = 0; i < 6; i++ )
	{
		AGDXGizmo* gizmo = gizmos[ i ];

		calculateObjRays( system == AGStateManager::World ? gizmo->getLocalMatrix() : gizmo->getResultMatrix() );

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

void AGDXDragger::mouseMoveEvent( AGDXSurface* surface )
{
	AGDXGizmo* gizmos[] = 
	{
		m_xArrow, m_yArrow, m_zArrow,
		m_xyPlane, m_xzPlane, m_yzPlane
	};
	
	AGStateManager::CoordSystem system = AGStateManager::getInstance().getCoordSystem(); 
	calculateRays( surface );

	if( AGInput().isButtonPressed( "LMB" ) && m_selectedObject )
	{
		D3DXVECTOR3 axis = m_selectedObject->getAxis();

		D3DXVECTOR3 cameraEye = surface->getCamera()->getEye();
		D3DXVECTOR3 cameraDir = surface->getCamera()->getDir();

		D3DXVECTOR3 axisX( axis.x, 0.0f, 0.0f );
		D3DXVECTOR3 axisY( 0.0f, axis.y, 0.0f );
		D3DXVECTOR3 axisZ( 0.0f, 0.0f, axis.z );

		D3DXMATRIX rotMatrix = m_selectedObject->getWorldRotMatrix(); 

		D3DXVec3TransformCoord( &axisX, &axisX, &rotMatrix );
		D3DXVec3TransformCoord( &axisY, &axisY, &rotMatrix );
		D3DXVec3TransformCoord( &axisZ, &axisZ, &rotMatrix );

		float cosX = D3DXVec3Dot( &axisX, &m_rayDelta );
		float cosY = D3DXVec3Dot( &axisY, &m_rayDelta );
		float cosZ = D3DXVec3Dot( &axisZ, &m_rayDelta );

		for( int i = 0; i < 6; i++ )
		{
			D3DXVECTOR3 worldPos = gizmos[ i ]->getWorldPos(); 
			D3DXVECTOR3 lookDir = worldPos - cameraEye; 

			float len = D3DXVec3Length( &lookDir );

			gizmos[ i ]->translateWorldPos( D3DXVECTOR3( axisX.x, axisX.y, axisX.z ) * cosX * len );
			gizmos[ i ]->translateWorldPos( D3DXVECTOR3( axisY.x, axisY.y, axisY.z ) * cosY * len );
			gizmos[ i ]->translateWorldPos( D3DXVECTOR3( axisZ.x, axisZ.y, axisZ.z ) * cosZ * len );
		}

		D3DXVECTOR3 worldPos = gizmos[ 0 ]->getWorldPos();

		if( m_object )
		{
			m_object->setPos( worldPos.x, worldPos.y, worldPos.z );
		}
		else 
		{
			for( AGObject* object : m_objects )
			{
				object->setPos( worldPos.x, worldPos.y, worldPos.z );
			}
		}
				
		return;
	}

	AGDXGizmo* closestPrimitive = nullptr; 
	float minDist = -1.0f; 

	for( int i = 0; i < 6; i++ )
	{
		AGDXGizmo* gizmo = gizmos[ i ];

		calculateObjRays( system == AGStateManager::World ? gizmo->getLocalMatrix() : gizmo->getResultMatrix() );

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
}

void AGDXDragger::draw(AGDXSurface* surface)
{
	AGDXGizmo* gizmos[] = 
	{
		m_xArrow, m_yArrow, m_zArrow,
		m_xyPlane, m_xzPlane, m_yzPlane
	};

	if( !m_object && m_objects.size() == 0 )
		return; 

	if( m_object )
	{
		AGVec3 angle = m_object->getRotation(); 
		for( int i = 0; i < 6; i++ )
		{
			gizmos[ i ]->setWorldAngle( angle.x, angle.y, angle.z );
			gizmos[ i ]->draw( surface );
		}
	}
}
