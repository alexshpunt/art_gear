#ifndef AG_TERRAIN_H
#define AG_TERRAIN_H

#include "Engine/Graphics/AGInputLayouts.h"

#include "Engine/Graphics/Interfaces/AGPureInterfaces.h"

#include "Engine/Graphics/Objects/AGBuffer.h"
#include "Engine/Graphics/Objects/AGShader.h"
#include "Engine/Graphics/Objects/AGMaterial.h"

#include "Engine/Managers/AGResourceManager.h"
#include "Engine/Managers/AGLogger.h"
#include "Engine/Managers/AGInputManager.h"

#include "Engine/Math/AGMath.h"

#include "Engine/Graphics/Objects/Shapes/AGSphereShape.h"

class AGTer : public AGClickable
{
	public:
		AGTer();
		~AGTer();

		void draw( AGSurface* surface );

		bool mouseClickEvent( AGMouseButton button, AGSurface* surface ) override;

		bool mouseMoveEvent( AGSurface* surface ) override
		{
			calculateRays( surface, AGMatrix() );
			return intersect( m_rayOrigin, m_rayDir ) > 0.0f; 
		}

		float intersect( const AGVec3& rayOrigin, const AGVec3& rayDir ) override
		{
			return -1.f;
		}

	protected:
		AGBuffer< int >* m_ibo;
		AGBuffer< AGVertex >* m_vbo;

		std::vector< AGVertex > m_vertices; 

		std::vector< std::vector< AGVertex > > m_vertexMap; 

		AGShader* m_shader; 
		AGMaterial* m_material; 
		int m_heightSlot;
		int m_difSlot; 
		int m_rockSlot; 
		int m_mapsSlot; 
		AGTexture2D* m_height;
		AGTexture2D* m_dif; 
		AGTexture2D* m_rock;
		AGTexture2DArray* m_txArray; 
};

#endif 