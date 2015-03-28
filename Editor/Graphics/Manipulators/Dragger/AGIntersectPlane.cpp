#include "AGIntersectPlane.h"

#include "AGArrow.h"

#include "Engine/Managers/AGLogger.h"
#include "Managers/AGEStateManager.h"
#include "Engine/Graphics/Interfaces/AGSurface.h"
#include "Engine/Graphics/Objects/AGCamera.h"

AGIntersectPlane::AGIntersectPlane( PlaneAxis axis )
{
	m_axis = axis; 

	D3DXVECTOR4 red  ( 0.798431372, 0.0f, 0.0f, 1.0f );
	D3DXVECTOR4 green( 0.0f, 0.6117647058, 0.0f, 1.0f );
	D3DXVECTOR4 blue ( 0.0f, 0.0f, 0.76470588233, 1.0f );

	D3DXVECTOR4 firstColor;
	D3DXVECTOR4 secondColor;
	
	switch( axis )
	{
		case XY_AXIS:
			firstColor = green;
			secondColor = red; 
		break;
		case XZ_AXIS:
			firstColor = red;
			secondColor = blue;
		break;
		case YZ_AXIS:
			firstColor = green;
			secondColor = blue; 
		break;
	}

	float len = 0.1f;

	D3DXVECTOR4 yellow( red.x, green.y, 0.0f, 0.4f );

	AGPrimitiveVertex vertices[] = 
	{
		//Unselected rect
		{ AGVec3( 0.0f, 0.0f, 0.0f ), firstColor  }, //0
		{ AGVec3( 0.0f, len, 0.0f  ), firstColor  }, //1

		{ AGVec3( 0.0f, len, 0.0f  ), secondColor }, //2
		{ AGVec3( len , len, 0.0f  ), secondColor }, //3
			
		{ AGVec3( len , len, 0.0f  ), firstColor  }, //4
		{ AGVec3( len , 0.0f, 0.0f ), firstColor  }, //5

		{ AGVec3( len , 0.0f, 0.0f ), secondColor }, //6	
		{ AGVec3( 0.0f, 0.0f, 0.0f ), secondColor }, //7	

		//Selected rect
		{ AGVec3( 0.0f, 0.0f, 0.0f ), yellow  }, //8
		{ AGVec3( len, len, 0.0f   ), yellow  }, //9
		{ AGVec3( 0.0f, len, 0.0f  ), yellow  }, //10

		{ AGVec3( len , 0.0f, 0.0f ), yellow  }, //11
		{ AGVec3( len , len, 0.0f  ), yellow  }, //12
		{ AGVec3( 0.0f, 0.0f, 0.0f ), yellow  }, //13	
	};

	for (int i = 0; i < 6; i++)
	{
		m_vertices[ i ] = vertices[ 8 + i ].pos; 
	}

	m_vertexBuffer = new AGBuffer< AGPrimitiveVertex >( vector< AGPrimitiveVertex >( vertices, vertices + 14 ), AGBufferType::Vertex );
}

AGIntersectPlane::~AGIntersectPlane()
{

}

void AGIntersectPlane::draw( AGSurface* surface )
{
	AGCamera* camera = surface->getCamera(); 
	ID3D10Device* device = surface->getDevice(); 

	updatePos( camera );

	switch( m_axis )
	{
		case XZ_AXIS:
			setLocalAngle( D3DXToRadian( -90.0f ), D3DXToRadian( 0.0f ), D3DXToRadian( -90.0f  ) );
		break;
		case YZ_AXIS:
			setLocalAngle( 0.0f, D3DXToRadian( -90.0f ), 0.0f );
		break; 
	}

	setupBuffers( surface );

	while( m_shader->applyNextPass() )
	{
		if( !m_isSelected )
		{
			device->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_LINELIST );
			device->Draw( 2, 2 );
			device->Draw( 2, 4 );
		}
		else
		{
			device->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
			device->Draw( 6, 8 );
		}
	}

	releaseBuffers();
}

float AGIntersectPlane::intersect(AGVec3 rayOrigin, AGVec3 rayDir)
{
	float retDist = -1.0f;
	for( int i = 0; i < 3; i++ )
	{
		AGVec3 vertex1 = m_vertices[ i ];
		AGVec3 vertex2 = m_vertices[ i + 1 ];
		AGVec3 vertex3 = m_vertices[ i + 2 ];

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

AGVec3 AGIntersectPlane::getAxis()
{
	if( m_axis == XY_AXIS )
		return AGVec3( 1.0f, 1.0f, 0.0f );
	if( m_axis == XZ_AXIS )
		return AGVec3( 1.0f, 0.0f, 1.0f );
	if( m_axis == YZ_AXIS )
		return AGVec3( 0.0f, 1.0f, 1.0f );

	return AGVec3( 0.0f, 0.0f, 0.0f );
}

