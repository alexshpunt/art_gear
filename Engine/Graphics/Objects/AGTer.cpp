#include "AGTer.h"

#include "Engine/Managers/AGResourceManager.h"

#include <fstream>

AGTer::AGTer()
{
	std::string fullPath = "data/meshes/terrain.agmsh";

	ifstream in( fullPath, ios::binary );
#define READ( a ) in.read( (char*)&a, sizeof( a ) )

	char header[ 6];
	in.read( header, 5 );
	header[ 5 ] = '\0';

	if( strcmp( header, "AGMSH" ) != 0 )
	{
		return; 
	}

	int nSubMeshes;
	READ( nSubMeshes );
	if( nSubMeshes == 0 )
	{
		AGError() << "There are 0 sub meshes in "; 
		return; 
	}

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

	m_vbo = new AGBuffer< AGVertex >( m_vertices, AGBufferType::Vertex );
	m_ibo = new AGBuffer< int >( m_indices, AGBufferType::Index );

	m_material = new AGMaterial; 
	m_material->loadFrom( in );
	delete m_material; 

	AGVec3 v1;
	AGVec3 v2; 

	READ( v1.x );
	READ( v1.y );
	READ( v1.z );
	READ( v2.x );
	READ( v2.y );
	READ( v2.z );

	m_shader = AGResourceManager::getInstance().getShader( L"terrain" );

	m_heightSlot = m_difSlot = 0; 

	m_height = new AGTexture2D( L"data/textures/grass1.png" ); 
	m_dif = new AGTexture2D( L"data/textures/dif.png" );
	m_heightSlot = m_shader->addNewTextureVar( "txHeight" );
}

AGTer::~AGTer()
{

}

void AGTer::draw(AGSurface* surface)
{
	ID3D10Device* device = surface->getDevice();

	assert( m_vbo );
	assert( m_ibo );

	m_vbo->apply( surface );
	m_ibo->apply( surface );

	m_shader->setMap( m_heightSlot, m_height, surface );
	m_shader->setMap( 1, m_dif, surface );

	m_shader->apply( surface );
	
	AGRasterizeState* state = AGGraphics::getInstance().getRasterizeState( surface->getDevice() ); 

	m_shader->applyNextPass();
	device->RSSetState( state->solid ); 
	device->DrawIndexed( m_indices.size(), 0, 0 );	

	device->RSSetState( state->solid );
}

