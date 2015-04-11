#ifndef AG_TEXTURE2D_H
#define AG_TEXTURE2D_H

#include <string>
#include <vector>

#include <d3dx10.h>
#include <d3d10.h>

#include "Engine/Interfaces/AGResource.h"

class AGSurface; 
class AGResourceManager; 

class AGTexture2DLoadingData
{
	public:
		std::vector< ID3D10ShaderResourceView* > views;
};

class AGTexture2D : public AGResource
{
	friend class AGResourceManager; 
	public:	
		AGTexture2D( AGTexture2DLoadingData* data );
		AGTexture2D( const std::wstring& fileName );
		~AGTexture2D();

		void apply( ID3D10EffectShaderResourceVariable* var, AGSurface* surface );

		unsigned int getType() const; 

	private:
		std::vector< ID3D10ShaderResourceView* > m_views; 
};

#endif 