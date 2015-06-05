#include "AGTexture2D.h"

#include <list>

#include "Engine/Managers/AGResourceManager.h"
#include "Engine/Managers/AGLogger.h"

#include "Engine/Graphics/Interfaces/AGSurface.h"

#include "Engine/Graphics/AGGraphics.h"

#include "Engine/Utils/AGErrorHandling.h"

AGTexture2D::AGTexture2D( D3D10_TEXTURE2D_DESC* desc, D3D10_SUBRESOURCE_DATA* data)
{
	D3D10_SHADER_RESOURCE_VIEW_DESC srDesc; 
	srDesc.Format = desc->Format; 
	srDesc.Texture2D.MipLevels = desc->MipLevels; 
	srDesc.Texture2D.MostDetailedMip = 0; 
	srDesc.ViewDimension = D3D10_SRV_DIMENSION_TEXTURE2D; 

	std::list< AGSurface* > surfaces = AGGraphics::getInstance().getSurfaces(); 

	for( AGSurface* surface : surfaces )
	{
		ID3D10ShaderResourceView* srView; 
		ID3D10Texture2D* texture = nullptr;
		handleDXError( surface->getDevice()->CreateTexture2D( desc, data, &texture ) );
		ID3D10Resource* res; 
		handleDXError( texture->QueryInterface( __uuidof( ID3D10Resource ), (void**)&res ) );
		handleDXError( surface->getDevice()->CreateShaderResourceView( res, &srDesc, &srView ) );
		m_views.push_back( srView );
		texture->Release();
	}
}

AGTexture2D::AGTexture2D(const std::wstring& fileName)
{
	std::wstring fullPath = L"data/textures/";
	fullPath += fileName; 

	std::list< AGSurface* > surfaces = AGGraphics::getInstance().getSurfaces(); 
	bool firstInit = true; 

	HANDLE texHandle;

	D3DX10_IMAGE_LOAD_INFO loadInfo; 
	ZeroMemory( &loadInfo, sizeof( D3DX10_IMAGE_LOAD_INFO ) );
	loadInfo.BindFlags = D3D10_BIND_SHADER_RESOURCE; 
	loadInfo.MiscFlags = D3D10_RESOURCE_MISC_SHARED; 
	loadInfo.Format = DXGI_FORMAT_BC1_UNORM; 

	for( AGSurface* surface : surfaces )
	{
		ID3D10ShaderResourceView* view; 

		if( firstInit )
		{
			HRESULT hr = D3DX10CreateShaderResourceViewFromFile( surface->getDevice(), &fullPath[ 0 ], &loadInfo, NULL, &view, NULL );
			if( FAILED( hr ) )
			{
				AGError() << "Couldn't load texture: " << fullPath << " " << DXGetErrorDescription( hr ) << AGErrorSnippet; 
				return; 
			}

			AGSucces() << fileName << " was loaded";

			ID3D10Resource* resource; 

			view->GetResource( &resource );

			IDXGIResource* res( NULL );
			handleDXError( resource->QueryInterface( __uuidof( IDXGIResource ), (void**)&res ) );

			hr = res->GetSharedHandle( &texHandle );

			if( FAILED( hr ) )
			{
				AGError() << "Cant get shared handle " << DXGetErrorDescription( hr ) << AGErrorSnippet; 
			}
			else
			{
				firstInit = false;
			}
		}
		else 
		{
			IDXGIResource* resource;

			HRESULT hr = surface->getDevice()->OpenSharedResource( texHandle, __uuidof( IDXGIResource ), (void**)&resource );

			if( FAILED( hr ) )
			{
				AGError() << "Couldn't open shared resource" << " " << DXGetErrorString( hr ) << AGErrorSnippet; 
				return; 
			}

			ID3D10Resource* res;
			hr = resource->QueryInterface( __uuidof( ID3D10Resource ), (void**)&res ); 

			if( FAILED( hr ) )
			{
				AGError() << "Can't quary interface ID3D10Resource" << AGErrorSnippet; 
				return; 
			}

			D3D10_SHADER_RESOURCE_VIEW_DESC srvDesc; 
			D3D10_RESOURCE_DIMENSION type; 
			res->GetType( &type );

			if( type == D3D10_RESOURCE_DIMENSION_TEXTURE2D )
			{
				D3D10_TEXTURE2D_DESC desc;
				ID3D10Texture2D* texture = (ID3D10Texture2D*)res; 
				texture->GetDesc( &desc );

				srvDesc.Format = desc.Format; 
				srvDesc.Texture2D.MipLevels = desc.MipLevels;
				srvDesc.Texture2D.MostDetailedMip = 0; 
				srvDesc.ViewDimension = D3D10_SRV_DIMENSION_TEXTURE2D; 
			}

			hr = surface->getDevice()->CreateShaderResourceView( res, &srvDesc, &view );
			if( FAILED( hr ) )
			{
				AGError() << "Cant create shader resource view " << DXGetErrorDescription( hr ) << AGErrorSnippet; 
			}
		}

		m_views.push_back( view ); 
	}
	m_isValid = true; 
}

AGTexture2D::AGTexture2D(AGTexture2DLoadingData* data)
{
	m_views = std::move( data->views );
	m_isValid = true; 
}

AGTexture2D::~AGTexture2D()
{
	for( ID3D10ShaderResourceView* view : m_views )
	{
		view->Release(); 
	}
	m_views.clear(); 
}

void AGTexture2D::apply(ID3D10EffectShaderResourceVariable* var, AGSurface* surface)
{
	if( var->IsValid() )
	{
		var->SetResource( m_views[ surface->getId() ] );
	}
}

unsigned int AGTexture2D::getType() const
{
	return AGResourceManager::Texture; 
}

