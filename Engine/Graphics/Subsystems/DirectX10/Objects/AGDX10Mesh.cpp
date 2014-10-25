#include "AGDX10Mesh.h"

#include "Managers/AGLogger.h"
#include "Graphics/Subsystems/DirectX10/AGDX10SubSys.h"
#include "AGDX10BoundingBox.h"
#include "AGDX10Camera.h"

class AGSubMesh
{
	public:
		AGSubMesh( AGDX10Mesh* mesh );
		~AGSubMesh();

		void loadFrom( ifstream& in, ID3D10Device* device );
		void draw( ID3D10Device* device, AGDX10Camera* camera  ); 
		float intersect( D3DXVECTOR3 rayOrigin, D3DXVECTOR3 rayDir );
	private:
		AGDX10Mesh* m_mesh;
		vector< AGDX10Vertex > m_vertices; 
		vector< int > m_indices; 
		AGDX10Material* m_material; 

		ID3D10Buffer* m_vertexBuffer; 
		ID3D10Buffer* m_indexBuffer; 
};

AGSubMesh::AGSubMesh( AGDX10Mesh* mesh ) : m_mesh( mesh )
{

}

AGSubMesh::~AGSubMesh()
{

}

void AGSubMesh::loadFrom( ifstream& in, ID3D10Device* device )
{
	#define READ( a ) in.read( (char*)&a, sizeof( a ) )

	int nVertices; 
	READ( nVertices );

	for( int i = 0; i < nVertices; i++ )
	{
		AGDX10Vertex vertex; 

		READ( vertex.pos.x );
		READ( vertex.pos.y );
		READ( vertex.pos.z );

		READ( vertex.normal.x );
		READ( vertex.normal.y );
		READ( vertex.normal.z );

		READ( vertex.binormal.x );
		READ( vertex.binormal.y );
		READ( vertex.binormal.z );

		READ( vertex.tangent.x );
		READ( vertex.tangent.y );
		READ( vertex.tangent.z );

		READ( vertex.uv.x );
		READ( vertex.uv.y );
		m_vertices.push_back( vertex );
	}

	int nIndices; 
	READ( nIndices );
	for( int i = 0; i < nIndices; i++ )
	{
		int index;
		READ( index ); 
		m_indices.push_back( index );
	}

	D3D10_BUFFER_DESC buffDesc; 

	buffDesc.Usage = D3D10_USAGE_DEFAULT; 
	buffDesc.ByteWidth = sizeof( AGDX10Vertex ) * m_vertices.size(); 
	buffDesc.CPUAccessFlags = 0;
	buffDesc.MiscFlags = 0;
	buffDesc.BindFlags = D3D10_BIND_VERTEX_BUFFER; 

	D3D10_SUBRESOURCE_DATA subresData; 
	subresData.pSysMem = &m_vertices[ 0 ];

	HRESULT hr = device->CreateBuffer( &buffDesc, &subresData, &m_vertexBuffer );

	if( FAILED( hr ) )
	{
		AGError() << "Couldn't create vertex buffer";
		return; 
	}

	buffDesc.ByteWidth = sizeof( int ) * m_indices.size();
	buffDesc.BindFlags = D3D10_BIND_INDEX_BUFFER; 
	subresData.pSysMem = &m_indices[ 0 ];

	hr = device->CreateBuffer( &buffDesc, &subresData, &m_indexBuffer );

	if( FAILED( hr ) )
	{
		AGError() << "Couldn't create index buffer"; 
		return; 
	}

	m_material = new AGDX10Material; 
	m_material->loadFrom( in, device );
}

void AGSubMesh::draw( ID3D10Device* device, AGDX10Camera* camera  )
{
	UINT stride = sizeof( AGDX10Vertex );
	UINT offset = 0; 
	device->IASetVertexBuffers( 0, 1, &m_vertexBuffer, &stride, &offset );
	device->IASetIndexBuffer( m_indexBuffer, DXGI_FORMAT_R32_UINT, 0 );
	m_material->setWorldMatrix( m_mesh->getWorldMatrix() );
	m_material->setViewMatrix( camera->getViewMatrix() );
	m_material->setProjMatrix( camera->getProjMatrix() );
	m_material->apply( device ); 
	device->DrawIndexed( m_indices.size(), 0, 0 );
}

float AGSubMesh::intersect(D3DXVECTOR3 rayOrigin, D3DXVECTOR3 rayDir)
{
	float retDist = -1.0f;
	int nIndices = m_indices.size() - 2;  
	for( int i = 0; i < nIndices; i++ )
	{
		D3DXVECTOR3 vertex1 = m_vertices[ m_indices[ i ] ].pos;
		D3DXVECTOR3 vertex2 = m_vertices[ m_indices[ i + 1 ] ].pos;
		D3DXVECTOR3 vertex3 = m_vertices[ m_indices[ i + 2 ] ].pos;

		float dist, u, v; 

		bool res = D3DXIntersectTri( &vertex1, &vertex2, &vertex3, &rayOrigin, &rayDir, &u, &v, &dist );
		if( res )
		{
			if( retDist < 0 )
			{
				retDist = dist; 
			}
			else 
			{
				retDist = min( retDist, dist );	
			}
		}
	}
	return retDist; 
}


