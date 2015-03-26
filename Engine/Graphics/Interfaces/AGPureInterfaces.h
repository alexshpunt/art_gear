#ifndef AG_PUREINTERFACES_H
#define AG_PUREINTERFACES_H

#include "Engine/Math/AGMath.h"

#include "Engine/Graphics/Interfaces/AGSurface.h"

#include "Engine/Managers/AGInputManager.h"

//������ ��������� ��������� ������ ���� ������������ �������� �������
//����� �� ����� ������������ ����������� ����� ����� �������������
class AGDrawable
{
	public:
		virtual void draw( AGSurface* surface ) = 0;
		//���� ������������ �������� < 0, ������, ��� ��� �� �������� ����� ���������, ����� ��� ��������� 
		virtual float intersect( const AGVec3& rayOrigin, const AGVec3& rayDir ){ return -1.0f; }
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
		void calculateRays( AGSurface* surface, const AGMatrix& worldMatrix );
		void calculateObjRays( const AGMatrix& matWorld ); 

		AGVec3 m_rayOrigin;
		AGVec3 m_rayDir; 
		AGVec3 m_rayDelta; 

		AGVec3 m_rayObjOrigin;
		AGVec3 m_rayObjDir; 
};

#endif 