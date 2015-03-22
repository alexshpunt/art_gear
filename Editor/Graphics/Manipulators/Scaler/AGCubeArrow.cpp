#include "AGCubeArrow.h"

#include "Engine/Managers/AGLogger.h"
#include "Engine/Graphics/Interfaces/AGSurface.h"
#include "Engine/Graphics/Objects/AGCamera.h"

AGCubeArrow::AGCubeArrow( CubeArrowAxis axis )
{
	m_axis = axis; 
	m_isSelected = false; 

	D3DXVECTOR4 color( (axis == X_AXIS) * 0.798431372, (axis == Y_AXIS) * 0.6117647058, (axis == Z_AXIS) * 0.76470588233, 1.0f );
	D3DXVECTOR4 yellow( 1.0f, 1.0f, 0.0f, 1.0f );
	float k = 0.2f;
	float height = 1.0f;
	float radius = 1.0f;
	float side = 0.3f;
	AGPrimitiveVertex vertices[] = 
	{
		{ D3DXVECTOR3( k * radius * -0.0315, k * height * 1, k * radius * -0.03125 ), color }, //0 
		{ D3DXVECTOR3( k * radius * 0.0315, k * height * 1, k * radius * 0.03125 ), color }, //1 
		{ D3DXVECTOR3( k * radius * -0.0315, k * height * 1, k * radius * 0.03125 ), color }, //2 
		{ D3DXVECTOR3( k * radius * 0.0315, k * height * 1, k * radius * -0.03125 ), color }, //3 
		{ D3DXVECTOR3( k * radius * -0.0315, k * height * 1.063, k * radius * -0.03125 ), color }, //4 
		{ D3DXVECTOR3( k * radius * 0.0315, k * height * 1.063, k * radius * 0.03125 ), color }, //5 
		{ D3DXVECTOR3( k * radius * 0.0315, k * height * 1.063, k * radius * -0.03125 ), color }, //6 
		{ D3DXVECTOR3( k * radius * -0.0315, k * height * 1.063, k * radius * 0.03125 ), color }, //7 

		//Линия
		{ D3DXVECTOR3( 0.0f, k * height * 1.063, 0.0f ), color }, //8
		{ D3DXVECTOR3( 0.0f, 0.0f, 0.0f ), color }, //9

		{ D3DXVECTOR3( 0.0f, k * height * 1.063, 0.0f ), yellow }, //10
		{ D3DXVECTOR3( 0.0f, 0.0f, 0.0f ), yellow }, //11
	};

	m_vertexBuffer = new AGBuffer< AGPrimitiveVertex >( vector< AGPrimitiveVertex >( vertices, vertices + 12 ), AGBufferType::Vertex );

	int verticesCount = sizeof( vertices ) / sizeof( AGPrimitiveVertex ) - 4; //4 вертекса на линию 

	for( int i = 0 ; i < verticesCount; i++ )
	{
		m_vertices.push_back( vertices[ i ] );
	}

	int indices[] = 
	{
		0, 
		1, 2, 1, 0, 3, 
		4, 5, 6, 5, 4, 
		7, 0, 6, 3, 6, 
		0, 4, 3, 5, 1, 
		5, 3, 6, 1, 7, 
		2, 7, 1, 5, 2, 
		4, 0, 4, 2, 7, //36
	};

	m_nIndices = sizeof( indices ) / sizeof( int );

	m_indexBuffer = new AGBuffer< int >( vector< int >( indices, indices + m_nIndices + 1 ), AGBufferType::Index );

	m_boundingBox = new AGBoundingBox( D3DXVECTOR3( -0.01f, 0.0f, -0.01f ), D3DXVECTOR3( 0.01f, k * height, 0.01f ) );
}

AGCubeArrow::~AGCubeArrow()
{

}

