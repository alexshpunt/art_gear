#include "AGIntersectTriangle.h"

#include <list>

#include "Engine/Managers/AGLogger.h"
#include "Engine/Graphics/Interfaces/AGSurface.h"
#include "Engine/Graphics/Objects/AGCamera.h"

AGIntersectTriangle::AGIntersectTriangle( TriangleAxis axis)
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
			firstColor = blue;
			secondColor = red;
		break;
		case YZ_AXIS:
			firstColor = green;
			secondColor = blue; 
		break;
	}

	float len = 0.15f;

	AGColor yellowTransp( red.getRedF(), green.getGreenF(), 0.0f, 0.4f );
	AGColor yellow( 1.0f, 1.0f, 0.0f, 1.f );

	if( m_axis == XYZ_AXIS )
	{
		len = len / 1.5f; 
		AGColorVertex vertices[] = 
		{
			//Selected tri
			//XY Selected
			{ AGVec3( 0.0f, len, 0.0f  ), yellow },                //0
			{ AGVec3( len, 0.0f, 0.0f  ), yellow },                //1

			{ AGVec3( 0.0f, len, 0.0f  ), yellow },                //2
			{ AGVec3( len / 2.0f , len / 2.0f, 0.0f  ), yellow },  //3

			//XZ Selected
			{ AGVec3( 0.0f, 0.0f, len ), yellow },                 //4
			{ AGVec3( len, 0.0f, 0.0f  ), yellow },                //5

			{ AGVec3( 0.0f, 0.0f,  len  ), yellow },               //6
			{ AGVec3( len / 2.0f , 0.0f , len / 2.0f  ), yellow }, //7

			//YZ Selected
			{ AGVec3( 0.0f, 0.0f, len ), yellow },                 //8
			{ AGVec3( 0.0f, len, 0.0f  ), yellow },                //9

			{ AGVec3( 0.0f, 0.0f,  len  ), yellow },               //10
			{ AGVec3( 0.0f, len / 2.0f, len / 2.0f  ), yellow },   //11

			//X Selected
			{ AGVec3( 0.0f, 0.0f, 0.0f  ), yellow },         //12
			{ AGVec3( len, 0.0f, 0.0f  ), yellow },        //13
			//Y Selected
			{ AGVec3( 0.0f, 0.0f, 0.0f  ), yellow },         //14
			{ AGVec3( 0.0f, len, 0.0f  ), yellow },        //15
			//Z Selected
			{ AGVec3( 0.0f, 0.0f, 0.0f  ), yellow },         //16
			{ AGVec3( 0.0f, 0.0f, len  ), yellow },        //17

			//XY Selected
			{ AGVec3 ( 0.0f, 0.0f, 0.0f ), yellowTransp },          //18
			{ AGVec3( 0.0f, len, 0.0f  ), yellowTransp },          //19
			{ AGVec3( len, 0.0f, 0.0f  ), yellowTransp },          //20

			//YZ Selected
			{ AGVec3 ( 0.0f, 0.0f, 0.0f ), yellowTransp },          //21
			{ AGVec3( 0.0f, len, 0.0f  ), yellowTransp },          //22
			{ AGVec3( 0.0f, 0.0f, len  ), yellowTransp },          //23

			//XZ Selected
			{ AGVec3 ( 0.0f, 0.0f, 0.0f ), yellowTransp },          //24
			{ AGVec3( 0.0f, 0.0f , len  ), yellowTransp },          //25
			{ AGVec3( len, 0.0f, 0.0f  ), yellowTransp },          //26

			//XYZ Selected
			{ AGVec3 ( 0.0f, 0.0f, len ), yellowTransp },          //27
			{ AGVec3( 0.0f, len, 0.0f  ), yellowTransp },          //28
			{ AGVec3( len, 0.0f, 0.0f  ), yellowTransp },          //29
		};

		for (int i = 0; i < 9; i++)
		{
			m_vertices.push_back( vertices[ 18+i ].pos ); 
		}
		
		m_vertexBuffer = new AGBuffer< AGColorVertex >( 
			vector< AGColorVertex >( vertices, vertices + 30 ), AGBufferType::Vertex );
	}
	else 
	{
		AGColorVertex vertices[] = 
		{
			//Unselected tri
			{ AGVec3 ( 0.0f, len / 1.5, 0.0f ), firstColor },                         //0
			{ AGVec3 ( (len / 1.5f) / 2.0f, (len / 1.5) / 2.0f, 0.0f ), firstColor }, //1

			{ AGVec3 ( (len / 1.5f) / 2.0f, (len / 1.5) / 2.0f, 0.0f ), secondColor },//2
			{ AGVec3( len / 1.5f, 0.0f, 0.0f  ), secondColor },                       //3

			{ AGVec3( 0.0f, len, 0.0f  ), firstColor },                               //4
			{ AGVec3( len / 2.0f, len / 2.0f, 0.0f  ), firstColor },                  //5

			{ AGVec3( len / 2.0f, len / 2.0f, 0.0f  ), secondColor },                 //6
			{ AGVec3( len, 0.0f, 0.0f  ), secondColor },                              //7

			//Selected Tri
			{ AGVec3 ( 0.0f, len / 1.5, 0.0f ), yellow },  //8
			{ AGVec3( len / 1.5f, 0.0f, 0.0f  ), yellow }, //9

			{ AGVec3( len, 0.0f, 0.0f  ), yellow },        //10
			{ AGVec3( 0.0f, len, 0.0f  ), yellow },        //11

			//Selected Rect
			{ AGVec3 ( 0.0f, len / 1.5, 0.0f ), yellowTransp },  //12
			{ AGVec3( len / 1.5f, 0.0f, 0.0f  ), yellowTransp }, //13
			{ AGVec3( 0.0f, len, 0.0f  ), yellowTransp },        //14

			{ AGVec3( len / 1.5f, 0.0f, 0.0f  ), yellowTransp }, //15
			{ AGVec3( len, 0.0f, 0.0f  ), yellowTransp },        //16
			{ AGVec3( 0.0f, len, 0.0f  ), yellowTransp },        //17
		};

		for (int i = 0; i < 6; i++)
		{
			m_vertices.push_back( vertices[ 12+i ].pos ); 
		}

		m_vertexBuffer = new AGBuffer< AGColorVertex >( 
			vector< AGColorVertex >( vertices, vertices + 18 ), AGBufferType::Vertex );	
	}
}

