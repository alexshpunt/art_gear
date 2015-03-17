#include "AGIntersectTriangle.h"

#include <list>

#include "Engine/Managers/AGLogger.h"
#include "Engine/Graphics/Interfaces/AGSurface.h"
#include "Engine/Graphics/Objects/AGCamera.h"

AGIntersectTriangle::AGIntersectTriangle( TriangleAxis axis)
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
			firstColor = blue;
			secondColor = red;
		break;
		case YZ_AXIS:
			firstColor = green;
			secondColor = blue; 
		break;
	}

	float len = 0.15f;

	D3DXVECTOR4 yellowTransp( red.x, green.y, 0.0f, 0.4f );
	D3DXVECTOR4 yellow( 1.0f, 1.0f, 0.0f, 1.f );

	if( m_axis == XYZ_AXIS )
	{
		len = len / 1.5f; 
		AGPrimitiveVertex vertices[] = 
		{
			//Selected tri
			//XY Selected
			{ D3DXVECTOR3( 0.0f, len, 0.0f  ), yellow },                //0
			{ D3DXVECTOR3( len, 0.0f, 0.0f  ), yellow },                //1

			{ D3DXVECTOR3( 0.0f, len, 0.0f  ), yellow },                //2
			{ D3DXVECTOR3( len / 2.0f , len / 2.0f, 0.0f  ), yellow },  //3

			//XZ Selected
			{ D3DXVECTOR3( 0.0f, 0.0f, len ), yellow },                 //4
			{ D3DXVECTOR3( len, 0.0f, 0.0f  ), yellow },                //5

			{ D3DXVECTOR3( 0.0f, 0.0f,  len  ), yellow },               //6
			{ D3DXVECTOR3( len / 2.0f , 0.0f , len / 2.0f  ), yellow }, //7

			//YZ Selected
			{ D3DXVECTOR3( 0.0f, 0.0f, len ), yellow },                 //8
			{ D3DXVECTOR3( 0.0f, len, 0.0f  ), yellow },                //9

			{ D3DXVECTOR3( 0.0f, 0.0f,  len  ), yellow },               //10
			{ D3DXVECTOR3( 0.0f, len / 2.0f, len / 2.0f  ), yellow },   //11

			//X Selected
			{ D3DXVECTOR3( 0.0f, 0.0f, 0.0f  ), yellow },         //12
			{ D3DXVECTOR3( len, 0.0f, 0.0f  ), yellow },        //13
			//Y Selected
			{ D3DXVECTOR3( 0.0f, 0.0f, 0.0f  ), yellow },         //14
			{ D3DXVECTOR3( 0.0f, len, 0.0f  ), yellow },        //15
			//Z Selected
			{ D3DXVECTOR3( 0.0f, 0.0f, 0.0f  ), yellow },         //16
			{ D3DXVECTOR3( 0.0f, 0.0f, len  ), yellow },        //17

			//XY Selected
			{ D3DXVECTOR3 ( 0.0f, 0.0f, 0.0f ), yellowTransp },          //18
			{ D3DXVECTOR3( 0.0f, len, 0.0f  ), yellowTransp },          //19
			{ D3DXVECTOR3( len, 0.0f, 0.0f  ), yellowTransp },          //20

			//YZ Selected
			{ D3DXVECTOR3 ( 0.0f, 0.0f, 0.0f ), yellowTransp },          //21
			{ D3DXVECTOR3( 0.0f, len, 0.0f  ), yellowTransp },          //22
			{ D3DXVECTOR3( 0.0f, 0.0f, len  ), yellowTransp },          //23

			//XZ Selected
			{ D3DXVECTOR3 ( 0.0f, 0.0f, 0.0f ), yellowTransp },          //24
			{ D3DXVECTOR3( 0.0f, 0.0f , len  ), yellowTransp },          //25
			{ D3DXVECTOR3( len, 0.0f, 0.0f  ), yellowTransp },          //26

			//XYZ Selected
			{ D3DXVECTOR3 ( 0.0f, 0.0f, len ), yellowTransp },          //27
			{ D3DXVECTOR3( 0.0f, len, 0.0f  ), yellowTransp },          //28
			{ D3DXVECTOR3( len, 0.0f, 0.0f  ), yellowTransp },          //29
		};

		for (int i = 0; i < 9; i++)
		{
			m_vertices[ i ] = vertices[ 18+i ].pos; 
		}
		
		m_vertexBuffer = new AGBuffer< AGPrimitiveVertex >( 
			vector< AGPrimitiveVertex >( vertices, vertices + 30 ), AGBufferType::Vertex );
	}
	else 
	{
		AGPrimitiveVertex vertices[] = 
		{
			//Unselected tri
			{ D3DXVECTOR3 ( 0.0f, len / 1.5, 0.0f ), firstColor },                         //0
			{ D3DXVECTOR3 ( (len / 1.5f) / 2.0f, (len / 1.5) / 2.0f, 0.0f ), firstColor }, //1

			{ D3DXVECTOR3 ( (len / 1.5f) / 2.0f, (len / 1.5) / 2.0f, 0.0f ), secondColor },//2
			{ D3DXVECTOR3( len / 1.5f, 0.0f, 0.0f  ), secondColor },                       //3

			{ D3DXVECTOR3( 0.0f, len, 0.0f  ), firstColor },                               //4
			{ D3DXVECTOR3( len / 2.0f, len / 2.0f, 0.0f  ), firstColor },                  //5

			{ D3DXVECTOR3( len / 2.0f, len / 2.0f, 0.0f  ), secondColor },                 //6
			{ D3DXVECTOR3( len, 0.0f, 0.0f  ), secondColor },                              //7

			//Selected Tri
			{ D3DXVECTOR3 ( 0.0f, len / 1.5, 0.0f ), yellow },  //8
			{ D3DXVECTOR3( len / 1.5f, 0.0f, 0.0f  ), yellow }, //9

			{ D3DXVECTOR3( len, 0.0f, 0.0f  ), yellow },        //10
			{ D3DXVECTOR3( 0.0f, len, 0.0f  ), yellow },        //11

			//Selected Rect
			{ D3DXVECTOR3 ( 0.0f, len / 1.5, 0.0f ), yellowTransp },  //12
			{ D3DXVECTOR3( len / 1.5f, 0.0f, 0.0f  ), yellowTransp }, //13
			{ D3DXVECTOR3( 0.0f, len, 0.0f  ), yellowTransp },        //14

			{ D3DXVECTOR3( len / 1.5f, 0.0f, 0.0f  ), yellowTransp }, //15
			{ D3DXVECTOR3( len, 0.0f, 0.0f  ), yellowTransp },        //16
			{ D3DXVECTOR3( 0.0f, len, 0.0f  ), yellowTransp },        //17
		};

		for (int i = 0; i < 6; i++)
		{
			m_vertices[ i ] = vertices[ 12+i ].pos; 
		}

		m_vertexBuffer = new AGBuffer< AGPrimitiveVertex >( 
			vector< AGPrimitiveVertex >( vertices, vertices + 18 ), AGBufferType::Vertex );	
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

	D3DXVECTOR3 xAxis( 1.0f, 0.0f, 0.0f );
	D3DXVECTOR3 zAxis( 0.0f, 0.0f, 1.0f );
	D3DXVECTOR3 yAxis( 0.0f, 1.0f, 0.0f );

	AGEStateManager::CoordSystem system = AGEStateManager::getInstance().getCoordSystem(); 

	if( system == AGEStateManager::Local )
	{
		D3DXMATRIX rotMatrix = getWorldRotMatrix(); 

		D3DXVec3TransformCoord( &xAxis, &xAxis, &rotMatrix );
		D3DXVec3TransformCoord( &yAxis, &yAxis, &rotMatrix );
		D3DXVec3TransformCoord( &zAxis, &zAxis, &rotMatrix );	
	}

	D3DXVECTOR3 camEye = camera->getEye() - m_beginPos; 

	float cosX = D3DXVec3Dot( &xAxis, &camEye );
	float cosY = D3DXVec3Dot( &yAxis, &camEye );
	float cosZ = D3DXVec3Dot( &zAxis, &camEye );

	if( m_axis == XY_AXIS )
	{
		cosX = cosX >= 0.0f ? 0.0f : -1.0f;
		cosY = cosY >= 0.0f ? 0.0f : -1.0f;

		setLocalAngle( D3DXToRadian( 180.0f * cosY ), D3DXToRadian( 180.0f * cosX ), D3DXToRadian( 0.0f  ) );
	}
	else if( m_axis == XZ_AXIS )
	{
		cosX = cosX >= 0.0f ? 0.0f : -1.0f;
		cosZ = cosZ > 0.0f ? 1.0f : cosZ < 0.0f ? -1.0f : 0.0f;

		setLocalAngle( D3DXToRadian( ( cosX < 0.0f ? -1.0f : 1.0f ) * 90.0f * cosZ  ), D3DXToRadian( 180.0f * cosX ), D3DXToRadian( 0.0f ) );
	}
	else if( m_axis == YZ_AXIS )
	{
		cosY = cosY >= 0.0f ? 0.0f : -1.0f;
		cosZ = cosZ > 0.0f ? 1.0f : cosZ < 0.0f ? -1.0f : 0.0f;

		setLocalAngle( D3DXToRadian( -180.0f * cosY ), D3DXToRadian( -90.0f * cosZ ), 0.0f );
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

			setLocalAngle( D3DXToRadian( -90.0f * cosY ), D3DXToRadian( 90.0f * ( cosX + cosZ ) ), D3DXToRadian( 0.0f ) );	
		}
		else if( cosX * cosZ < 0.0f )
		{
			setLocalAngle( D3DXToRadian( -90.0f * cosY ), D3DXToRadian( 90.0f * cosX ), D3DXToRadian( 0.0f ) );
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

	releaseBuffers(); 
}

float AGIntersectTriangle::intersect(D3DXVECTOR3 rayOrigin, D3DXVECTOR3 rayDir)
{
	float retDist = -1.0f;
	int high = ( m_axis == XYZ_AXIS ) ? 3 : 2; 
	for( int i = 0; i < high; i++ )
	{
		D3DXVECTOR3 vertex1 = m_vertices[ 3*i ];
		D3DXVECTOR3 vertex2 = m_vertices[ 3*i + 1 ];
		D3DXVECTOR3 vertex3 = m_vertices[ 3*i + 2 ];

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

D3DXVECTOR3 AGIntersectTriangle::getAxis()
{
	if( m_axis == XY_AXIS )
		return D3DXVECTOR3( 1.0f, 1.0f, 0.0f );
	if( m_axis == XZ_AXIS )
		return D3DXVECTOR3( 1.0f, 0.0f, 1.0f );
	if( m_axis == YZ_AXIS )
		return D3DXVECTOR3( 0.0f, 1.0f, 1.0f );
	if( m_axis == XYZ_AXIS )
		return D3DXVECTOR3( 1.0f, 1.0f, 1.0f ); 
	return D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
}