void AGCubeArrow::draw( AGSurface* surface )
{
	AGCamera* camera = surface->getCamera(); 
	ID3D10Device* device = surface->getDevice(); 

	updatePos( camera );

	D3DXMATRIX worldTextMat = getLocalMatrix();
	D3DXVECTOR3 xAxis( 1.0f, 0.0f, 0.0f );
	D3DXVECTOR3 yAxis( 0.0f, 1.0f, 0.0f );
	D3DXVECTOR3 zAxis( 0.0f, 0.0f, 1.0f );

	AGEStateManager::CoordSystem system = AGEStateManager::getInstance().getCoordSystem(); 

	if( system == AGEStateManager::Local )
	{
		D3DXMATRIX rotMatrix = getWorldRotMatrix(); 

		D3DXVec3TransformCoord( &xAxis, &xAxis, &rotMatrix );
		D3DXVec3TransformCoord( &yAxis, &yAxis, &rotMatrix );
		D3DXVec3TransformCoord( &zAxis, &zAxis, &rotMatrix );	
	}

	D3DXVECTOR3 camEye = camera->getPos() - m_beginPos; 	

	if( m_axis == X_AXIS )
	{
		float cosA = D3DXVec3Dot( &xAxis, &camEye );
		if( cosA > 0.0f )
		{
			cosA = 1.0f; 
			m_axisDir.x = 1.0f;
		}
		else if( cosA < 0.0f )
		{
			cosA = -1.0f; 
			m_axisDir.x = -1.0f;
		}
		else 
		{
			cosA == 0.0f; 
			m_axisDir.x = 0.0f;
		}
		setLocalAngle( 0.0f, 0.0f, D3DXToRadian( -90.0f * cosA ) );	
	}
	else if( m_axis == Y_AXIS )
	{
		float cosA = D3DXVec3Dot( &yAxis, &camEye );
		if( cosA >= 0.0f )
		{
			cosA = 0.0f; 
			m_axisDir.y = 0.0f; 
		}
		else if( cosA < 0.0f )
		{
			cosA = -1.0f; 
			m_axisDir.y = -1.0f; 
		}
		setLocalAngle( D3DXToRadian( 180.0f * cosA ), 0.0f, 0.0f );	
	}
	else if( m_axis == Z_AXIS )
	{
		float cosA = D3DXVec3Dot( &zAxis, &camEye );
		if( cosA > 0.0f )
		{
			cosA = 1.0f; 
			m_axisDir.z = 1.0f; 
		}
		else if( cosA < 0.0f )
		{
			cosA = -1.0f; 
			m_axisDir.z = -1.0f; 
		}
		else 
		{
			cosA == 0.0f; 
			m_axisDir.z = 0.0f; 
		}
		setLocalAngle( D3DXToRadian( 90.0f * cosA ), 0.0f, 0.0f );	
	} 	

	setupBuffers( surface );

	while( m_shader->applyNextPass() )
	{
		device->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
		device->DrawIndexed( m_nIndices, 0, 0 );
		device->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_LINELIST );
		if( m_isSelected )
			device->Draw( 2, 10 );
		else 
			device->Draw( 2, 8 );
	}

	releaseBuffers(); 
	m_boundingBox->setLocalMatrix( getLocalMatrix() );
}

float AGCubeArrow::intersect(D3DXVECTOR3 rayOrigin, D3DXVECTOR3 rayDir)
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

	float boundBoxDist = m_boundingBox->intersect( rayOrigin, rayDir );

	if( boundBoxDist > 0 )
	{
		if( retDist > 0  )
			retDist = min( retDist, boundBoxDist);
		else 
			retDist = boundBoxDist;	
	}

	return retDist; 
}

D3DXVECTOR3 AGCubeArrow::getAxis()
{
	D3DXVECTOR3 axis( m_axis == X_AXIS, m_axis == Y_AXIS, m_axis == Z_AXIS );

	axis.x *= m_axisDir.x != 0 ? m_axisDir.x : 1;
	axis.y *= m_axisDir.y != 0 ? m_axisDir.y : 1; 
	axis.z *= m_axisDir.z != 0 ? m_axisDir.z : 1;

	return axis;
}

