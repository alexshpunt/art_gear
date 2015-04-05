#include "AGIntersectPlane.h"

#include "AGArrow.h"

#include "Engine/Managers/AGLogger.h"
#include "Managers/AGEStateManager.h"
#include "Engine/Graphics/Interfaces/AGSurface.h"
#include "Engine/Graphics/Objects/AGCamera.h"

AGIntersectPlane::AGIntersectPlane( PlaneAxis axis )
{
	m_axis = axis; 

	AGColor red  ( 0.798431372, 0.0f, 0.0f, 1.0f );
	AGColor green( 0.0f, 0.6117647058, 0.0f, 1.0f );
	AGColor blue ( 0.0f, 0.0f, 0.76470588233, 1.0f );

	AGColor firstColor;
	AGColor secondColor;
	
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

	AGColor yellow( red.getRedF(), green.getGreenF(), 0.0f, 0.4f );

	AGColorVertex vertices[] = 
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
		m_vertices.push_back( vertices[ 8 + i ].pos ); 
	}

	m_vertexBuffer = new AGBuffer< AGColorVertex >( vector< AGColorVertex >( vertices, vertices + 14 ), AGBufferType::Vertex );
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
			setLocalAngle( AGDegrees( -90.0f ), AGDegrees( 0.0f ), AGDegrees( -90.0f  ) );
		break;
		case YZ_AXIS:
			setLocalAngle( AGDegrees( 0.0f ), AGDegrees( -90.0f ), AGDegrees( 0.0f ) );
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

float AGIntersectPlane::intersect(const AGVec3& rayOrigin, const AGVec3& rayDir)
{
	float retDist = -1.0f; 

	for( int i = 0; i < 3; i++ )
	{
		AGVec3 v1 = m_vertices[ i ]; 
		AGVec3 v2 = m_vertices[ i + 1 ];
		AGVec3 v3 = m_vertices[ i + 2 ]; 

		AGMath::IntersectResult res = AGMath::intersectTriangle( rayOrigin, rayDir, AGMath::Triangle( v1, v2, v3 ), false );

		if( res.hit )
		{
			if( retDist < 0.0f )
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

