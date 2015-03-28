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
