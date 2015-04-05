#ifndef AG_MESH_H
#define AG_MESH_H

#include <list>
#include <vector>

#include <d3dx10.h>
#include <d3d10.h>

#include "Graphics/AGGraphics.h"

#include "Graphics/Objects/Shapes/AGBoxShape.h"

#include "Engine/Interfaces/AGResource.h"
#include "Engine/Interfaces/AGMovable.h"

using namespace std;

class AGSubMesh;
class AGSurface; 
class AGBoundingBox;
class AGResourceManager; 

class AGMesh : public AGMovable, public AGResource
{
	friend class AGResourceManager; 
	public:
		unsigned int getType() const; 

		void draw( AGSurface* surface ); 

		void setSelected( bool value );
		bool isSelected() const; 

		float intersect( const AGVec3& rayOrigin, const AGVec3& rayDir );

		AGBoxShape* getBoundingBox() const; 
	private:
		AGMesh( const std::string &fileName );
		~AGMesh();

		vector< AGSubMesh* > m_subMeshes; 

		AGBoxShape* m_boundingBox; 

		bool m_isSelected; 

		ID3D10RasterizerState* m_fillState;
		ID3D10RasterizerState* m_edgedState; 

		ID3D10DepthStencilState* m_depthState; 
};

#endif 