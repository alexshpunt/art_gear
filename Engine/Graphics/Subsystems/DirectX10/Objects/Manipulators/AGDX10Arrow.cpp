#include "AGDX10Arrow.h"

#include "Managers/AGLogger.h"
#include "Graphics/Subsystems/DirectX10/Objects/AGDX10Camera.h"

AGDX10Arrow::AGDX10Arrow( ID3D10Device* device, ArrowAxis axis  ) : AGDX10Primitive( device )
{
	m_axis = axis; 
	D3DXVECTOR4 color( (axis == X_AXIS) * 0.798431372, (axis == Y_AXIS) * 0.6117647058, (axis == Z_AXIS) * 0.76470588233, 1.0f );
	float k = 0.05f;
	float height = 5.0f;
	float radius = 0.2f;
	float d = 0.025f;
	AGColorVertex vertices[] = 
	{
		{ D3DXVECTOR3( k * radius * 0            , k * height, k * radius * 0 ),             color }, //0 
		{ D3DXVECTOR3( k * radius * 1            , k * height, k * radius * 0 ),             color }, //1 
		{ D3DXVECTOR3( k * radius * 0.951057     , k * height, k * radius * 0.309017 ),      color }, //2 
		{ D3DXVECTOR3( k * radius * 0.809017     , k * height, k * radius * 0.587785 ),      color }, //3 
		{ D3DXVECTOR3( k * radius * 0.587785     , k * height, k * radius * 0.809017 ),      color }, //4 
		{ D3DXVECTOR3( k * radius * 0.309017     , k * height, k * radius * 0.951057 ),      color }, //5 
		{ D3DXVECTOR3( k * radius * -4.37114e-008, k * height, k * radius * 1 ),             color }, //6 
		{ D3DXVECTOR3( k * radius * -0.309017    , k * height, k * radius * 0.951056 ),      color }, //7 
		{ D3DXVECTOR3( k * radius * -0.587785    , k * height, k * radius * 0.809017 ),      color }, //8 
		{ D3DXVECTOR3( k * radius * -0.809017    , k * height, k * radius * 0.587785 ),      color }, //9 
		{ D3DXVECTOR3( k * radius * -0.951057    , k * height, k * radius * 0.309017 ),      color }, //10 
		{ D3DXVECTOR3( k * radius * -1           , k * height, k * radius * -3.25841e-007 ), color }, //11 
		{ D3DXVECTOR3( k * radius * -0.951056    , k * height, k * radius * -0.309017 ),     color }, //12 
		{ D3DXVECTOR3( k * radius * -0.809017    , k * height, k * radius * -0.587786 ),     color }, //13 
		{ D3DXVECTOR3( k * radius * -0.587785    , k * height, k * radius * -0.809017 ),     color }, //14 
		{ D3DXVECTOR3( k * radius * -0.309016    , k * height, k * radius * -0.951057 ),     color }, //15 
		{ D3DXVECTOR3( k * radius * 9.65599e-007 , k * height, k * radius * -1 ),            color }, //16 
		{ D3DXVECTOR3( k * radius * 0.309018     , k * height, k * radius * -0.951056 ),     color }, //17 
		{ D3DXVECTOR3( k * radius * 0.587786     , k * height, k * radius * -0.809016 ),     color }, //18 
		{ D3DXVECTOR3( k * radius * 0.809018     , k * height, k * radius * -0.587784 ),     color }, //19 
		{ D3DXVECTOR3( k * radius * 0.951057     , k * height, k * radius * -0.309016 ),     color }, //20 
		{ D3DXVECTOR3( k * radius * 0            , k * height * 1.3, k * radius * 0 ),       color }, //21 
		{ D3DXVECTOR3( k * radius * 0            , 0             , k * radius * 0 ),         color }, //22 
		{ D3DXVECTOR3( k * d            , k * height, 0.0f ),       color }, //21 
		{ D3DXVECTOR3( k * d           , 0             , 0 ),         color }, //22 
		{ D3DXVECTOR3( -k * d            , k * height, 0.0f ),       color }, //21 
		{ D3DXVECTOR3( -k * d            , 0             , 0.0f ),         color }, //22 
	};

	D3D10_BUFFER_DESC buffDesc; 

	buffDesc.Usage = D3D10_USAGE_DEFAULT; 
	buffDesc.ByteWidth = sizeof( vertices ); 
	buffDesc.CPUAccessFlags = 0;
	buffDesc.MiscFlags = 0;
	buffDesc.BindFlags = D3D10_BIND_VERTEX_BUFFER; 

	D3D10_SUBRESOURCE_DATA subresData; 
	subresData.pSysMem = vertices;

	HRESULT hr = device->CreateBuffer( &buffDesc, &subresData, &m_vertexBuffer );

	if( FAILED( hr ) )
	{
		AGError() << "Couldn't create vertex buffer";
		return; 
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

	buffDesc.ByteWidth = sizeof( indices );
	buffDesc.BindFlags = D3D10_BIND_INDEX_BUFFER; 
	subresData.pSysMem = indices;

	m_nIndices = sizeof( indices ) / sizeof( indices[ 0 ] );

	hr = device->CreateBuffer( &buffDesc, &subresData, &m_indexBuffer );

	if( FAILED( hr ) )
	{
		AGError() << "Couldn't create index buffer"; 
		return; 
	}

	D3D10_DEPTH_STENCIL_DESC dsDesc; 

	dsDesc.DepthEnable = false; 
	dsDesc.DepthFunc = D3D10_COMPARISON_GREATER; 
	dsDesc.DepthWriteMask = D3D10_DEPTH_WRITE_MASK_ALL; 

	dsDesc.StencilEnable = true;
	dsDesc.StencilReadMask = 0xFF;
	dsDesc.StencilWriteMask = 0xFF;

	// Stencil operations if pixel is front-facing
	dsDesc.FrontFace.StencilFailOp = D3D10_STENCIL_OP_KEEP;
	dsDesc.FrontFace.StencilDepthFailOp = D3D10_STENCIL_OP_INCR;
	dsDesc.FrontFace.StencilPassOp = D3D10_STENCIL_OP_KEEP;
	dsDesc.FrontFace.StencilFunc = D3D10_COMPARISON_ALWAYS;

	// Stencil operations if pixel is back-facing
	dsDesc.BackFace.StencilFailOp = D3D10_STENCIL_OP_KEEP;
	dsDesc.BackFace.StencilDepthFailOp = D3D10_STENCIL_OP_DECR;
	dsDesc.BackFace.StencilPassOp = D3D10_STENCIL_OP_KEEP;
	dsDesc.BackFace.StencilFunc = D3D10_COMPARISON_ALWAYS;

	device->CreateDepthStencilState( &dsDesc, &m_depthState );

}

AGDX10Arrow::~AGDX10Arrow()
{

}

void AGDX10Arrow::draw( ID3D10Device* device, AGDX10Camera* camera )
{
	D3D10_TECHNIQUE_DESC desc; 
	m_technique->GetDesc( &desc );

	D3DXMATRIX translMatr;
	D3DXVECTOR3 camEye = camera->getEye(); 
	D3DXVECTOR3 at( 1.5f, 2.5f, 0.0f ); 
	D3DXVECTOR3 camAt = camera->getAt(); 
	D3DXVECTOR3 dir = camEye - at; 
	D3DXVec3Normalize( &dir, &dir );
	dir = camEye - dir * 1.5f; 
	D3DXVECTOR3 pos = dir; 
	D3DXMatrixIdentity( &translMatr );
	D3DXMatrixTranslation( &translMatr, pos.x, pos.y, pos.z );
	D3DXMatrixIdentity( &m_world );

	D3DXMATRIX rotMat;
	float angleY = camera->getAngleY(); 
	D3DXMatrixRotationY( &rotMat, angleY );

	D3DXMATRIX axisRotMat;
	D3DXMatrixIdentity( &axisRotMat );

	if( m_axis == X_AXIS )
	{
		D3DXMatrixRotationZ( &axisRotMat, D3DXToRadian( 90.0f ) );	
	}
	else if( m_axis == Z_AXIS )
	{
		D3DXMatrixRotationX( &axisRotMat, D3DXToRadian( 90.0f ) );
	}

	m_world *= rotMat; 
	m_world *= axisRotMat;
	m_world *= translMatr;

	m_worldVar->SetMatrix( m_world );
	m_viewVar->SetMatrix( camera->getViewMatrix() );
	m_projectionVar->SetMatrix( camera->getProjMatrix() );

	device->IASetInputLayout( m_inputLayout );
	device->IASetIndexBuffer( m_indexBuffer, DXGI_FORMAT_R32_UINT, 0 );
	UINT stride = sizeof( AGColorVertex );
	UINT offset = 0; 
	device->IASetVertexBuffers( 0, 1, &m_vertexBuffer, &stride, &offset );

	ID3D10DepthStencilState* state;
	device->OMGetDepthStencilState( &state, 0 );
	device->OMSetDepthStencilState( m_depthState, 1 );

	for( int i = 0; i < desc.Passes; i++ )
	{
		m_technique->GetPassByIndex( i )->Apply( 0 );
		device->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
		device->DrawIndexed( m_nIndices, 0, 0 );
		device->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_LINELIST );
		device->Draw( 6, 21 );
	}

	device->OMSetDepthStencilState( state, 0 );

}

float AGDX10Arrow::intersect( D3DXVECTOR3 rayOrigin, D3DXVECTOR3 rayDir )
{
	return -1.0f; 
}

