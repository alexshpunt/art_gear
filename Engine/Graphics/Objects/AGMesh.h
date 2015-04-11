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

#include "Engine/Graphics/Objects/AGBuffer.h"

using namespace std;

class AGSubMesh;
class AGSurface; 
class AGBoundingBox;
class AGResourceManager; 
class AGResourceManagerStrategy;
class AGMaterial;

class AGMeshLoadingData
{
	public:
		vector< AGSubMesh* > subMeshes; 
		AGBoxShape* boundingBox; 
};

class AGMesh : public AGMovable, public AGResource
{
	friend class AGResourceManager; 
	friend class AGResourceManagerStrategy; 
	public:
		AGMesh(); 
		AGMesh( const std::string &fileName );
		~AGMesh();

		void initFrom( AGMeshLoadingData* data );

		unsigned int getType() const; 

		void draw( AGSurface* surface ); 

		void setSelected( bool value );
		bool isSelected() const; 

		float intersect( const AGVec3& rayOrigin, const AGVec3& rayDir );

		AGBoxShape* getBoundingBox() const; 
	private:
		vector< AGSubMesh* > m_subMeshes; 

		AGBoxShape* m_boundingBox; 

		bool m_isSelected; 

		ID3D10RasterizerState* m_fillState;
		ID3D10RasterizerState* m_edgedState; 

		ID3D10DepthStencilState* m_depthState; 
};

class AGSubMeshLoadingData
{
	public:
		vector< AGVertex > vertices; 
		vector< int > indices; 
		AGMaterial* material; 

		AGBuffer< AGVertex >* vertexBufffer; 
		AGBuffer< int >* indexBuffer; 
};

class AGSubMesh
{
	public:
		AGSubMesh( AGMesh* mesh, AGSubMeshLoadingData* data );
		AGSubMesh( AGMesh* mesh );
		~AGSubMesh();

		void loadFrom( ifstream& in );
		void draw( AGSurface* surface ); 
		float intersect( const AGVec3& rayOrigin, const AGVec3& rayDir );
	private:
		AGMesh* m_mesh;
		vector< AGVertex > m_vertices; 
		vector< int > m_indices; 
		AGMaterial* m_material; 

		AGBuffer< AGVertex >* m_vertexBufffer; 
		AGBuffer< int >* m_indexBuffer; 
};

#endif 