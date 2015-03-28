#ifndef AG_BOUNDINGBOX_H
#define AG_BOUNDINGBOX_H

#include "Engine/Graphics/Interfaces/AGPrimitive.h"
#include "Math/AGPoint3.h"

class AGCamera;

class AGBoundingBox  : public AGPrimitive
{
	public:
		//V1 - конец диагонали, V2 - начало диагонали 
		AGBoundingBox( AGVec3 v1, AGVec3 v2 );
		~AGBoundingBox();

		void draw( AGSurface* surface );
		//Если возвращаемое значение < 0, значит, что луч не коснулся коробки, иначе это дистанция 
		float intersect( AGVec3 rayOrigin, AGVec3 rayDir );

	private:
		int m_indices[ 36 ];
		AGVec3 m_vertices[ 8 ]; 
};

#endif 