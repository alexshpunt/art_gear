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
		AGTexture2DArray();
		~AGTexture2DArray();

		void setTextures( std::vector< std::wstring >&& texture );
		void append( std::wstring fileName );
		void reloadArray(); 

		void apply( ID3D10EffectShaderResourceVariable* var, AGSurface* surface );

		unsigned int getType() const; 

	private:
		std::vector< std::wstring > m_textures; 
		std::vector< ID3D10ShaderResourceView* > m_views; 
};

#endif 