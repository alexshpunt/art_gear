#include "AGDXCubeArrow.h"

#include "Managers/AGLogger.h"
#include "Graphics/Interfaces/AGSurface.h"
#include "Graphics/Objects/AGDXCamera.h"

AGDXCubeArrow::AGDXCubeArrow(ID3D10Device* device, CubeArrowAxis axis) : AGDXGizmo( device )
{
	m_axis = axis; 
	m_isSelected = false; 

	D3DXVECTOR4 color( (axis == X_AXIS) * 0.798431372, (axis == Y_AXIS) * 0.6117647058, (axis == Z_AXIS) * 0.76470588233, 1.0f );
	D3DXVECTOR4 yellow( 1.0f, 1.0f, 0.0f, 1.0f );
	float k = 0.2f;
	float height = 1.0f;
	float radius = 1.0f;
	float side = 0.3f;
	AGColorVertex vertices[] = 
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

	D3D10_BUFFER_DESC buffDesc; 

	buffDesc.Usage = D3D10_USAGE_DEFAULT; 
	buffDesc.ByteWidth = sizeof( vertices ); 
	buffDesc.CPUAccessFlags = 0;
	buffDesc.MiscFlags = 0;
	buffDesc.BindFlags = D3D10_BIND_VERTEX_BUFFER; 

	D3D10_SUBRESOURCE_DATA subresData; 
	subresData.pSysMem = vertices;

	HRESULT hr = device->CreateBuffer( &buffDesc, &subresData, &m_vertexBuffer );

	int verticesCount = sizeof( vertices ) / sizeof( AGColorVertex ) - 4; //4 вертекса на линию 

	for( int i = 0 ; i < verticesCount; i++ )
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
		0, 
		1, 2, 1, 0, 3, 
		4, 5, 6, 5, 4, 
		7, 0, 6, 3, 6, 
		0, 4, 3, 5, 1, 
		5, 3, 6, 1, 7, 
		2, 7, 1, 5, 2, 
		4, 0, 4, 2, 7, 
	};

	buffDesc.ByteWidth = sizeof( indices );
	buffDesc.BindFlags = D3D10_BIND_INDEX_BUFFER; 
	subresData.pSysMem = indices;

	m_nIndices = sizeof( indices ) / sizeof( int );

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
}

AGDXCubeArrow::~AGDXCubeArrow()
{

}

void AGDXCubeArrow::draw(AGDXSurface* surface)
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
	D3DXVECTOR3 xAxis( 1.0f, 0.0f, 0.0f );
	D3DXVECTOR3 yAxis( 0.0f, 1.0f, 0.0f );
	D3DXVECTOR3 zAxis( 0.0f, 0.0f, 1.0f );

	AGStateManager::CoordSystem system = AGStateManager::getInstance().getCoordSystem(); 

	if( system == AGStateManager::Local )
	{
		D3DXMATRIX rotMatrix = getWorldRotMatrix(); 

		D3DXVec3TransformCoord( &xAxis, &xAxis, &rotMatrix );
		D3DXVec3TransformCoord( &yAxis, &yAxis, &rotMatrix );
		D3DXVec3TransformCoord( &zAxis, &zAxis, &rotMatrix );	
	}

	camEye -= m_worldPos;

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

	D3DXMATRIX viewMat = camera->getViewMatrix();
	D3DXMATRIX projMat = camera->getProjMatrix();

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
		if( m_isSelected )
			device->Draw( 2, 10 );
		else 
			device->Draw( 2, 8 );
	}

	m_boundingBox->setLocalMatrix( getLocalMatrix() );
}

float AGDXCubeArrow::intersect(D3DXVECTOR3 rayOrigin, D3DXVECTOR3 rayDir)
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

D3DXVECTOR3 AGDXCubeArrow::getAxis()
{
	D3DXVECTOR3 axis( m_axis == X_AXIS, m_axis == Y_AXIS, m_axis == Z_AXIS );

	axis.x *= m_axisDir.x != 0 ? m_axisDir.x : 1;
	axis.y *= m_axisDir.y != 0 ? m_axisDir.y : 1; 
	axis.z *= m_axisDir.z != 0 ? m_axisDir.z : 1;

	return axis;
}

