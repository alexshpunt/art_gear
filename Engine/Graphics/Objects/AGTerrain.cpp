#include "AGTerrain.h"

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
	int sqrnVertices = sqrt( nVertices );
	AGDebug() << nVertices << " " << sqrnVertices;

	std::vector< AGVertex > verticesForMap; 

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
		verticesForMap.push_back( vertex );
		m_vertices.push_back( vertex );
		if( i != 0 && i % sqrnVertices == 0 )
		{
			m_vertexMap.push_back( verticesForMap );
			verticesForMap.clear(); 
		}
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

	D3D10_TEXTURE2D_DESC txDesc; 
	ZeroMemory( &txDesc, sizeof( txDesc ) );
	txDesc.Width = 256; 
	txDesc.Height = 256; 
	txDesc.ArraySize = txDesc.MipLevels = 1;
	txDesc.Format = DXGI_FORMAT_R8_UNORM;
	txDesc.SampleDesc.Count = 1;
	txDesc.SampleDesc.Quality = 0; 
	txDesc.Usage = D3D10_USAGE_DEFAULT;
	txDesc.BindFlags = D3D10_BIND_SHADER_RESOURCE; 
	txDesc.MiscFlags = D3D10_RESOURCE_MISC_SHARED; 

	unsigned char data[ 256 ][ 256 ];
	for( int i = 0; i < 256; i++ )
	{
		for( int j = 0; j < 256; j++ )
		{
			data[ i ][ j ] = sqrt( i*i + j*j ) * 255; 
		}
	}

	D3D10_SUBRESOURCE_DATA subres; 
	subres.pSysMem = data; 
	subres.SysMemPitch = 8;

	std::list< AGSurface* > surfaces = AGGraphics::getInstance().getSurfaces(); 

	m_txArray = new AGTexture2DArray; 
	m_txArray->append( L"data/textures/grass2.png" );
	m_txArray->append( L"data/textures/grass3.png" );
	m_txArray->append( L"data/textures/rock.jpg" );
	m_txArray->reloadArray();

	m_height = new AGTexture2D( L"t.png" );//( &txDesc, &subres ); 
	m_dif = new AGTexture2D( L"blend.png" );
	m_rock = new AGTexture2D( L"index.png" );
	m_difSlot = m_shader->addNewTextureVar( "txDiff" );
	m_heightSlot = m_shader->addNewTextureVar( "txHeight" );
	m_rockSlot = m_shader->addNewTextureVar( "txRock" ); 
	m_mapsSlot = m_shader->addNewTextureVar( "txMaps" );
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
	m_shader->setMap( m_difSlot, m_dif, surface );
	m_shader->setMap( m_rockSlot, m_rock, surface );
	m_shader->setArray( m_mapsSlot, m_txArray, surface );

	m_shader->setWorldMatrix( AGMatrix() );
	m_shader->apply( surface );

	device->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
	m_shader->applyNextPass();
	device->DrawIndexed( m_indices.size(), 0, 0 );	
}

bool AGTer::mouseClickEvent(AGMouseButton button, AGSurface* surface)
{	
	return false; 
}