AGIntersectTriangle::~AGIntersectTriangle()
{

}

void AGIntersectTriangle::setArrows(AGArrow* arrow1, AGArrow* arrow2)
{

}

void AGIntersectTriangle::draw( AGSurface* surface )
{
	AGCamera* camera = surface->getCamera(); 
	ID3D10Device* device = surface->getDevice(); 

	updatePos( camera );

	AGVec3 xAxis( 1.0f, 0.0f, 0.0f );
	AGVec3 zAxis( 0.0f, 0.0f, 1.0f );
	AGVec3 yAxis( 0.0f, 1.0f, 0.0f );

	AGEStateManager::CoordSystem system = AGEStateManager::getInstance().getCoordSystem(); 

	if( system == AGEStateManager::Local )
	{
		AGMatrix rotMatrix = getWorldRotMatrix(); 

		xAxis *= rotMatrix;
		yAxis *= rotMatrix;
		zAxis *= rotMatrix; 
	}

	AGVec3 camEye = camera->getPos() - m_beginPos; 

	float cosX = AGVec3::dot( xAxis, camEye );
	float cosY = AGVec3::dot( yAxis, camEye );
	float cosZ = AGVec3::dot( zAxis, camEye );

	if( m_axis == XY_AXIS )
	{
		cosX = cosX >= 0.0f ? 0.0f : -1.0f;
		cosY = cosY >= 0.0f ? 0.0f : -1.0f;

		setLocalAngle( AGDegrees( 180.0f * cosY ), AGDegrees( 180.0f * cosX ), AGDegrees( 0.0f  ) );
	}
	else if( m_axis == XZ_AXIS )
	{
		cosX = cosX >= 0.0f ? 0.0f : -1.0f;
		cosZ = cosZ > 0.0f ? 1.0f : cosZ < 0.0f ? -1.0f : 0.0f;

		setLocalAngle(AGDegrees( ( cosX < 0.0f ? -1.0f : 1.0f ) * 90.0f * cosZ  ), AGDegrees( 180.0f * cosX ), AGDegrees( 0.0f ) );
	}
	else if( m_axis == YZ_AXIS )
	{
		cosY = cosY >= 0.0f ? 0.0f : -1.0f;
		cosZ = cosZ > 0.0f ? 1.0f : cosZ < 0.0f ? -1.0f : 0.0f;

		setLocalAngle( AGDegrees( -180.0f * cosY ), AGDegrees( -90.0f * cosZ ), AGDegrees( 0.0f ) );
	}	
	else if( m_axis == XYZ_AXIS )
	{
		cosX = cosX > 0.0f ? 1.0f : cosX < 0.0f ? -1.0f : 0.0f;
		cosY = cosY >= 0.0f ? 0.0f : -1.0f;
		cosZ = cosZ > 0.0f ? 1.0f : cosZ < 0.0f ? -1.0f : 0.0f;

		if( cosX * cosZ > 0.0f )
		{
			cosX = cosX > 0.0f ? 0.0f : cosX; 
			cosZ = cosZ > 0.0f ? 0.0f : cosZ; 

			setLocalAngle( AGDegrees( -90.0f * cosY ), AGDegrees( 90.0f * ( cosX + cosZ ) ), AGDegrees( 0.0f ) );	
		}
		else if( cosX * cosZ < 0.0f )
		{
			setLocalAngle( AGDegrees( -90.0f * cosY ), AGDegrees( 90.0f * cosX ), AGDegrees( 0.0f ) );
		}
	}

	setupBuffers( surface );

	while( m_shader->applyNextPass() )
	{
		if( m_axis == XYZ_AXIS )
		{
			if( m_isSelected )
			{
				device->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_LINELIST );
				device->Draw( 18, 0 );
				device->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
				device->Draw( 9, 18 );
			}
		}
		else
		{
			if( !m_isSelected )
			{
				device->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_LINELIST );
				device->Draw( 8, 0 );
			}
			else
			{
				device->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_LINELIST );
				device->Draw( 8, 0 );
				device->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
				device->Draw( 6, 12 );
			}
		}
	}
}

float AGIntersectTriangle::intersect( const AGVec3& rayOrigin, const AGVec3& rayDir )
{
	float retDist = -1.0f;
	int high = ( m_axis == XYZ_AXIS ) ? 3 : 2; 
	for( int i = 0; i < high; i++ )
	{
		AGVec3 v1 = m_vertices[ 3*i ];
		AGVec3 v2 = m_vertices[ 3*i + 1 ];
		AGVec3 v3 = m_vertices[ 3*i + 2 ];

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

AGVec3 AGIntersectTriangle::getAxis()
{
	if( m_axis == XY_AXIS )
		return AGVec3( 1.0f, 1.0f, 0.0f );
	if( m_axis == XZ_AXIS )
		return AGVec3( 1.0f, 0.0f, 1.0f );
	if( m_axis == YZ_AXIS )
		return AGVec3( 0.0f, 1.0f, 1.0f );
	if( m_axis == XYZ_AXIS )
		return AGVec3( 1.0f, 1.0f, 1.0f ); 
	return AGVec3( 0.0f, 0.0f, 0.0f );
}

