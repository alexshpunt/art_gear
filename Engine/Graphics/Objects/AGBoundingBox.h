#ifndef AG_BOUNDINGBOX_H
#define AG_BOUNDINGBOX_H

#include "Engine/Graphics/Interfaces/AGPrimitive.h"
#include "Math/AGPoint3.h"

class AGCamera;

class AGBoundingBox  : public AGPrimitive
{
	public:
		//V1 - ����� ���������, V2 - ������ ��������� 
		AGBoundingBox( AGVec3 v1, AGVec3 v2 );
		~AGBoundingBox();

		void draw( AGSurface* surface );
		//���� ������������ �������� < 0, ������, ��� ��� �� �������� �������, ����� ��� ��������� 
		float intersect( AGVec3 rayOrigin, AGVec3 rayDir );

	private:
		int m_indices[ 36 ];
		AGVec3 m_vertices[ 8 ]; 
};

#endif 