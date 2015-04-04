#ifndef AG_VERTEXBUFFER_H
#define AG_VERTEXBUFFER_H

#include <windows.h>

#include <d3dx10.h>
#include <d3d10.h>
#include <DxErr.h>
#include <map>

#include <vector>
#include <list>

#include <Engine/Managers/AGLogger.h>

#include <Engine/Graphics/AGGraphics.h>

enum AGBufferType { Vertex, Index };

///////////////////////////////////////////////////////////////////////////
////////////////////////Interface//////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

template < class T > 
class AGBuffer
{
	public:
		AGBuffer( std::vector< T > vertices, AGBufferType bufferType );
		~AGBuffer();

		//Return buffer for specific ID3D10Device
		ID3D10Buffer* applyTo( ID3D10Device* device );

		void apply( AGSurface* surface ); 

	private:
		std::map< ID3D10Device*, ID3D10Buffer* > m_buffers; 
		ID3D10Buffer* m_buffer; 
		AGBufferType m_type; 
};

///////////////////////////////////////////////////////////////////////////
///////////////////////Implementation//////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

template < class T >
AGBuffer<T>::AGBuffer( std::vector< T > vertices, AGBufferType bufferType )
{
	m_type = bufferType; 

	ID3D10Device* device = AGGraphics::getInstance().getDevice();

	std::list< AGSurface* > surfaces = AGGraphics::getInstance().getSurfaces(); 

	if( !device )
	{
		AGError() << "Device = nullptr " << AGCurFileFunctionLineSnippet; 
		return; 
	}

	D3D10_BUFFER_DESC buffDesc; 

	buffDesc.Usage = D3D10_USAGE_DEFAULT; 
	buffDesc.ByteWidth = sizeof( T ) * vertices.size(); 
	buffDesc.CPUAccessFlags = 0;
	buffDesc.MiscFlags = 0;
	buffDesc.BindFlags = bufferType == AGBufferType::Vertex ? D3D10_BIND_VERTEX_BUFFER : D3D10_BIND_INDEX_BUFFER; 
	buffDesc.MiscFlags = D3D10_RESOURCE_MISC_SHARED;

	D3D10_SUBRESOURCE_DATA subresData; 
	subresData.pSysMem = &vertices[0];

	for( AGSurface* surface : surfaces )
	{
		ID3D10Buffer* buffer; 
		HRESULT hr = surface->getDevice()->CreateBuffer( &buffDesc, &subresData, &buffer );
		if( FAILED( hr ) )
		{
			AGError() << DXGetErrorDescription( hr ); 
			return; 
		}
		m_buffers[ surface->getDevice() ] = buffer; 
	}
}

template < class T >
AGBuffer<T>::~AGBuffer()
{
	for( auto iter : m_buffers )
	{
		ID3D10Buffer* buffer = iter.second; 
		buffer->Release(); 
	}
}

template < class T >
ID3D10Buffer* AGBuffer<T>::applyTo( ID3D10Device* device)
{
	std::map< ID3D10Device*, ID3D10Buffer* >::iterator iter = m_buffers.find( device ); 
	if( iter == m_buffers.end() )
		return nullptr;
	else 
		return  iter->second; 
}

template < class T >
void AGBuffer<T>::apply(AGSurface* surface)
{
	std::map< ID3D10Device*, ID3D10Buffer* >::iterator iter = m_buffers.find( surface->getDevice() ); 
	if( iter == m_buffers.end() )
	{
		AGWarning() << "There is no buffer for device"; 
	}
	else 
	{
		if( m_type == Index )
		{
			surface->getDevice()->IASetIndexBuffer( iter->second, DXGI_FORMAT_R32_UINT, 0 ); 
		}
		else if( m_type == Vertex )
		{
			UINT stride = sizeof( AGPrimitiveVertex );
			UINT offset = 0; 
			surface->getDevice()->IASetVertexBuffers( 0, 1, &iter->second, &stride, &offset );
		}
	}
}

#endif 