#include "AGMesh.h"

#include <fstream>

#include "Managers/AGLogger.h"
#include "AGMaterial.h"
#include "AGBoundingBox.h"
#include "Graphics/Interfaces/AGSurface.h"
#include "AGCamera.h"

#include "Engine/Graphics/Objects/AGShader.h"
#include <Engine/Graphics/Objects/AGBuffer.h>

#include "Engine/Managers/AGResourceManager.h"

class AGSubMesh
{
	public:
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

AGSubMesh::AGSubMesh( AGMesh* mesh ) : m_mesh( mesh )
{

}

AGSubMesh::~AGSubMesh()
{

}

void AGSubMesh::loadFrom( ifstream& in )
{
	#define READ( a ) in.read( (char*)&a, sizeof( a ) )

	int nVertices; 
	READ( nVertices );

	for( int i = 0; i < nVertices; i++ )
	{
		AGVertex vertex; 

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

	m_vertexBufffer = new AGBuffer< AGVertex >( m_vertices, AGBufferType::Vertex );
	m_indexBuffer = new AGBuffer< int >( m_indices, AGBufferType::Index );

	m_material = new AGMaterial; 
	m_material->loadFrom( in );
}

void AGSubMesh::draw( AGSurface* surface )
{
	ID3D10Device* device = surface->getDevice();

	assert( m_vertexBufffer );
	assert( m_indexBuffer );

	m_vertexBufffer->apply( surface );
	m_indexBuffer->apply( surface );

	assert( m_material );
	AGShader* shader = m_material->getShader();
	assert( shader );
	m_material->apply(); 
	 
	shader->setWorldMatrix( m_mesh->getResultMatrix() );
	shader->apply( surface );

	AGRasterizeState* state = AGGraphics::getInstance().getRasterizeState( surface->getDevice() ); 

	if( surface->getSurfaceMode() == AGSurface::EdgedFaces )
	{
		shader->applyNextPass();
		device->RSSetState( state->solid );
		device->DrawIndexed( m_indices.size(), 0, 0 );	

		shader->applyNextPass();
		device->RSSetState( state->wireframe);
		device->DrawIndexed( m_indices.size(), 0, 0 );
	}
	else
	{
		if( surface->getSurfaceMode() == AGSurface::Wireframe )
		{
			shader->applyNextPass(); 
			shader->applyNextPass();
			device->RSSetState( state->wireframe );
			device->DrawIndexed( m_indices.size(), 0, 0 );	
		} 
		else 
		{
			shader->applyNextPass();
			device->RSSetState( state->solid ); 
			device->DrawIndexed( m_indices.size(), 0, 0 );	
		}
	}	

	device->RSSetState( state->solid );
}

float AGSubMesh::intersect(const AGVec3& rayOrigin, const AGVec3& rayDir)
{
	float retDist = -1.0f;
	int nIndices = m_indices.size() - 2;  
	for( int i = 0; i < nIndices; i++ )
	{
		AGVec3 v1 = m_vertices[ m_indices[ i ] ].pos;
		AGVec3 v2 = m_vertices[ m_indices[ i + 1 ] ].pos;
		AGVec3 v3 = m_vertices[ m_indices[ i + 2 ] ].pos;

		AGMath::IntersectResult res = AGMath::intersectTriangle( rayOrigin, rayDir, AGMath::Triangle( v1, v2, v3 ) ); 
		if( res.hit )
		{
			if( retDist < 0 )
			{
				retDist = res.distance; 
			}
			else 
			{
				retDist = min( retDist, res.distance ); 
			}
		}
	}
	return retDist; 
}


AGMesh::AGMesh(const std::string &fileName)
{
	m_isSelected = true; 

	std::string fullPath = "data/meshes/";
	fullPath += fileName; 

	ifstream in( fullPath, ios::binary );
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
		subMesh->loadFrom( in );
		m_subMeshes.push_back( subMesh );
	}
	AGVec3 v1;
	AGVec3 v2; 

	READ( v1.x );
	READ( v1.y );
	READ( v1.z );
	READ( v2.x );
	READ( v2.y );
	READ( v2.z );

	m_boundingBox = new AGBoxShape( v1, v2 );
}

AGMesh::~AGMesh()
{
	//m_subMeshes.clear(); 
	delete m_boundingBox;
}

void AGMesh::draw( AGSurface* surface )
{
	ID3D10Device* device = surface->getDevice();
	device->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

	for( AGSubMesh* subMesh : m_subMeshes )
	{
		subMesh->draw( surface ); 
	}
	m_boundingBox->setLocalMatrix( getResultMatrix() );
}	

AGBoxShape* AGMesh::getBoundingBox() const
{
	return m_boundingBox; 
}

void AGMesh::setSelected(bool value)
{
	m_isSelected = value; 
}

bool AGMesh::isSelected() const
{
	return m_isSelected;
}

float AGMesh::intersect( const AGVec3& rayOrigin, const AGVec3& rayDir )
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

unsigned int AGMesh::getType() const
{
	return AGResourceManager::Mesh; 
}
