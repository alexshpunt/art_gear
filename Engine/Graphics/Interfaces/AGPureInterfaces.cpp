#include "AGPureInterfaces.h"

#include "Graphics/Objects/AGCamera.h"
#include "Graphics/Interfaces/AGSurface.h"

void AGClickable::calculateRays( AGSurface* surface )
{
	AGPoint2 mousePos = AGInput().getMousePos(); 
	AGPoint2 point2 = mousePos + AGInput().getMouseDeltaPos();
	AGSize winSize = surface->getSize();  
	AGCamera* camera = surface->getCamera(); 

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

	D3DXMatrixInverse( &mat, NULL, &matView );

	m_rayDir.x = v.x * mat._11 + v.y * mat._21 + v.z * mat._31; 
	m_rayDir.y = v.x * mat._12 + v.y * mat._22 + v.z * mat._32; 
	m_rayDir.z = v.x * mat._13 + v.y * mat._23 + v.z * mat._33; 

	m_rayOrigin.x = mat._41;
	m_rayOrigin.y = mat._42;
	m_rayOrigin.z = mat._43;

	D3DXVECTOR3 rayOrigin, rayDir;

	rayDir.x = v1.x * mat._11 + v1.y * mat._21 + v1.z * mat._31; 
	rayDir.y = v1.x * mat._12 + v1.y * mat._22 + v1.z * mat._32; 
	rayDir.z = v1.x * mat._13 + v1.y * mat._23 + v1.z * mat._33; 

	rayOrigin.x = mat._41;
	rayOrigin.y = mat._42;
	rayOrigin.z = mat._43; 

	D3DXVECTOR3 point3d1 = m_rayOrigin + m_rayDir;
	D3DXVECTOR3 point3d2 = rayOrigin + rayDir;

	m_rayDelta = point3d2 - point3d1;
}

void AGClickable::calculateRays(AGSurface* surface, D3DXMATRIX worldMatrix)
{
	AGPoint2 mousePos = AGInput().getMousePos(); 
	AGSize winSize = surface->getSize();  
	AGCamera* camera = surface->getCamera();

	if( !camera )
	{
		return; 
	}

	D3DXMATRIX matProj = camera->getProjMatrix(); 
	D3DXMATRIX matView = camera->getViewMatrix(); 

	D3D10_VIEWPORT viewport; 
	viewport.Height = winSize.getHeight();
	viewport.Width = winSize.getWidth();
	viewport.MaxDepth = 1.0f; 
	viewport.MinDepth = 0.0f;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0; 

	D3DXVECTOR3 nearPoint( mousePos.x, mousePos.y, 0.0f );
	D3DXVECTOR3 farPoint( mousePos.x, mousePos.y, 1.0f );

	D3DXVec3Unproject( &nearPoint, &nearPoint, &viewport, &matProj, &matView, &worldMatrix );
	D3DXVec3Unproject( &farPoint, &farPoint, &viewport, &matProj, &matView, &worldMatrix );

	D3DXVECTOR3 dir = farPoint - nearPoint; 
	D3DXVec3Normalize( &dir, &dir );

	m_rayOrigin = nearPoint; 
	m_rayDir = dir; 
}

void AGClickable::calculateObjRays( const AGMatrix& matWorld )
{
	D3DXMATRIX matInverce;
	D3DXMatrixInverse( &matInverce, NULL, &matWorld );

	D3DXVec3TransformCoord( &m_rayObjOrigin, &m_rayOrigin, &matInverce );
	D3DXVec3TransformNormal( &m_rayObjDir, &m_rayDir, &matInverce );

	D3DXVec3Normalize( &m_rayObjDir, &m_rayObjDir );
}