AGDX10Mesh::AGDX10Mesh()
{
	D3DXMatrixIdentity( &m_worldMatrix );

	D3DXMatrixIdentity( &m_translMatrix );
	D3DXMatrixIdentity( &m_rotMatrix );
	D3DXMatrixIdentity( &m_scaleMatrix );

	m_isSelected = false; 
}

AGDX10Mesh::~AGDX10Mesh()
{

}

void AGDX10Mesh::loadFrom( const string &fileName, ID3D10Device* device )
{
	ifstream in( fileName, ios::binary );
	#define READ( a ) in.read( (char*)&a, sizeof( a ) )

	char header[ 6];
	in.read( header, 5 );
	header[ 5 ] = '\0';

	if( strcmp( header, "AGMSH" ) != 0 )
	{
		AGError() << "Couldn't load mesh file: " << fileName; 
		return; 
	}
	
	int nSubMeshes;
	READ( nSubMeshes );
	if( nSubMeshes == 0 )
	{
		AGError() << "There are 0 sub meshes in " << fileName; 
		return; 
	}
	for( int i = 0; i < nSubMeshes; i++ )
	{
		AGSubMesh* subMesh = new AGSubMesh( this ); 
		subMesh->loadFrom( in, device );
		m_subMeshes.push_back( subMesh );
	}
	D3DXVECTOR3 v1;
	D3DXVECTOR3 v2; 

	READ( v1.x );
	READ( v1.y );
	READ( v1.z );
	READ( v2.x );
	READ( v2.y );
	READ( v2.z );

	m_boundingBox = new AGDX10BoundingBox( v1, v2, device );
	m_xArrow = new AGDX10Arrow( device, AGDX10Arrow::X_AXIS );
	m_yArrow = new AGDX10Arrow( device, AGDX10Arrow::Y_AXIS );
	m_zArrow = new AGDX10Arrow( device, AGDX10Arrow::Z_AXIS );
}

D3DXMATRIX AGDX10Mesh::getWorldMatrix()
{
	m_worldMatrix = m_scaleMatrix * m_rotMatrix * m_translMatrix; 
	return m_worldMatrix; 
}

void AGDX10Mesh::draw( ID3D10Device* device, AGDX10Camera* camera  )
{
	for( AGSubMesh* subMesh : m_subMeshes )
	{
		device->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
		subMesh->draw( device, camera ); 
	}
	if( m_isSelected )
		m_boundingBox->draw( device, camera );
	m_xArrow->draw( device, camera ); 
	m_yArrow->draw( device, camera ); 
	m_zArrow->draw( device, camera ); 
}	

void AGDX10Mesh::setPos(D3DXVECTOR3 pos)
{
	m_pos = pos; 
	D3DXMatrixTranslation( &m_translMatrix, m_pos.x, m_pos.y, m_pos.z );
}

void AGDX10Mesh::setPos(float x, float y, float z)
{
	m_pos = D3DXVECTOR3( x, y, z );
	setPos( m_pos );
}

D3DXVECTOR3 AGDX10Mesh::getPos() const
{
	return m_pos; 
}

void AGDX10Mesh::setAngle(D3DXVECTOR3 angles)
{
	m_angle = angles;
	D3DXMatrixRotationYawPitchRoll( &m_rotMatrix, angles.y, angles.x, angles.z );
}

void AGDX10Mesh::setAngle(float x, float y, float z)
{
	m_angle = D3DXVECTOR3( x, y, z );
	setAngle( m_angle );
}

D3DXVECTOR3 AGDX10Mesh::getAngle() const
{
	return m_angle; 
}

void AGDX10Mesh::setScale(D3DXVECTOR3 scale)
{
	m_scale = scale; 
	D3DXMatrixScaling( &m_scaleMatrix, scale.x, scale.y, scale.z );
}

void AGDX10Mesh::setScale(float x, float y, float z)
{
	m_scale = D3DXVECTOR3( x, y, z );
	setScale( m_scale );
}

D3DXVECTOR3 AGDX10Mesh::getScale() const
{
	return m_scale; 
}

AGDX10BoundingBox* AGDX10Mesh::getBoundingBox() const
{
	return m_boundingBox; 
}

void AGDX10Mesh::setSelected(bool value)
{
	m_isSelected = value; 
}

bool AGDX10Mesh::isSelected() const
{
	return m_isSelected;
}

float AGDX10Mesh::intersect( D3DXVECTOR3 rayOrigin, D3DXVECTOR3 rayDir )
{
	float res = -1.0f; 
	for( AGSubMesh* subMesh : m_subMeshes )
	{
		float dist = subMesh->intersect( rayOrigin, rayDir );
		if( res < 0 && dist > 0 )
		{
			res = dist; 
		}
		else if( dist > 0 )
		{
			res = min( dist, res );
		}
	}
	return res; 
}
