#ifndef AGDX10_MESH_H
#define AGDX10_MESH_H

#include <map>
#include <vector>
#include <fstream>

#include <d3dx10.h>
#include <d3d10.h>
#include "AGDX10Material.h"
#include "Manipulators/AGDX10Arrow.h"
#include "Math/AGMath.h"

using namespace std;

class AGSubMesh;
class AGDX10Camera; 
class AGDX10BoundingBox;

struct AGDX10Vertex 
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 normal;
	D3DXVECTOR3 binormal;
	D3DXVECTOR3 tangent; 
	D3DXVECTOR3 uv; 
};

class AGDX10Mesh
{
	public:
		AGDX10Mesh();
		~AGDX10Mesh();

		void setPos( D3DXVECTOR3 pos );
		void setPos( float x, float y, float z );
		D3DXVECTOR3 getPos() const;

		void setAngle( D3DXVECTOR3 angle );
		void setAngle( float x, float y, float z );
		D3DXVECTOR3 getAngle() const; 

		void setScale( D3DXVECTOR3 scale );
		void setScale( float x, float y, float z ); 
		D3DXVECTOR3 getScale() const; 

		void loadFrom( const string &fileName, ID3D10Device* device );
		void draw( ID3D10Device* device, AGDX10Camera* camera ); 
		D3DXMATRIX getWorldMatrix(); 

		void setSelected( bool value );
		bool isSelected() const; 

		float intersect( D3DXVECTOR3 rayOrigin, D3DXVECTOR3 rayDir );
		AGDX10BoundingBox* getBoundingBox() const; 
	private:
		vector< AGSubMesh* > m_subMeshes; 

		AGDX10BoundingBox* m_boundingBox; 

		bool m_isSelected; 

		D3DXVECTOR3 m_pos;
		D3DXVECTOR3 m_angle;
		D3DXVECTOR3 m_scale; 

		D3DXMATRIX m_translMatrix;
		D3DXMATRIX m_rotMatrix;
		D3DXMATRIX m_scaleMatrix; 

		D3DXMATRIX m_worldMatrix; 

		AGDX10Arrow* m_xArrow; 
		AGDX10Arrow* m_yArrow; 
		AGDX10Arrow* m_zArrow; 
};

#endif 