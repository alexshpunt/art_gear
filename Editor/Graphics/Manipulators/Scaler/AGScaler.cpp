#include "AGScaler.h"

#include "AGCubeArrow.h"
#include "AGIntersectTriangle.h"
#include "Engine/Graphics/Objects/AGCamera.h"
#include "Engine/Objects/AGGameObject.h"
#include "Engine/Graphics/Interfaces/AGSurface.h"
#include "Engine/Managers/AGInputManager.h"
#include "Engine/Managers/AGGraphicsSettings.h"
#include "Managers/AGEStateManager.h"
#include "Engine/Managers/AGLogger.h"
#include "Engine/Math/AGMath.h"

AGScaler::AGScaler()
{
	m_xArrow = new AGCubeArrow( AGCubeArrow::X_AXIS );
	m_yArrow = new AGCubeArrow( AGCubeArrow::Y_AXIS );
	m_zArrow = new AGCubeArrow( AGCubeArrow::Z_AXIS );

	m_xyPlane  = new AGIntersectTriangle( AGIntersectTriangle::XY_AXIS );
	m_xzPlane  = new AGIntersectTriangle( AGIntersectTriangle::XZ_AXIS );
	m_yzPlane  = new AGIntersectTriangle( AGIntersectTriangle::YZ_AXIS );
	m_xyzPlane = new AGIntersectTriangle( AGIntersectTriangle::XYZ_AXIS );

	m_selectedObject = nullptr;
}

AGScaler::~AGScaler()
{
	delete m_xArrow;
	delete m_yArrow;
	delete m_zArrow;

	delete m_xyPlane;
	delete m_xzPlane;
	delete m_yzPlane;
	delete m_xyzPlane; 
}

