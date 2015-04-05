#ifndef AG_CIRCLE_H
#define AG_CIRCLE_H

#include <vector>

#include "Engine/Graphics/Objects/AGGizmo.h"

using namespace std;

class AGCircle : public AGGizmo
{
	public:
		enum CircleAxis{ X_AXIS, Y_AXIS, Z_AXIS };
		AGCircle( CircleAxis axis );
		~AGCircle();

		void draw(  AGSurface* surface  );
		float intersect( const AGVec3& rayOrigin, const AGVec3& rayDir );

		AGVec3 getAxis(); 
		AGVec3 getTangent(); 
	private:
		ID3D10EffectVectorVariable* m_cameraPosVar; 
		ID3D10EffectScalarVariable* m_fadingVar;

		int m_nBoundIndices; 
		CircleAxis m_axis; 
		ID3D10DepthStencilState* m_depthState; 
		ID3DX10Font* m_font; 
		vector< AGVec3 > m_tangents; 
		AGVec3 m_tangent; 
		
		AGBuffer< AGColorVertex >* m_additionalVB; 
};


#endif 