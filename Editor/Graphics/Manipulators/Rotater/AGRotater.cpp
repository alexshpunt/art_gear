#include "AGRotater.h"

#include "Engine/Graphics/Components/AGRenderer.h"
#include "AGCircle.h"
#include "Editor/Managers/AGEStateManager.h"
#include "Engine/Graphics/Objects/AGCamera.h"
#include "Engine/Objects/AGGameObject.h"
#include "Engine/Graphics/Interfaces/AGSurface.h"
#include "Engine/Managers/AGInputManager.h"
#include "Engine/Managers/AGGraphicsSettings.h"
#include "Engine/Managers/AGLogger.h"
#include "Engine/Math/AGMath.h"

AGRotater::AGRotater() : AGManipulator()
{
	m_xCircle = new AGCircle( AGCircle::X_AXIS );
	m_yCircle = new AGCircle( AGCircle::Y_AXIS );
	m_zCircle = new AGCircle( AGCircle::Z_AXIS );

	m_selectedObject = nullptr;
	m_angles = AGVec3( 0.0f, 0.0f, 0.0f );
}

AGRotater::~AGRotater()
{

}

bool AGRotater::mouseClickEvent( AGMouseButton btn, AGSurface* surface)
{
	AGEStateManager::ToolBarState toolBarState = AGEStateManager::getInstance().getToolBarState(); 

	if( toolBarState != AGEStateManager::Rotater || !m_object ) 
		return false; 
	

	if( btn != AGMouseButton::LMB )
		return false; 

	AGEStateManager::CoordSystem system = AGEStateManager::getInstance().getCoordSystem(); 

	AGGizmo* gizmos[] = 
	{
		m_xCircle, m_yCircle, m_zCircle
	};

	AGGizmo* closestPrimitive = nullptr; 
	float minDist = -1.0f; 

	for( int i = 0; i < 3; i++ )
	{
		AGGizmo* gizmo = gizmos[ i ];

		calculateRays( surface, system == AGEStateManager::World ? gizmo->getLocalMatrix() : gizmo->getResultMatrix()  );

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
	}
	m_selectedObject = closestPrimitive;

	if( m_selectedObject )
	{
		m_v1 = m_selectedObject->getBeginPos();
		m_v2 = ( reinterpret_cast< AGCircle* >( m_selectedObject ) )->getTangent(); 

		AGVec3 axis = m_selectedObject->getAxis();
		AGVec3 pos = m_selectedObject->getBeginPos();
		AGMatrix worldRot = m_selectedObject->getWorldRotMatrix();
		AGRadians pi4( AGMath::toRadians( 90.0f ) );

		AGMatrix transl = AGMatrix::Translation( pos );
		AGMatrix rot = AGMatrix::Rotation( 
			AGRadians( axis.x * pi4 + axis.y * pi4 + axis.z * pi4 ),
			AGRadians( axis.x * pi4 ),
			AGRadians( axis.z * pi4 ) 
		);

		AGMatrix world = worldRot * rot * transl; 

		m_v1 *= world;
		m_v2 *= world; 

		m_tangent = ( m_v2 - m_v1 ).normilized(); 

		return true; 
	}
	return false; 
}

bool AGRotater::mouseMoveEvent(AGSurface* surface)
{
	AGEStateManager::ToolBarState toolBarState = AGEStateManager::getInstance().getToolBarState(); 

	if( toolBarState != AGEStateManager::Rotater || !m_object ) 
		return false; 

	AGGizmo* gizmos[] = 
	{
		m_xCircle, m_yCircle, m_zCircle,
	};

	AGEStateManager::CoordSystem system = AGEStateManager::getInstance().getCoordSystem(); 
	calculateDeltaRays( surface );

	if( AGInput().isButtonPressed( "LMB" ) && m_selectedObject )
	{
		AGVec3 axis = m_selectedObject->getAxis();

		AGVec3 cameraEye = surface->getCamera()->getPos();

		float cosT = AGVec3::dot( m_tangent, m_rayDelta );

		AGEStateManager::CoordSystem system = AGEStateManager::getInstance().getCoordSystem(); 

		if( m_object )
		{
			float angle = absMax( absMax( m_rayDelta.x, m_rayDelta.y ), m_rayDelta.z ) * 1.6f;
			if( m_selectedObject == m_xCircle )
			{
				switch( system )
				{
					case AGEStateManager::World:
						m_object->rotateAroundWorldX( angle );
					break;
					case AGEStateManager::Local:
						m_object->rotateLocalX( angle );
					break;
				}
			}
			else if( m_selectedObject == m_yCircle )
			{
				switch( system )
				{
					case AGEStateManager::World:
						m_object->rotateAroundWorldY( angle );
					break;
					case AGEStateManager::Local:
						m_object->rotateLocalY( angle );
					break;
				}
			}
			else if( m_selectedObject == m_zCircle )
			{
				switch( system )
				{
					case AGEStateManager::World:
						m_object->rotateAroundWorldZ( angle );
					break;
					case AGEStateManager::Local:
						m_object->rotateLocalZ( angle );
					break;
				}
			}
			
			
		}
		AGEStateManager::getInstance().setRotating( true );

		return true;
	}
	AGEStateManager::getInstance().setRotating( false );

	AGGizmo* closestPrimitive = nullptr; 
	float minDist = -1.0f; 

	for( int i = 0; i < 3; i++ )
	{
		AGGizmo* gizmo = gizmos[ i ];

		calculateRays( surface, system == AGEStateManager::World ? gizmo->getLocalMatrix() : gizmo->getResultMatrix()  );

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

	if( !closestPrimitive && m_selectedObject )
		closestPrimitive = m_selectedObject;

	if( closestPrimitive )
	{
		closestPrimitive->setSelected( true );
		return true; 
	}
	return false; 
}

void AGRotater::draw( AGSurface* surface )
{
	AGEStateManager::ToolBarState toolBarState = AGEStateManager::getInstance().getToolBarState(); 

	if( toolBarState != AGEStateManager::Rotater || !m_object ) 
		return; 

	AGGizmo* gizmos[] = 
	{
		m_xCircle, m_yCircle, m_zCircle,
	};

	AGVec3 gizmoPos; 
	AGVec3 gizmoAngles; 

	if( m_object )
	{
		AGVec3 pos = m_object->getLocalPos();
		AGVec3 angles = m_object->getLocalRot(); 
		gizmoPos = AGVec3( pos.x, pos.y, pos.z );
		gizmoAngles = AGVec3( angles.x, angles.y, angles.z );
	}
	else 
	{
		//TODO: Вычисление центра координат множества объектов 
	}

	for( int i = 0; i < 3; i++ )
	{
		gizmos[ i ]->setWorldRotMatrix( m_object->getRenderer()->getLocalRotMatrix() );
		gizmos[ i ]->setBeginPos( gizmoPos );
		gizmos[ i ]->draw( surface );
	}

	//AGDebugDraw::getInstance().drawLine( surface, AGVec3( 0.0f, 0.0f, 0.0f ), m_tangent, D3DXVECTOR4( 1.0f, 1.0f, 0.0f, 1.0f ) );
}

 