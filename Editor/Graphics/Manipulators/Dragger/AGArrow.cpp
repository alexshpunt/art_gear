#include "AGArrow.h"

#include "Engine/Managers/AGLogger.h"
#include "Engine/Graphics/Interfaces/AGSurface.h"
#include "Engine/Graphics/Objects/AGCamera.h"

AGArrow::AGArrow( ArrowAxis axis  )
{
	m_axis = axis; 
	m_isSelected = false; 

	AGColor color( (axis == X_AXIS) * 0.798431372, (axis == Y_AXIS) * 0.6117647058, (axis == Z_AXIS) * 0.76470588233, 1.0f );
	AGColor yellow( 1.0f, 1.0f, 0.0f, 1.0f );
	float k = 0.05f;
	float height = 4.0f;
	float radius = 0.2f;
	float d = 0.025f;
	AGColorVertex vertices[] = 
	{
		{ AGVec3( k * radius * 0            , k * height, k * radius * 0 ),             color }, //0 
		{ AGVec3( k * radius * 1            , k * height, k * radius * 0 ),             color }, //1 
		{ AGVec3( k * radius * 0.951057     , k * height, k * radius * 0.309017 ),      color }, //2 
		{ AGVec3( k * radius * 0.809017     , k * height, k * radius * 0.587785 ),      color }, //3 
		{ AGVec3( k * radius * 0.587785     , k * height, k * radius * 0.809017 ),      color }, //4 
		{ AGVec3( k * radius * 0.309017     , k * height, k * radius * 0.951057 ),      color }, //5 
		{ AGVec3( k * radius * -4.37114e-008, k * height, k * radius * 1 ),             color }, //6 
		{ AGVec3( k * radius * -0.309017    , k * height, k * radius * 0.951056 ),      color }, //7 
		{ AGVec3( k * radius * -0.587785    , k * height, k * radius * 0.809017 ),      color }, //8 
		{ AGVec3( k * radius * -0.809017    , k * height, k * radius * 0.587785 ),      color }, //9 
		{ AGVec3( k * radius * -0.951057    , k * height, k * radius * 0.309017 ),      color }, //10 
		{ AGVec3( k * radius * -1           , k * height, k * radius * -3.25841e-007 ), color }, //11 
		{ AGVec3( k * radius * -0.951056    , k * height, k * radius * -0.309017 ),     color }, //12 
		{ AGVec3( k * radius * -0.809017    , k * height, k * radius * -0.587786 ),     color }, //13 
		{ AGVec3( k * radius * -0.587785    , k * height, k * radius * -0.809017 ),     color }, //14 
		{ AGVec3( k * radius * -0.309016    , k * height, k * radius * -0.951057 ),     color }, //15 
		{ AGVec3( k * radius * 9.65599e-007 , k * height, k * radius * -1 ),            color }, //16 
		{ AGVec3( k * radius * 0.309018     , k * height, k * radius * -0.951056 ),     color }, //17 
		{ AGVec3( k * radius * 0.587786     , k * height, k * radius * -0.809016 ),     color }, //18 
		{ AGVec3( k * radius * 0.809018     , k * height, k * radius * -0.587784 ),     color }, //19 
		{ AGVec3( k * radius * 0.951057     , k * height, k * radius * -0.309016 ),     color }, //20 
		{ AGVec3( k * radius * 0            , k * height * 1.3, k * radius * 0 ), color }, //21 
		{ AGVec3( 0.0f                      , k * height, k * radius * 0 ),       color }, //22 
		{ AGVec3( 0.0f                      , 0               , k * radius * 0 ),       color }, //23 
		{ AGVec3( 0.0f                      , k * height, k * radius * 0 ),      yellow }, //24
		{ AGVec3( 0.0f                      , 0               , k * radius * 0 ),      yellow }, //25
	};

	m_vertexBuffer = new AGBuffer< AGColorVertex >( vector< AGColorVertex >( vertices, vertices + 26 ), AGBufferType::Vertex );

	for( int i = 0 ; i < 26; i++ )
	{
		m_vertices.push_back( vertices[ i ].pos );
	}

	int indices[] = 
	{
		0, //1
		1, 2, 0, 2, 3, //6 
		0, 3, 4, 0, 4, //11
		5, 0, 5, 6, 0, 
		6, 7, 0, 7, 8, 
		0, 8, 9, 0, 9, 
		10, 0, 10, 11, 0, 
		11, 12, 0, 12, 13, 
		0, 13, 14, 0, 14, 
		15, 0, 15, 16, 0, 
		16, 17, 0, 17, 18, 
		0, 18, 19, 0, 19, 
		20, 0, 20, 1, 1, 
		21, 21, 1, 21, 2, 
		2, 21, 21, 2, 21, 
		3, 3, 21, 21, 3, 
		21, 4, 4, 21, 21, 
		4, 21, 5, 5, 21, 
		21, 5, 21, 6, 6, 
		21, 21, 6, 21, 7, 
		7, 21, 21, 7, 21, 
		8, 8, 21, 21, 8, 
		21, 9, 9, 21, 21, 
		9, 21, 10, 10, 21, 
		21, 10, 21, 11, 11, 
		21, 21, 11, 21, 12, 
		12, 21, 21, 12, 21, 
		13, 13, 21, 21, 13, 
		21, 14, 14, 21, 21, 
		14, 21, 15, 15, 21, 
		21, 15, 21, 16, 16, 
		21, 21, 16, 21, 17, 
		17, 21, 21, 17, 21, 
		18, 18, 21, 21, 18, 
		21, 19, 19, 21, 21, 
		19, 21, 20, 20, 21, 
		21, 20, 21, 1, 21, 
	};

	int indexCount = sizeof( indices ) / sizeof( indices[ 0 ] );

	m_indices = vector< int >( indices, indices + indexCount ); 

	m_indexBuffer = new AGBuffer< int >( m_indices, AGBufferType::Index ); 

	m_boundingBox = new AGBoundingBox( AGVec3( -0.01f, 0.0f, -0.01f ), AGVec3( 0.01f, k * height, 0.01f ) );
}

AGArrow::~AGArrow()
{

}

void AGArrow::draw( AGSurface* surface )
{
	AGCamera* camera = surface->getCamera(); 
	ID3D10Device* device = surface->getDevice(); 

	updatePos( camera );

	if( m_axis == X_AXIS )
	{
		setLocalAngle( AGDegrees( 0.0f ), AGDegrees( 0.0f ), AGDegrees( -90.0f ) );	
	}
	else if( m_axis == Z_AXIS )
	{
		setLocalAngle( AGDegrees( 90.0f ), AGDegrees( 0.0f ), AGDegrees( 0.0f ) );	
	} 

	int curTick = GetTickCount(); 

	setupBuffers( surface );

	while( m_shader->applyNextPass() )
	{
		device->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
		device->DrawIndexed( m_indices.size(), 0, 0 );
		device->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_LINELIST );
		if( m_isSelected )
			device->Draw( 2, 24 );
		else 
			device->Draw( 2, 22 );
	}

	m_boundingBox->setLocalMatrix( getLocalMatrix() );
}

float AGArrow::intersect( const AGVec3& rayOrigin, const AGVec3& rayDir )
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

AGVec3 AGArrow::getAxis()
{
	return AGVec3( m_axis == X_AXIS, m_axis == Y_AXIS, m_axis == Z_AXIS );
}


