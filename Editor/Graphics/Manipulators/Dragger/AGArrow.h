#ifndef AG_ARROW_H
#define AG_ARROW_H

#include <vector>

#include "Engine/Graphics/Objects/AGGizmo.h"
#include "Engine/Graphics/Objects/AGBoundingBox.h"

using namespace std;

class AGArrow : public AGGizmo
{
	public:
		enum ArrowAxis{ X_AXIS, Y_AXIS, Z_AXIS };
		AGArrow( ArrowAxis axis );
		~AGArrow();

		void draw(  AGSurface* surface  );
		float intersect( const AGVec3& rayOrigin, const AGVec3& rayDir );

		AGVec3 getAxis(); 
	private:
		int m_nIndices; 
		ArrowAxis m_axis; 
		ID3D10DepthStencilState* m_depthState; 
		ID3DX10Font* m_font; 
		AGBoundingBox* m_boundingBox;
		vector< AGPrimitiveVertex > m_vertices;
		vector< int > m_indices; 
};

#endif 