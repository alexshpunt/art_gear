#include "AGDXScaler.h"

#include "AGDXCubeArrow.h"
#include "AGDXIntersectTriangle.h"
#include "Graphics/Objects/AGDXCamera.h"
#include "Objects/AGObject.h"
#include "Graphics/Interfaces/AGSurface.h"
#include "Managers/AGInputManager.h"
#include "Managers/AGGraphicsSettings.h"
#include "Managers/AGStateManager.h"
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

	m_selectedObject = nullptr;
	m_object = nullptr;
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

void AGDXScaler::mouseClickEvent( MouseButton btn, AGDXSurface* surface)
{
	if( btn != MouseButton::LMB )
		return; 

	AGStateManager::CoordSystem system = AGStateManager::getInstance().getCoordSystem(); 
	calculateRays( surface );

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
		else if( closestPrimitive == m_xyzPlane )
		{
			m_xArrow->setSelected( true );
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

	AGStateManager::CoordSystem system = AGStateManager::getInstance().getCoordSystem(); 
	calculateRays( surface );

	if( AGInput().isButtonPressed( "LMB" ) && m_selectedObject )
	{
		calculateObjRays( system == AGStateManager::World ? m_selectedObject->getLocalMatrix() : m_selectedObject->getResultMatrix() );

		D3DXVECTOR3 axis = m_selectedObject->getAxis();

		D3DXVECTOR3 cameraEye = surface->getCamera()->getEye();

		D3DXVECTOR3 worldPos = gizmos[ 0 ]->getWorldPos();

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

		float maxVel = absMax( absMax( m_rayDelta.x, m_rayDelta.y ), m_rayDelta.z );
		maxVel *= 1.2f; 

		AGStateManager::getInstance().setRotating( true );

		D3DXVECTOR3 scale; 

		//Выглядит странно, но это работает так, как должно...
		if( m_selectedObject == m_xyPlane ||
		    m_selectedObject == m_xzPlane || 
		    m_selectedObject == m_yzPlane ||
		    m_selectedObject == m_xyzPlane )
		{
			scale = D3DXVECTOR3( maxVel * axis.x * sign( axis.x ), maxVel * axis.y * sign( axis.y ), maxVel * axis.z * sign( axis.z ) );
		}
		else
		{
			scale = D3DXVECTOR3( cosX * axis.x * sign( axis.x ), cosY * axis.y * sign( axis.y ), cosZ * axis.z * sign( axis.z ) );
		}

		for( int i = 0; i < 7; i++ )
		{
			gizmos[ i ]->scaleWorld( scale );
		}

		if( m_object )
		{
			m_object->scale( AGVec3( scale.x, scale.y, scale.z ) );
		}
		else
		{
			for( AGObject* object : m_objects )
			{
				object->scale( AGVec3( scale.x, scale.y, scale.z ) );
			}
		}

		return;
	}

	AGDXGizmo* closestPrimitive = nullptr; 
	float minDist = -1.0f; 

	for( int i = 0; i < 7; i++ )
	{
		AGDXGizmo* gizmo = gizmos[ i ];
		gizmo->setWorldScale( 1.0f, 1.0f, 1.0f );

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
	if( !m_object && m_objects.size() == 0 )
		return; 

	AGDXGizmo* gizmos[] = 
	{
		m_xArrow, m_yArrow, m_zArrow,
		m_xyzPlane, m_xyPlane, m_xzPlane, m_yzPlane
	};

	D3DXVECTOR3 gizmoPos; 
	D3DXVECTOR3 gizmoAngle; 

	if( m_object )
	{
		AGVec3 pos = m_object->getPos(); 
		AGVec3 angle = m_object->getRotation(); 
		gizmoPos = D3DXVECTOR3( pos.x, pos.y, pos.z );
		gizmoAngle = D3DXVECTOR3( angle.x, angle.y, angle.z );
	}
	else
	{
		//TODO: Нахождение центра и перемещение контроллера туда
	}

	for( int i = 0; i < 7; i++ )
	{
		gizmos[ i ]->setWorldPos( gizmoPos );
		gizmos[ i ]->setWorldAngle( gizmoAngle );
		gizmos[ i ]->draw( surface );
	}
}

