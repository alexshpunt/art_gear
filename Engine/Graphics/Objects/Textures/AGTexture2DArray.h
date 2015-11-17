#ifndef AG_TEXTURE2DARRAY_H
#define AG_TEXTURE2DARRAY_H

#include <string>
#include <vector>

#include <d3dx10.h>
#include <d3d10.h>

#include "Engine/Interfaces/AGResource.h"

class AGSurface; 
class AGResourceManager; 

class AGTexture2DArray : public AGResource
{
	friend class AGResourceManager; 
	public:	
		enum Type{ Dynamic, Static };

		AGTexture2DArray( Type type );
		~AGTexture2DArray();

		void setTextures( std::vector< std::wstring >&& texture );
		void append( std::wstring fileName );
		void append( const D3D10_TEXTURE2D_DESC& desc );
		void reloadArray(); 

		void apply( ID3D10EffectShaderResourceVariable* var, AGSurface* surface );

		unsigned int getType() const; 

	private:
		Type m_type; 
		std::vector< std::vector< ID3D10Texture2D* > > m_textures; 
		std::vector< std::wstring > m_texturesNames; 
		std::vector< ID3D10ShaderResourceView* > m_views; 
};

#endif 