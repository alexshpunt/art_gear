#include "AGDragger.h"

#include "AGArrow.h"
#include "Engine/Graphics/Objects/AGCamera.h"
#include "Engine/Objects/AGGameObject.h"
#include "Engine/Graphics/Interfaces/AGSurface.h"
#include "Engine/Managers/AGInputManager.h"
#include "Engine/Managers/AGGraphicsSettings.h"
#include "Engine/Managers/AGLogger.h"
#include "Engine/Graphics/Components/AGRenderer.h"
#include "Engine/Math/AGMath.h"

#include "AGIntersectPlane.h"

#include "Editor/Managers/AGEStateManager.h"

AGDragger::AGDragger()
{
	m_xArrow = new AGArrow( AGArrow::X_AXIS );
	m_yArrow = new AGArrow( AGArrow::Y_AXIS );
	m_zArrow = new AGArrow( AGArrow::Z_AXIS );

	m_xyPlane = new AGIntersectPlane( AGIntersectPlane::XY_AXIS );
	m_xzPlane = new AGIntersectPlane( AGIntersectPlane::XZ_AXIS );
	m_yzPlane = new AGIntersectPlane( AGIntersectPlane::YZ_AXIS );

	m_selectedObject = nullptr;
}

AGDragger::~AGDragger()
{
	delete m_xArrow;
	delete m_yArrow;
	delete m_zArrow;
	delete m_xyPlane;
	delete m_xzPlane;
	delete m_yzPlane;
}

bool AGDragger::mouseClickEvent( AGMouseButton btn, AGSurface* surface )
{ 
	AGEStateManager::ToolBarState toolBarState = AGEStateManager::getInstance().getToolBarState(); 
	
	if( toolBarState != AGEStateManager::Dragger || !m_object ) 
		return false; 

	if( btn != AGMouseButton::LMB )
		return false; 

	AGEStateManager::CoordSystem system = AGEStateManager::getInstance().getCoordSystem(); 

	AGGizmo* gizmos[] = 
	{
		m_xArrow, m_yArrow, m_zArrow,
		m_xyPlane, m_xzPlane, m_yzPlane
	};

	AGGizmo* closestPrimitive = nullptr; 
	float minDist = -1.0f; 

	for( int i = 0; i < 6; i++ )
	{
		AGGizmo* gizmo = gizmos[ i ];

		calculateRays( surface, system == AGEStateManager::World ? gizmo->getLocalMatrix() : gizmo->getResultMatrix() );

		float dist = gizmo->intersect( m_rayOrigin, m_rayDir );
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

	return m_selectedObject; 
}

bool AGDragger::mouseMoveEvent( AGSurface* surface )
{
	AGEStateManager::ToolBarState toolBarState = AGEStateManager::getInstance().getToolBarState(); 

	if( toolBarState != AGEStateManager::Dragger || !m_object ) 
		return false; 

	AGGizmo* gizmos[] = 
	{
		m_xArrow, m_yArrow, m_zArrow,
		m_xyPlane, m_xzPlane, m_yzPlane
	};
	
	AGEStateManager::CoordSystem system = AGEStateManager::getInstance().getCoordSystem(); 
	calculateDeltaRays( surface );

	if( AGInput().isButtonPressed( "LMB" ) && m_selectedObject )
	{
		AGVec3 axis = m_selectedObject->getAxis();

		AGVec3 cameraEye = surface->getCamera()->getPos();
		AGVec3 cameraDir = surface->getCamera()->getDir();

		AGVec3 axisX( axis.x, 0.0f, 0.0f );
		AGVec3 axisY( 0.0f, axis.y, 0.0f );
		AGVec3 axisZ( 0.0f, 0.0f, axis.z );

		D3DXMATRIX rotMatrix = m_selectedObject->getWorldRotMatrix(); 

		if( system == AGEStateManager::Local )
		{
			D3DXVec3TransformCoord( &axisX, &axisX, &rotMatrix );
			D3DXVec3TransformCoord( &axisY, &axisY, &rotMatrix );
			D3DXVec3TransformCoord( &axisZ, &axisZ, &rotMatrix );
		}
		
		float cosX = D3DXVec3Dot( &axisX, &m_rayDelta );
		float cosY = D3DXVec3Dot( &axisY, &m_rayDelta );
		float cosZ = D3DXVec3Dot( &axisZ, &m_rayDelta );

		for( int i = 0; i < 6; i++ )
		{
			AGVec3 worldPos = gizmos[ i ]->getBeginPos(); 
			AGVec3 lookDir = worldPos - cameraEye; 

			float len = D3DXVec3LengthSq( &lookDir );
		
			gizmos[ i ]->translateBeginPos( AGVec3( axisX.x, axisX.y, axisX.z ) * cosX * len );
			gizmos[ i ]->translateBeginPos( AGVec3( axisY.x, axisY.y, axisY.z ) * cosY * len );
			gizmos[ i ]->translateBeginPos( AGVec3( axisZ.x, axisZ.y, axisZ.z ) * cosZ * len );
		}

		AGVec3 worldPos = gizmos[ 0 ]->getBeginPos();

		if( m_object )
		{
			switch( system )
			{
				case AGEStateManager::Local:
					m_object->setLocalPos( worldPos.x, worldPos.y, worldPos.z );
				break;
				case AGEStateManager::World:
					m_object->setWorldPos( worldPos.x, worldPos.y, worldPos.z );
				break;

			}
		}
		else 
		{
			for( AGGameObject* object : m_objects )
			{
				switch( system )
				{
					case AGEStateManager::Local:
						object->setLocalPos( worldPos.x, worldPos.y, worldPos.z );
					break;
					case AGEStateManager::World:
						object->setWorldPos( worldPos.x, worldPos.y, worldPos.z );
					break;
				}
			}
		}
				
		return true;
	}

	AGGizmo* closestPrimitive = nullptr; 
	float minDist = -1.0f; 

	for( int i = 0; i < 6; i++ )
	{
		AGGizmo* gizmo = gizmos[ i ];

		calculateObjRays( system == AGEStateManager::World ? gizmo->getLocalMatrix() : gizmo->getResultMatrix() );

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
		return true;
	}
	return false; 
}

void AGDragger::draw( AGSurface* surface )
{
	AGEStateManager::ToolBarState toolBarState = AGEStateManager::getInstance().getToolBarState(); 

	if( toolBarState != AGEStateManager::Dragger || !m_object ) 
		return; 

	AGGizmo* gizmos[] = 
	{
		m_xArrow, m_yArrow, m_zArrow,
		m_xyPlane, m_xzPlane, m_yzPlane
	};

	AGVec3 angle = m_object->getLocalRot(); 
	for( int i = 0; i < 6; i++ )
	{
		gizmos[ i ]->setWorldRotMatrix( m_object->getRenderer()->getLocalRotMatrix() );
		gizmos[ i ]->draw( surface );
	}
}
