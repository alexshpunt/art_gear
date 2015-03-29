#include "AGCubeArrow.h"

#include "Engine/Managers/AGLogger.h"
#include "Engine/Graphics/Interfaces/AGSurface.h"
#include "Engine/Graphics/Objects/AGCamera.h"

AGCubeArrow::AGCubeArrow( CubeArrowAxis axis )
{
	m_axis = axis; 
	m_isSelected = false; 

	AGColor color( (axis == X_AXIS) * 0.798431372, (axis == Y_AXIS) * 0.6117647058, (axis == Z_AXIS) * 0.76470588233, 1.0f );
	AGColor yellow( 1.0f, 1.0f, 0.0f, 1.0f );
	float k = 0.2f;
	float height = 1.0f;
	float radius = 1.0f;
	float side = 0.3f;
	AGPrimitiveVertex vertices[] = 
	{
		{ AGVec3( k * radius * -0.0315, k * height * 1, k * radius * -0.03125 ), color }, //0 
		{ AGVec3( k * radius * 0.0315, k * height * 1, k * radius * 0.03125 ), color }, //1 
		{ AGVec3( k * radius * -0.0315, k * height * 1, k * radius * 0.03125 ), color }, //2 
		{ AGVec3( k * radius * 0.0315, k * height * 1, k * radius * -0.03125 ), color }, //3 
		{ AGVec3( k * radius * -0.0315, k * height * 1.063, k * radius * -0.03125 ), color }, //4 
		{ AGVec3( k * radius * 0.0315, k * height * 1.063, k * radius * 0.03125 ), color }, //5 
		{ AGVec3( k * radius * 0.0315, k * height * 1.063, k * radius * -0.03125 ), color }, //6 
		{ AGVec3( k * radius * -0.0315, k * height * 1.063, k * radius * 0.03125 ), color }, //7 

		//Линия
		{ AGVec3( 0.0f, k * height * 1.063, 0.0f ), color }, //8
		{ AGVec3( 0.0f, 0.0f, 0.0f ), color }, //9

		{ AGVec3( 0.0f, k * height * 1.063, 0.0f ), yellow }, //10
		{ AGVec3( 0.0f, 0.0f, 0.0f ), yellow }, //11
	};

	m_vertexBuffer = new AGBuffer< AGPrimitiveVertex >( vector< AGPrimitiveVertex >( vertices, vertices + 12 ), AGBufferType::Vertex );

	int verticesCount = sizeof( vertices ) / sizeof( AGPrimitiveVertex ) - 4; //4 вертекса на линию 

	for( int i = 0 ; i < verticesCount; i++ )
	{
		m_vertices.push_back( vertices[ i ].pos );
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

	int indexCount = sizeof( indices ) / sizeof( int );

	m_indices = vector< int >( indices, indices + indexCount );

	m_indexBuffer = new AGBuffer< int >( m_indices, AGBufferType::Index );

	m_boundingBox = new AGBoundingBox( AGVec3( -0.01f, 0.0f, -0.01f ), AGVec3( 0.01f, k * height, 0.01f ) );
}

AGCubeArrow::~AGCubeArrow()
{
	delete m_boundingBox;
	delete m_indexBuffer;
}

void AGCubeArrow::draw( AGSurface* surface )
{
	AGCamera* camera = surface->getCamera(); 
	ID3D10Device* device = surface->getDevice(); 

	assert( camera );
	assert( device );

	updatePos( camera );

	AGVec3 xAxis( 1.0f, 0.0f, 0.0f );
	AGVec3 yAxis( 0.0f, 1.0f, 0.0f );
	AGVec3 zAxis( 0.0f, 0.0f, 1.0f );

	AGEStateManager::CoordSystem system = AGEStateManager::getInstance().getCoordSystem(); 

	if( system == AGEStateManager::Local )
	{
		AGMatrix rotMatrix = getWorldRotMatrix(); 

		xAxis *= rotMatrix;
		yAxis *= rotMatrix;
		zAxis *= rotMatrix; 
	}

	AGVec3 camEye = camera->getPos() - m_beginPos; 	

	if( m_axis == X_AXIS )
	{
		float cosA = AGVec3::dot( xAxis, camEye );
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
		setLocalAngle( AGDegrees( 0.0f ), AGDegrees( 0.0f ), AGDegrees( -90.0f * cosA ) );	
	}
	else if( m_axis == Y_AXIS )
	{
		float cosA = AGVec3::dot( yAxis, camEye );
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
		setLocalAngle( AGDegrees( 180.0f * cosA ), AGDegrees( 0.0f ), AGDegrees( 0.0f ) );	
	}
	else if( m_axis == Z_AXIS )
	{
		float cosA = AGVec3::dot( zAxis, camEye );
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
		setLocalAngle( AGDegrees( 90.0f * cosA ), AGDegrees( 0.0f ), AGDegrees( 0.0f ) );	
	} 	

	setupBuffers( surface );

	while( m_shader->applyNextPass() )
	{
		device->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
		device->DrawIndexed( m_indices.size(), 0, 0 );
		device->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_LINELIST );
		if( m_isSelected )
			device->Draw( 2, 10 );
		else 
			device->Draw( 2, 8 );
	}

	m_boundingBox->setLocalMatrix( getLocalMatrix() );
}

float AGCubeArrow::intersect( const AGVec3& rayOrigin, const AGVec3& rayDir)
{
	float retDist = AGDrawable::intersect( rayOrigin, rayDir );

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

AGVec3 AGCubeArrow::getAxis()
{
	AGVec3 axis( m_axis == X_AXIS, m_axis == Y_AXIS, m_axis == Z_AXIS );

	axis.x *= m_axisDir.x != 0 ? m_axisDir.x : 1;
	axis.y *= m_axisDir.y != 0 ? m_axisDir.y : 1; 
	axis.z *= m_axisDir.z != 0 ? m_axisDir.z : 1;

	return axis;
}

