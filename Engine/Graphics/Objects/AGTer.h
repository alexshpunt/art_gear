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

#include "Engine/Graphics/Objects/Shapes/AGSphereShape.h"

class AGTer : public AGClickable
{
	public:
		AGTer()
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

			m_height = new AGTexture2D( L"grass1.png" ); 
			m_dif = new AGTexture2D( L"grass2.png" );
			m_rock = new AGTexture2D( L"rock.jpg" );
			m_difSlot = m_shader->addNewTextureVar( "txDiff" );
			m_heightSlot = m_shader->addNewTextureVar( "txHeight" );
			m_rockSlot = m_shader->addNewTextureVar( "txRock" ); 
		}
		~AGTer(){}

		void draw( AGSurface* surface )
		{
			ID3D10Device* device = surface->getDevice();

			assert( m_vbo );
			assert( m_ibo );

			m_vbo->apply( surface );
			m_ibo->apply( surface );

			m_shader->setMap( m_heightSlot, m_height, surface );
			m_shader->setMap( m_difSlot, m_dif, surface );
			m_shader->setMap( m_rockSlot, m_rock, surface );

			m_shader->setWorldMatrix( AGMatrix() );
			m_shader->apply( surface );

			device->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
			m_shader->applyNextPass();
			device->DrawIndexed( m_indices.size(), 0, 0 );	
		}

		bool mouseClickEvent( AGMouseButton button, AGSurface* surface ) override
		{	
			return false; 
		}

		bool mouseMoveEvent( AGSurface* surface ) override
		{
			calculateRays( surface, AGMatrix() );
			return intersect( m_rayOrigin, m_rayDir ) > 0.0f; 
		}

		AGPoint2 findVertex( int fromX, int toX, int fromY, int toY, AGVec3 pos )
		{
			int centerX = (toX - fromX)/2;
			int centerY = (toY - fromY)/2; 
			AGVertex vertex = m_vertexMap.at( centerY ).at( centerX );

			float len = (vertex.pos - pos).getLength();
			if( len < 0.01 )
			{
				return AGPoint2( centerX, centerY );
			}

			if( vertex.pos.x < centerX )
			{
				toX = centerX; 
			}
			else if( vertex.pos.x > centerX )
			{
				fromX = centerX; 
			}
			if( vertex.pos.y < centerY )
			{
				toY = centerY; 
			}
			else if( vertex.pos.y > centerY )
			{
				fromY = centerY; 
			}
			

			return findVertex( fromX, toX, fromY, toY, pos );
		}

		float intersect( const AGVec3& rayOrigin, const AGVec3& rayDir ) override
		{
			//AGPoint2 vertexIndex = findVertex( 0, m_vertexMap.size(), 0, m_vertexMap.size(), rayOrigin );
			return -1.f;
		}

	protected:
		AGBuffer< int >* m_ibo;
		AGBuffer< AGVertex >* m_vbo;

		std::vector< AGVertex > m_vertices; 

		std::vector< std::vector< AGVertex > > m_vertexMap; 

		AGShader* m_shader; 
		AGMaterial* m_material; 
		int m_heightSlot;
		int m_difSlot; 
		int m_rockSlot; 
		AGTexture2D* m_height;
		AGTexture2D* m_dif; 
		AGTexture2D* m_rock;
};

#endif 