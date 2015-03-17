#ifndef AG_BOUNDINGBOX_H
#define AG_BOUNDINGBOX_H

#include "Engine/Graphics/Interfaces/AGPrimitive.h"
#include "Math/AGPoint3.h"

class AGCamera;

class AGBoundingBox  : public AGPrimitive
{
	public:
		//V1 - ����� ���������, V2 - ������ ��������� 
		AGBoundingBox( D3DXVECTOR3 v1, D3DXVECTOR3 v2 );
		~AGBoundingBox();

		void draw( AGSurface* surface );
		//���� ������������ �������� < 0, ������, ��� ��� �� �������� �������, ����� ��� ��������� 
		float intersect( D3DXVECTOR3 rayOrigin, D3DXVECTOR3 rayDir );

	private:
		int m_indices[ 36 ];
		D3DXVECTOR3 m_vertices[ 8 ]; 
};

#endif 