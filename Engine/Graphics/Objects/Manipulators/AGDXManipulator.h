#ifndef AGDX_MANIPULATOR_H
#define AGDX_MANIPULATOR_H

#include <d3dx10.h>
#include <d3d10.h>
#include <string>
#include <list>

#include "Managers/AGInputManager.h"

class AGDXSurface; 
class AGObject; 

using namespace std; 

class AGDXManipulator 
{
	public:
		virtual ~AGDXManipulator(); 

		void setObjects( list< AGObject* > objects );
		list< AGObject* > getObjects() const; 

		void setObject( AGObject* object );
		AGObject* getObject() const; 

		virtual void mouseClickEvent( MouseButton btn, AGDXSurface* surface ) = 0;
		virtual void mouseMoveEvent( AGDXSurface* surface ) = 0;

		virtual void draw( AGDXSurface* surface ) = 0; 

	protected:
		void calculateRays( AGDXSurface* surface );
		void calculateObjRays( D3DXMATRIX matWorld ); 

		list< AGObject* > m_objects;
		AGObject* m_object; 

		D3DXVECTOR3 m_rayOrigin;
		D3DXVECTOR3 m_rayDir; 
		D3DXVECTOR3 m_rayDelta; 

		D3DXVECTOR3 m_rayObjOrigin;
		D3DXVECTOR3 m_rayObjDir; 
};

#endif 