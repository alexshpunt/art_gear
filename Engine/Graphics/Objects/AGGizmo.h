#ifndef AG_GIZMO_H
#define AG_GIZMO_H

#include "Engine/Graphics/Interfaces/AGPrimitive.h"

class AGGameObject; 

//������, ������� �������� ���� ���������� �� ��������� ��������� �� ������ ����� ������� � ���������� ������������ 
class AGGizmo : public AGPrimitive
{
	public:
		AGGizmo();
		virtual ~AGGizmo();

		void setDistance( float distance );
		float getDistance() const; 

		void setBeginPos( D3DXVECTOR3 beginPos );
		void setBeginPos( float x, float y, float z );
		D3DXVECTOR3 getBeginPos() const;

		void translateBeginPos( D3DXVECTOR3 delta );
		void translateBeginPos( float x, float y, float z );

		void setSelected( bool value );
		bool isSelected() const;

		virtual D3DXVECTOR3 getAxis() = 0;
		 
	protected:
		virtual void updatePos( AGCamera* camera ); 
		virtual void setupBuffers( AGSurface* surface );
		void releaseBuffers(); 

		D3DXVECTOR3 m_beginPos; 
		float m_distance; 

		bool m_isSelected;

		ID3D10Buffer* m_vbo; 
		ID3D10Buffer* m_ibo; 
};

#endif