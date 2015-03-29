#include "AGPureInterfaces.h"

#include "Engine/Managers/AGInputManager.h"

#include "Graphics/Objects/AGCamera.h"

#include "Graphics/Interfaces/AGSurface.h"

void AGClickable::calculateDeltaRays( AGSurface* surface )
{
	AGPoint2 mousePos = AGInput().getMousePos(); 
	AGPoint2 nextMousePos = mousePos + AGInput().getMouseDeltaPos();
	AGSize winSize = surface->getSize();  
	AGCamera* camera = surface->getCamera();

	assert( camera ); 

	AGMatrix matWorld; 
	const AGMatrix& matProj = camera->getProjMatrix(); 
	const AGMatrix& matView = camera->getViewMatrix(); 

	//Calculate one ray 
	{
		AGVec3 nearPoint = AGVec3::unproject( AGVec3( mousePos.x, mousePos.y, 0.0f ), AGRect( 0, 0, winSize ), matWorld, matView, matProj );
		AGVec3 farPoint  = AGVec3::unproject( AGVec3( mousePos.x, mousePos.y, 1.0f ), AGRect( 0, 0, winSize ), matWorld, matView, matProj );

		AGVec3 dir = ( farPoint - nearPoint ).normilized(); 

		m_rayOrigin = nearPoint; 
		m_rayDir = dir; 

		m_rayDelta = m_rayOrigin + m_rayDir; 
	}

	//Calculate another 
	{
		AGVec3 nearPoint = AGVec3::unproject( AGVec3( nextMousePos.x, nextMousePos.y, 0.0f ), AGRect( 0, 0, winSize ), matWorld, matView, matProj );
		AGVec3 farPoint  = AGVec3::unproject( AGVec3( nextMousePos.x, nextMousePos.y, 1.0f ), AGRect( 0, 0, winSize ), matWorld, matView, matProj );

		AGVec3 dir = ( farPoint - nearPoint ).normilized(); 

		m_rayDelta -= nearPoint + dir; 
	}

	
}

void AGClickable::calculateRays( AGSurface* surface, const AGMatrix& matWorld )
{
	AGPoint2 mousePos = AGInput().getMousePos(); 
	AGSize winSize = surface->getSize();  
	AGCamera* camera = surface->getCamera();

	assert( camera ); 

	const AGMatrix& matProj = camera->getProjMatrix(); 
	const AGMatrix& matView = camera->getViewMatrix(); 

	AGVec3 nearPoint = AGVec3::unproject( AGVec3( mousePos.x, mousePos.y, 0.0f ), AGRect( 0, 0, winSize ), matWorld, matView, matProj );
	AGVec3 farPoint  = AGVec3::unproject( AGVec3( mousePos.x, mousePos.y, 1.0f ), AGRect( 0, 0, winSize ), matWorld, matView, matProj );

	AGVec3 dir = ( farPoint - nearPoint ).normilized(); 

	m_rayOrigin = nearPoint; 
	m_rayDir = dir; 
}

float AGDrawable::intersect(const AGVec3& rayOrigin, const AGVec3& rayDir)
{
	float retDist = -1.0f;
	int nIndices = m_indices.size() - 2;  
	for( int i = 0; i < nIndices; i++ )
	{
		AGVec3 v1 = m_vertices[ m_indices[ i ] ];
		AGVec3 v2 = m_vertices[ m_indices[ i + 1 ] ];
		AGVec3 v3 = m_vertices[ m_indices[ i + 2 ] ];

		AGMath::IntersectResult res = AGMath::intersectTriangle( rayOrigin, rayDir, AGMath::Triangle( v1, v2, v3 ) ); 

		if( res.hit )
		{
			if( retDist < 0 )
			{
				retDist = res.distance; 
			}
			else 
			{
				retDist = min( retDist, res.distance ); 
			}
		}
	}

	return retDist; 
}
