#ifndef AG_PUREINTERFACES_H
#define AG_PUREINTERFACES_H

#include "Engine/Math/AGMath.h"

class AGSurface; 

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
		void calculateDeltaRays( AGSurface* surface );
		void calculateRays( AGSurface* surface, const AGMatrix& matWorld );

		AGVec3 m_rayOrigin;
		AGVec3 m_rayDir; 
		AGVec3 m_rayDelta; 
};

#endif 