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

#include "Engine/Graphics/Objects/Shapes/AGCircleShape.h"
#include "Engine/Graphics/Objects/Shapes/AGLine.h"

#include <QPixmap>

struct AGTerrainVertex
{
	AGVec3 pos;
	AGVec3 normal; 
};

class AGTerrain : public AGClickable
{
	public:
		AGTerrain();
		~AGTerrain();

		void draw( AGSurface* surface ) override; 
		bool mouseClickEvent( AGMouseButton button, AGSurface* surface ) override;
		bool mouseMoveEvent( AGSurface* surface ) override;
		float intersect( const AGVec3& rayOrigin, const AGVec3& rayDir ) override; 

		const AGVec3& getIntersectPos() const; 

		void setPaintingMode( bool value );
		void setRadius( float radius );
		void setHardness( float hardness );
		void setTextureIndex( int index );
		void addTexture( const std::wstring& fileName );
	protected:
		AGBuffer< int >* m_ibo;
		AGBuffer< AGVertex >* m_vbo; 

		std::vector< std::vector< AGVertex > > m_vertexMap; 
		std::vector< AGVec3 > m_normals; 

		AGCircleShape* m_circle; 
		AGLine* m_line; 

		AGVec3 m_border; 
		AGVec3 m_border2; 

		AGVec3 m_intersectPos; 

		AGShader* m_shader; 
		AGMaterial* m_material; 
		int m_heightSlot;
		int m_difSlot; 
		int m_rockSlot; 
		int m_mapsSlot; 
		int m_cursorPosSlot; 
		int m_radiusSlot; 
		AGTexture2D* m_height;
		AGTexture2D* m_dif; 
		AGTexture2D* m_rock;
		AGTexture2DArray* m_txArray; 
		AGTexture2DArray* m_blendArray; 

		AGSize m_textureSize; 

		bool m_paintingMode; 
		float m_radius; 
		float m_harndess; 
		int m_textureIndex; 

		QImage m_brushMap; 
		QImage m_scaledMap;

		bool m_init; 
};

#endif 