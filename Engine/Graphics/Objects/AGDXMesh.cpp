#include "AGDXMesh.h"

#include <fstream>

#include "Managers/AGLogger.h"
#include "AGDXMaterial.h"
#include "AGDXBoundingBox.h"
#include "Graphics/Interfaces/AGSurface.h"
#include "AGDXCamera.h"

class AGSubMesh
{
	public:
		AGSubMesh( AGDXMesh* mesh );
		~AGSubMesh();

		void loadFrom( ifstream& in, ID3D10Device* device );
		void draw( AGDXSurface* surface ); 
		float intersect( D3DXVECTOR3 rayOrigin, D3DXVECTOR3 rayDir );
	private:
		AGDXMesh* m_mesh;
		vector< AGDXVertex > m_vertices; 
		vector< int > m_indices; 
		AGDXMaterial* m_material; 

		ID3D10Buffer* m_vertexBuffer; 
		ID3D10Buffer* m_indexBuffer; 
};

AGSubMesh::AGSubMesh( AGDXMesh* mesh ) : m_mesh( mesh )
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
		AGDXVertex vertex; 

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
	buffDesc.ByteWidth = sizeof( AGDXVertex ) * m_vertices.size(); 
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

	m_material = new AGDXMaterial; 
	m_material->loadFrom( in, device );
}

void AGSubMesh::draw( AGDXSurface* surface )
{
	UINT stride = sizeof( AGDXVertex );
	UINT offset = 0; 
	AGDXCamera* camera = surface->getCamera();
	ID3D10Device* device = surface->getDevice();
	device->IASetVertexBuffers( 0, 1, &m_vertexBuffer, &stride, &offset );
	device->IASetIndexBuffer( m_indexBuffer, DXGI_FORMAT_R32_UINT, 0 );
	m_material->setWorldMatrix( m_mesh->getLocalMatrix() );
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


AGDXMesh::AGDXMesh() : AGDXMovable()
{
	m_isSelected = false; 
}

AGDXMesh::~AGDXMesh()
{

}

void AGDXMesh::loadFrom( const string &fileName, ID3D10Device* device )
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

	m_boundingBox = new AGDXBoundingBox( v1, v2, device );

	D3D10_DEPTH_STENCIL_DESC dsDesc; 

	dsDesc.DepthEnable = true; 
	dsDesc.DepthFunc = D3D10_COMPARISON_LESS; 
	dsDesc.DepthWriteMask = D3D10_DEPTH_WRITE_MASK_ALL; 

	dsDesc.StencilEnable = false;
	dsDesc.StencilReadMask = D3D10_DEFAULT_STENCIL_READ_MASK;
	dsDesc.StencilWriteMask = D3D10_DEFAULT_STENCIL_WRITE_MASK;

	// Stencil operations if pixel is front-facing
	dsDesc.FrontFace.StencilFailOp = D3D10_STENCIL_OP_KEEP;
	dsDesc.FrontFace.StencilDepthFailOp = D3D10_STENCIL_OP_INCR;
	dsDesc.FrontFace.StencilPassOp = D3D10_STENCIL_OP_KEEP;
	dsDesc.FrontFace.StencilFunc = D3D10_COMPARISON_ALWAYS;

	// Stencil operations if pixel is back-facing
	dsDesc.BackFace.StencilFailOp = D3D10_STENCIL_OP_KEEP;
	dsDesc.BackFace.StencilDepthFailOp = D3D10_STENCIL_OP_DECR;
	dsDesc.BackFace.StencilPassOp = D3D10_STENCIL_OP_KEEP;
	dsDesc.BackFace.StencilFunc = D3D10_COMPARISON_ALWAYS;

	device->CreateDepthStencilState( &dsDesc, &m_depthState );
}

void AGDXMesh::draw( AGDXSurface* surface )
{
	ID3D10Device* device = surface->getDevice();

	device->OMSetDepthStencilState( m_depthState, 0 );
	for( AGSubMesh* subMesh : m_subMeshes )
	{
		device->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
		subMesh->draw( surface ); 
	}
	m_boundingBox->setLocalMatrix( getLocalMatrix() );
}	

AGDXBoundingBox* AGDXMesh::getBoundingBox() const
{
	return m_boundingBox; 
}

void AGDXMesh::setSelected(bool value)
{
	m_isSelected = value; 
}

bool AGDXMesh::isSelected() const
{
	return m_isSelected;
}

float AGDXMesh::intersect( D3DXVECTOR3 rayOrigin, D3DXVECTOR3 rayDir )
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
