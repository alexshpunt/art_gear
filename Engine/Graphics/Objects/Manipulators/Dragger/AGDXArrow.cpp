#include "AGDXArrow.h"

#include "Managers/AGLogger.h"
#include "Graphics/Interfaces/AGSurface.h"
#include "Graphics/Objects/AGDXCamera.h"

AGDXArrow::AGDXArrow( ID3D10Device* device, ArrowAxis axis  ) : AGDXGizmo( device )
{
	m_axis = axis; 
	m_isSelected = false; 

	D3DXVECTOR4 color( (axis == X_AXIS) * 0.798431372, (axis == Y_AXIS) * 0.6117647058, (axis == Z_AXIS) * 0.76470588233, 1.0f );
	D3DXVECTOR4 yellow( 1.0f, 1.0f, 0.0f, 1.0f );
	float k = 0.05f;
	float height = 3.0f;
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
		{ D3DXVECTOR3( k * radius * 0, k * height * 1.3, k * radius * 0 ), color }, //21 
		{ D3DXVECTOR3( 0.0f                      , k * height, k * radius * 0 ),       color }, //22 
		{ D3DXVECTOR3( 0.0f                      , 0               , k * radius * 0 ),       color }, //23 
		{ D3DXVECTOR3( 0.0f                      , k * height, k * radius * 0 ),      yellow }, //24
		{ D3DXVECTOR3( 0.0f                      , 0               , k * radius * 0 ),      yellow }, //25
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

	for( int i = 0 ; i < 25; i++ )
	{
		m_vertices.push_back( vertices[ i ] );
	}

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

	for( int i = 0; i < m_nIndices; i++ )
	{
		m_indices.push_back( indices[ i ] );
	}

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

	dsDesc.FrontFace.StencilFailOp = D3D10_STENCIL_OP_KEEP;
	dsDesc.FrontFace.StencilDepthFailOp = D3D10_STENCIL_OP_INCR;
	dsDesc.FrontFace.StencilPassOp = D3D10_STENCIL_OP_KEEP;
	dsDesc.FrontFace.StencilFunc = D3D10_COMPARISON_ALWAYS;

	dsDesc.BackFace.StencilFailOp = D3D10_STENCIL_OP_KEEP;
	dsDesc.BackFace.StencilDepthFailOp = D3D10_STENCIL_OP_DECR;
	dsDesc.BackFace.StencilPassOp = D3D10_STENCIL_OP_KEEP;
	dsDesc.BackFace.StencilFunc = D3D10_COMPARISON_ALWAYS;

	device->CreateDepthStencilState( &dsDesc, &m_depthState );

	m_boundingBox = new AGDXBoundingBox( D3DXVECTOR3( -0.01f, 0.0f, -0.01f ), D3DXVECTOR3( 0.01f, k * height, 0.01f ), device );

	D3DX10_FONT_DESC fontDesc;

	fontDesc.CharSet = OUT_DEFAULT_PRECIS;
	wcscpy_s( fontDesc.FaceName, 32, L"Consolas" );
	fontDesc.Height = 16;
	fontDesc.Width = 0;
	fontDesc.Weight = 0;
	fontDesc.MipLevels = 1;
	fontDesc.Italic = false;
	fontDesc.Quality = DEFAULT_QUALITY; 
	fontDesc.PitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;

	D3DX10CreateFontIndirect( device, &fontDesc, &m_font );
}

AGDXArrow::~AGDXArrow()
{

}

void AGDXArrow::draw( AGDXSurface* surface )
{
	D3D10_TECHNIQUE_DESC desc; 
	m_technique->GetDesc( &desc );

	AGDXCamera* camera = surface->getCamera(); 
	ID3D10Device* device = surface->getDevice(); 

	D3DXVECTOR3 camEye = camera->getEye(); 
	D3DXVECTOR3 dir = camEye - m_worldPos; 
	D3DXVec3Normalize( &dir, &dir );
	dir = camEye - dir * 1.0f; 
	D3DXVECTOR3 pos = dir; 
	
	setLocalPos( pos.x, pos.y, pos.z );

	D3DXMATRIX worldTextMat = getLocalMatrix();

	if( m_axis == X_AXIS )
	{
		setLocalAngle( 0.0f, 0.0f, D3DXToRadian( -90.0f ) );	
	}
	else if( m_axis == Z_AXIS )
	{
		setLocalAngle( D3DXToRadian( 90.0f ), 0.0f, 0.0f );	
	} 

	D3DXMATRIX viewMat = camera->getViewMatrix();
	D3DXMATRIX projMat = camera->getProjMatrix();

	AGStateManager::CoordSystem system = AGStateManager::getInstance().getCoordSystem(); 

	m_worldVar->SetMatrix( system == AGStateManager::Local ? getResultMatrix() : getLocalMatrix() );
	m_viewVar->SetMatrix( viewMat );
	m_projectionVar->SetMatrix( projMat );

	device->IASetInputLayout( m_inputLayout );
	device->IASetIndexBuffer( m_indexBuffer, DXGI_FORMAT_R32_UINT, 0 );
	UINT stride = sizeof( AGColorVertex );
	UINT offset = 0; 
	device->IASetVertexBuffers( 0, 1, &m_vertexBuffer, &stride, &offset );

	device->OMSetDepthStencilState( m_depthState, 1 );

	for( int i = 0; i < desc.Passes; i++ )
	{
		m_technique->GetPassByIndex( i )->Apply( 0 );
		device->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
		device->DrawIndexed( m_nIndices, 0, 0 );
		device->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_LINELIST );
		if( m_isSelected || m_isActivated )
			device->Draw( 2, 24 );
		else 
			device->Draw( 2, 22 );
	}

	m_boundingBox->setLocalMatrix( getLocalMatrix() );

	/*float halfWidth = surface->getWidth() / 2.0f;
	float halfHeight = surface->getHeight() / 2.0f; 

	D3DXCOLOR fontColor( 0.798431372 * ( m_axis == X_AXIS ), 0.6117647058 * ( m_axis == Y_AXIS ), 0.76470588233 * ( m_axis == Z_AXIS ), 1.0f );

	switch( m_axis )
	{
		case X_AXIS:
			pos = D3DXVECTOR3( 0.18f, 0.05f, 0.0f ); 
		break;
		case Y_AXIS:
			pos = D3DXVECTOR3( 0.0f, 0.23f, 0.0f ); 
		break;
		case Z_AXIS:
			pos = D3DXVECTOR3( 0.0f, 0.05f, 0.18f ); 
		break;
	}

	D3DXVec3TransformCoord( &pos, &pos, &worldTextMat );
	D3DXVec3TransformCoord( &pos, &pos, &viewMat );
	D3DXVec3TransformCoord( &pos, &pos, &projMat );

	float textX = pos.x * halfWidth + halfWidth;
	float textY = -pos.y * halfHeight + halfHeight; 

	RECT rect = { textX, textY, 0, 0 }; 

	wchar_t* str = m_axis == X_AXIS ? L"X" : m_axis == Y_AXIS ? L"Y" : L"Z";

	m_font->DrawTextW( 0, str, -1, &rect, DT_NOCLIP, fontColor );		
	device->OMSetBlendState(NULL, 0, 0xffffffff);*/
	//m_boundingBox->draw( surface );
}

float AGDXArrow::intersect( D3DXVECTOR3 rayOrigin, D3DXVECTOR3 rayDir )
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

D3DXVECTOR3 AGDXArrow::getAxis()
{
	return D3DXVECTOR3( m_axis == X_AXIS, m_axis == Y_AXIS, m_axis == Z_AXIS );
}


