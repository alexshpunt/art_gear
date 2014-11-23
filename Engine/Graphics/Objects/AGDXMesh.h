#ifndef AGDX_MESH_H
#define AGDX_MESH_H

#include <vector>

#include <d3dx10.h>
#include <d3d10.h>

#include "Graphics/Interfaces/AGDXMovable.h"

using namespace std;

class AGSubMesh;
class AGDXSurface; 
class AGDXBoundingBox;

struct AGDXVertex 
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 normal;
	D3DXVECTOR3 binormal;
	D3DXVECTOR3 tangent; 
	D3DXVECTOR3 uv; 
};

struct AGDXIntersectedVertex
{
	D3DXVECTOR3 v1;
	D3DXVECTOR3 v2;
	D3DXVECTOR3 v3;
	float dist; 
};

class AGDXMesh : public AGDXMovable
{
	public:
		AGDXMesh();
		~AGDXMesh();

		void loadFrom( const string &fileName, ID3D10Device* device );
		void draw( AGDXSurface* surface ); 

		void setSelected( bool value );
		bool isSelected() const; 

		float intersect( D3DXVECTOR3 rayOrigin, D3DXVECTOR3 rayDir );

		AGDXBoundingBox* getBoundingBox() const; 
	private:
		vector< AGSubMesh* > m_subMeshes; 

		AGDXBoundingBox* m_boundingBox; 

		bool m_isSelected; 

		ID3D10DepthStencilState* m_depthState; 
};

#endif 