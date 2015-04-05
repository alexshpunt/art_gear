#ifndef AG_PUREINTERFACES_H
#define AG_PUREINTERFACES_H

#include <vector>

#include "Engine/Graphics/Interfaces/AGSurface.h"

#include "Engine/Managers/AGInputManager.h"

//������ ��������� ��������� ������ ���� ������������ �������� �������
//����� �� ����� ������������ ����������� ����� ����� �������������
class AGDrawable
{
	public:
		virtual void draw( AGSurface* surface ) = 0;
		//���� ������������ �������� < 0, ������, ��� ��� �� �������� ����� ���������, ����� ��� ��������� 
		virtual float intersect( D3DXVECTOR3 rayOrigin, D3DXVECTOR3 rayDir ){ return -1.0f; }
		virtual float intersect( const AGVec3& rayOrigin, const AGVec3& rayDir ); 
	protected:
		std::vector< int > m_indices;
		std::vector< AGVec3 > m_vertices; 
};

//������ ��������� ��������� ������ ��������� ����� ������� ��������� ������� ����
//��������, �� ������ ������� ��� ������������� ��� ������ 
class AGClickable : public AGDrawable
{
	public:
		virtual bool mouseClickEvent( AGMouseButton button, AGSurface* surface ) = 0;
		virtual bool mouseMoveEvent( AGSurface* surface ) = 0; 

	protected: 
		void calculateRays( AGSurface* surface );
		void calculateRays( AGSurface* surface, D3DXMATRIX worldMatrix );
		void calculateObjRays( D3DXMATRIX matWorld ); 

		D3DXVECTOR3 m_rayOrigin;
		D3DXVECTOR3 m_rayDir; 
		D3DXVECTOR3 m_rayDelta; 

		D3DXVECTOR3 m_rayObjOrigin;
		D3DXVECTOR3 m_rayObjDir; 
};

#endif 