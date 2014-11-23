#include "AGDXIntersectPlane.h"

#include "AGDXArrow.h"

#include "Managers/AGLogger.h"
#include "Graphics/Interfaces/AGSurface.h"
#include "Graphics/Objects/AGDXCamera.h"

AGDXIntersectPlane::AGDXIntersectPlane(ID3D10Device* device, PlaneAxis axis) : AGDXGizmo( device )
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

	AGColorVertex vertices[] = 
	{
		//Unselected rect
		{ D3DXVECTOR3( 0.0f, 0.0f, 0.0f ), firstColor  }, //0
		{ D3DXVECTOR3( 0.0f, len, 0.0f  ), firstColor  }, //1

		{ D3DXVECTOR3( 0.0f, len, 0.0f  ), secondColor }, //2
		{ D3DXVECTOR3( len , len, 0.0f  ), secondColor }, //3
			
		{ D3DXVECTOR3( len , len, 0.0f  ), firstColor  }, //4
		{ D3DXVECTOR3( len , 0.0f, 0.0f ), firstColor  }, //5

		{ D3DXVECTOR3( len , 0.0f, 0.0f ), secondColor }, //6	
		{ D3DXVECTOR3( 0.0f, 0.0f, 0.0f ), secondColor }, //7	

		//Selected rect
		{ D3DXVECTOR3( 0.0f, 0.0f, 0.0f ), yellow  }, //8
		{ D3DXVECTOR3( len, len, 0.0f   ), yellow  }, //9
		{ D3DXVECTOR3( 0.0f, len, 0.0f  ), yellow  }, //10

		{ D3DXVECTOR3( len , 0.0f, 0.0f ), yellow  }, //11
		{ D3DXVECTOR3( len , len, 0.0f  ), yellow  }, //12
		{ D3DXVECTOR3( 0.0f, 0.0f, 0.0f ), yellow  }, //13	
	};

	for (int i = 0; i < 6; i++)
	{
		m_vertices[ i ] = vertices[ 8 + i ].pos; 
	}

	D3D10_BUFFER_DESC buffDesc; 

	buffDesc.Usage = D3D10_USAGE_DEFAULT; 
	buffDesc.ByteWidth = sizeof( vertices ); 
	buffDesc.CPUAccessFlags = 0;
	buffDesc.MiscFlags = 0;
	buffDesc.BindFlags = D3D10_BIND_VERTEX_BUFFER; 

	D3D10_SUBRESOURCE_DATA subresData; 
	subresData.pSysMem = vertices;

	HRESULT hr = device->CreateBuffer( &buffDesc, &subresData, &m_vertexBuffer );

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

	m_arrow1 = m_arrow2 = nullptr;
}

AGDXIntersectPlane::~AGDXIntersectPlane()
{

}

void AGDXIntersectPlane::setArrows(AGDXArrow* arrow1, AGDXArrow* arrow2)
{
	m_arrow1 = arrow1;
	m_arrow2 = arrow2; 
}

void AGDXIntersectPlane::draw(AGDXSurface* surface)
{
	D3D10_TECHNIQUE_DESC desc; 
	m_technique->GetDesc( &desc );

	AGDXCamera* camera = surface->getCamera(); 
	ID3D10Device* device = surface->getDevice(); 

	D3DXVECTOR3 camEye = camera->getEye(); 
	D3DXVECTOR3 camAt = camera->getAt(); 
	D3DXVECTOR3 dir = camEye - m_worldPos; 
	D3DXVec3Normalize( &dir, &dir );
	dir = camEye - dir * 1.5f; 
	D3DXVECTOR3 pos = dir; 
	setPos( pos );

	switch( m_axis )
	{
		case XZ_AXIS:
			setAngle( D3DXToRadian( -90.0f ), D3DXToRadian( 0.0f ), D3DXToRadian( -90.0f  ) );
		break;
		case YZ_AXIS:
			setAngle( 0.0f, D3DXToRadian( -90.0f ), 0.0f );
		break; 
	}

	m_worldVar->SetMatrix( getWorld() );
	m_viewVar->SetMatrix( camera->getViewMatrix() );
	m_projectionVar->SetMatrix( camera->getProjMatrix() );

	device->IASetInputLayout( m_inputLayout );
	UINT stride = sizeof( AGColorVertex );
	UINT offset = 0; 
	device->IASetVertexBuffers( 0, 1, &m_vertexBuffer, &stride, &offset );

	device->OMSetDepthStencilState( m_depthState, 1 );

	for( int i = 0; i < desc.Passes; i++ )
	{
		m_technique->GetPassByIndex( i )->Apply( 0 );

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

float AGDXIntersectPlane::intersect(D3DXVECTOR3 rayOrigin, D3DXVECTOR3 rayDir)
{
	float retDist = -1.0f;
	for( int i = 0; i < 3; i++ )
	{
		D3DXVECTOR3 vertex1 = m_vertices[ i ];
		D3DXVECTOR3 vertex2 = m_vertices[ i + 1 ];
		D3DXVECTOR3 vertex3 = m_vertices[ i + 2 ];

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

D3DXVECTOR3 AGDXIntersectPlane::getAxis()
{
	if( m_axis == XY_AXIS )
		return D3DXVECTOR3( 1.0f, 1.0f, 0.0f );
	if( m_axis == XZ_AXIS )
		return D3DXVECTOR3( 1.0f, 0.0f, 1.0f );
	if( m_axis == YZ_AXIS )
		return D3DXVECTOR3( 0.0f, 1.0f, 1.0f );
	return D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
}

