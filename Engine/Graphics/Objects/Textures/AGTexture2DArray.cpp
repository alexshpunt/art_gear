#include "AGTexture2DArray.h"

#include <list>

#include "Engine/Managers/AGResourceManager.h"
#include "Engine/Managers/AGLogger.h"

#include "Engine/Graphics/Interfaces/AGSurface.h"

#include "Engine/Graphics/AGGraphics.h"

#include "Engine/Utils/AGErrorHandling.h"

AGTexture2DArray::AGTexture2DArray()
{

}

AGTexture2DArray::~AGTexture2DArray()
{
	for( ID3D10ShaderResourceView* view : m_views )
	{
		view->Release(); 
	}
	m_views.clear(); 
}

void AGTexture2DArray::apply(ID3D10EffectShaderResourceVariable* var, AGSurface* surface)
{
	if( var->IsValid() )
	{
		var->SetResource( m_views[ surface->getId() ] );
	}
}

unsigned int AGTexture2DArray::getType() const
{
	return AGResourceManager::Texture; 
}

void AGTexture2DArray::append(std::wstring fileName)
{
	m_textures.push_back( fileName );
}

void AGTexture2DArray::setTextures(std::vector< std::wstring >&& texture)
{
	m_textures = std::move( texture );
}

void AGTexture2DArray::reloadArray()
{
	std::vector< std::vector< ID3D10Texture2D* > > textures; 

	std::list< AGSurface* > surfaces = AGGraphics::getInstance().getSurfaces(); 

	for( std::wstring txName : m_textures )
	{
		D3DX10_IMAGE_LOAD_INFO loadInfo; 

		loadInfo.Width = D3DX10_FROM_FILE; 
		loadInfo.Height = D3DX10_FROM_FILE; 
		loadInfo.Depth = D3DX10_FROM_FILE;
		loadInfo.FirstMipLevel = 0; 
		loadInfo.MipLevels = D3DX10_FROM_FILE; 
		loadInfo.Usage = D3D10_USAGE_STAGING; 
		loadInfo.BindFlags = 0; 
		loadInfo.CpuAccessFlags = D3D10_CPU_ACCESS_WRITE | D3D10_CPU_ACCESS_READ; 
		loadInfo.MiscFlags = 0; 
		loadInfo.Format = DXGI_FORMAT_R8G8B8A8_UNORM; 
		loadInfo.Filter = D3DX10_FILTER_NONE; 
		loadInfo.MipFilter = D3DX10_FILTER_NONE; 
		loadInfo.pSrcInfo = 0;   

		std::vector< ID3D10Texture2D* > srcTex; 
		ID3D10Texture2D* texture; 

		for( AGSurface* surface : surfaces )
		{
			handleDXError( D3DX10CreateTextureFromFile( surface->getDevice(), txName.c_str(), &loadInfo, 0, (ID3D10Resource**)&texture, 0 ) );
			srcTex.push_back( texture );
		}
		textures.push_back( srcTex );
	}

	D3D10_TEXTURE2D_DESC txDesc; 
	textures.at( 0 ).at( 0 )->GetDesc( &txDesc );

	D3D10_TEXTURE2D_DESC txArrayDesc; 
	ZeroMemory( &txArrayDesc, sizeof( txArrayDesc ) );
	txArrayDesc.Width = txDesc.Width; 
	txArrayDesc.Height = txDesc.Height; 
	txArrayDesc.MipLevels = txDesc.MipLevels; 
	txArrayDesc.ArraySize = 4;
	txArrayDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	txArrayDesc.SampleDesc.Count = 1; 
	txArrayDesc.SampleDesc.Quality = 0; 
	txArrayDesc.Usage = D3D10_USAGE_DEFAULT;
	txArrayDesc.BindFlags = D3D10_BIND_SHADER_RESOURCE; 

	std::vector< ID3D10Texture2D* > txArray;
	
	for( AGSurface* surface : surfaces )
	{
		ID3D10Texture2D* texture = nullptr;
		surface->getDevice()->CreateTexture2D( &txArrayDesc, 0, &texture );
		for( int i = 0; i < textures.size(); i++ )
		{
			for( int j = 0; j < txDesc.MipLevels; j++ )
			{
				D3D10_MAPPED_TEXTURE2D mappedTex;
				textures.at( i ).at( surface->getId() )->Map( j, D3D10_MAP_READ, 0, &mappedTex );

				surface->getDevice()->UpdateSubresource( texture, 
					D3D10CalcSubresource( j, i, txDesc.MipLevels ),
					0, mappedTex.pData ,mappedTex.RowPitch, 0 );

				textures.at( i ).at( surface->getId() )->Unmap( j );
			}
		}
		txArray.push_back( texture );
	}

	D3D10_SHADER_RESOURCE_VIEW_DESC viewDesc; 
	viewDesc.Format = txArrayDesc.Format; 
	viewDesc.ViewDimension = D3D10_SRV_DIMENSION_TEXTURE2DARRAY; 
	viewDesc.Texture2DArray.MostDetailedMip = 0;
	viewDesc.Texture2DArray.MipLevels = txArrayDesc.MipLevels; 
	viewDesc.Texture2DArray.FirstArraySlice = 0;
	viewDesc.Texture2DArray.ArraySize = textures.at( 0 ).size(); 

	for( AGSurface* surface : surfaces )
	{
		ID3D10ShaderResourceView* view; 
		surface->getDevice()->CreateShaderResourceView( txArray.at( surface->getId() ), &viewDesc, &view );
		m_views.push_back( view );
	}

	for( ID3D10Texture2D* texture : txArray )
	{
		texture->Release(); 
	}

	for( int i = 0; i < textures.size(); i++ )
	{
		for( int j = 0; j < textures.at( i ).size(); j++ )
		{
			textures.at( i ).at( j )->Release(); 
		}
	}

}


