#ifndef AGDX_GIZMO_H
#define AGDX_GIZMO_H

#include "AGDXPrimitive.h"

class AGObject; 

class AGDXGizmo : public AGDXPrimitive
{
	public:
		AGDXGizmo( ID3D10Device* device );
		virtual ~AGDXGizmo();

		//Гизмо всегда рисуется на каком-то определённом расстоянии от камеры, поэтому следует 
		//задать положение гизмо в мировых координатах, где фактически должен он находится. 
		void setWorldPos( D3DXVECTOR3 worldPos );
		void setWorldPos( float x, float y, float z );
		D3DXVECTOR3 getWorldPos() const;

		void translateWorldPos( D3DXVECTOR3 delta );
		void translateWorldPos( float x, float y, float z );

		void setSelected( bool value );
		bool isSelected() const;

		void setActivated( bool value );
		bool isActivated() const; 

		virtual D3DXVECTOR3 getAxis() = 0;

	protected:
		D3DXVECTOR3 m_worldPos; 

		bool m_isSelected;
		bool m_isActivated; 
};

#endif