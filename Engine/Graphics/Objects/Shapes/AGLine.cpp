#include "AGLine.h"

#include "Managers/AGResourceManager.h"

AGLine::AGLine(D3DXVECTOR3 startPoint, D3DXVECTOR3 endPoint, D3DXVECTOR4 color )
{
	m_shader = AGResourceManager::getInstance().getShader( L"shape" );
	m_vertexBuffer = nullptr; 

	setLine( startPoint, endPoint, color );
}

AGLine::~AGLine()
{

}

void AGLine::setLine( D3DXVECTOR3 startPoint, D3DXVECTOR3 endPoint, D3DXVECTOR4 color )
{
	if( m_vertexBuffer )
		delete m_vertexBuffer; 

	vector< AGPrimitiveVertex > vertices; 

	AGPrimitiveVertex vertex; 
	vertex.color = color;

	vertex.pos = startPoint; 
	vertices.push_back( vertex );
	
	vertex.pos = endPoint; 
	vertices.push_back( vertex );
	
	m_vertexBuffer = new AGBuffer< AGPrimitiveVertex >( vertices, AGBufferType::Vertex );

}

void AGLine::draw( AGSurface* surface )
{
	ID3D10Device* device = surface->getDevice(); 

	m_shader->applySurface( surface );
	m_shader->setWorldMatrix( getLocalMatrix() ); 	

	device->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_LINELIST );

	ID3D10Buffer* vertexBuffer = m_vertexBuffer->applyTo( device ); 

	AGInputLayout* layout = AGGraphics::getInstance().getInputLayout( device );

	device->IASetInputLayout( layout->colorVertexInputLayout );
	UINT stride = sizeof( AGPrimitiveVertex );

	UINT offset = 0; 
	device->IASetVertexBuffers( 0, 1, &vertexBuffer, &stride, &offset );

	while( m_shader->applyNextPass() )
	{
		device->Draw( 2, 0 );
	}
}