bool AGScaler::mouseClickEvent( AGMouseButton btn, AGSurface* surface)
{
	AGEStateManager::ToolBarState toolBarState = AGEStateManager::getInstance().getToolBarState(); 

	if( toolBarState != AGEStateManager::Scaler || !m_object ) 
		return false; 

	if( btn != AGMouseButton::LMB )
		return false; 

	AGEStateManager::CoordSystem system = AGEStateManager::getInstance().getCoordSystem(); 
	calculateDeltaRays( surface );

	AGGizmo* gizmos[] = 
	{
		m_xArrow, m_yArrow, m_zArrow,
		m_xyzPlane, m_xyPlane, m_xzPlane, m_yzPlane
	};

	AGGizmo* closestPrimitive = nullptr; 
	float minDist = -1.0f; 

	for( int i = 0; i < 7; i++ )
	{
		D3DXMATRIX matInverce;

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
	m_selectedObject = closestPrimitive;
	
	return m_selectedObject;
}

bool AGScaler::mouseMoveEvent(AGSurface* surface)
{
	AGEStateManager::ToolBarState toolBarState = AGEStateManager::getInstance().getToolBarState(); 

	if( toolBarState != AGEStateManager::Scaler || !m_object ) 
		return false; 

	AGGizmo* gizmos[] = 
	{
		m_xArrow, m_yArrow, m_zArrow,
		m_xyzPlane, m_xyPlane, m_xzPlane, m_yzPlane
	};

	AGEStateManager::CoordSystem system = AGEStateManager::getInstance().getCoordSystem(); 
	calculateDeltaRays( surface );

	if( AGInput().isButtonPressed( "LMB" ) && m_selectedObject )
	{
		calculateObjRays( system == AGEStateManager::World ? m_selectedObject->getLocalMatrix() : m_selectedObject->getResultMatrix() );

		AGVec3 axis = m_selectedObject->getAxis();

		AGVec3 cameraEye = surface->getCamera()->getPos();

		AGVec3 worldPos = gizmos[ 0 ]->getBeginPos();

		AGVec3 axisX( axis.x, 0.0f, 0.0f );
		AGVec3 axisY( 0.0f, axis.y, 0.0f );
		AGVec3 axisZ( 0.0f, 0.0f, axis.z );

		D3DXMATRIX rotMatrix = m_selectedObject->getWorldRotMatrix(); 

		D3DXVec3TransformCoord( &axisX, &axisX, &rotMatrix );
		D3DXVec3TransformCoord( &axisY, &axisY, &rotMatrix );
		D3DXVec3TransformCoord( &axisZ, &axisZ, &rotMatrix );

		float cosX = D3DXVec3Dot( &axisX, &m_rayDelta );
		float cosY = D3DXVec3Dot( &axisY, &m_rayDelta );
		float cosZ = D3DXVec3Dot( &axisZ, &m_rayDelta );

		float maxVel = absMax( absMax( m_rayDelta.x, m_rayDelta.y ), m_rayDelta.z );
		maxVel *= 1.2f; 

		AGEStateManager::getInstance().setRotating( true );

		AGVec3 scale; 

		//Выглядит странно, но это работает так, как должно...
		if( m_selectedObject == m_xyPlane ||
		    m_selectedObject == m_xzPlane || 
		    m_selectedObject == m_yzPlane ||
		    m_selectedObject == m_xyzPlane )
		{
			scale = AGVec3( maxVel * axis.x * sign( axis.x ), maxVel * axis.y * sign( axis.y ), maxVel * axis.z * sign( axis.z ) );
		}
		else
		{
			scale = AGVec3( cosX * axis.x * sign( axis.x ), cosY * axis.y * sign( axis.y ), cosZ * axis.z * sign( axis.z ) );
		}

		for( int i = 0; i < 7; i++ )
		{
			gizmos[ i ]->scaleWorld( scale );
		}

		if( m_object )
		{
			switch( system )
			{
				case AGEStateManager::Local:
					m_object->scaleLocal( AGVec3( scale.x, scale.y, scale.z ) );
				break;
				case AGEStateManager::World:
					m_object->scaleWorld( AGVec3( scale.x, scale.y, scale.z ) );
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
						object->scaleLocal( AGVec3( scale.x, scale.y, scale.z ) );
					break;
					case AGEStateManager::World:
						object->scaleWorld( AGVec3( scale.x, scale.y, scale.z ) );
					break;
				}
			}
		}

		return true;
	}

	AGGizmo* closestPrimitive = nullptr; 
	float minDist = -1.0f; 

	for( int i = 0; i < 7; i++ )
	{
		AGGizmo* gizmo = gizmos[ i ];
		gizmo->setWorldScale( 1.0f, 1.0f, 1.0f );

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
		else if( closestPrimitive == m_xyzPlane )
		{
			m_xArrow->setSelected( true );
			m_yArrow->setSelected( true );
			m_zArrow->setSelected( true );
		}
	}
	return m_selectedObject;
}

void AGScaler::draw( AGSurface* surface )
{
	AGEStateManager::ToolBarState toolBarState = AGEStateManager::getInstance().getToolBarState(); 

	if( toolBarState != AGEStateManager::Scaler || !m_object ) 
		return; 

	if( !m_object && m_objects.size() == 0 )
		return; 

	AGGizmo* gizmos[] = 
	{
		m_xArrow, m_yArrow, m_zArrow,
		m_xyzPlane, m_xyPlane, m_xzPlane, m_yzPlane
	};

	AGVec3 gizmoPos; 
	AGVec3 gizmoAngle; 

	if( m_object )
	{
		AGVec3 pos = m_object->getLocalPos(); 
		AGVec3 angle = m_object->getLocalRot(); 
		gizmoPos = AGVec3( pos.x, pos.y, pos.z );
		gizmoAngle = AGVec3( angle.x, angle.y, angle.z );
	}
	else
	{
		//TODO: Нахождение центра и перемещение контроллера туда
	}

	for( int i = 0; i < 7; i++ )
	{
		gizmos[ i ]->setBeginPos( gizmoPos );
		gizmos[ i ]->setWorldAngle( gizmoAngle );
		gizmos[ i ]->draw( surface );
	}
}

