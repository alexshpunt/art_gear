#ifndef AG_TEXTURE2D_H
#define AG_TEXTURE2D_H

#include <string>
#include <vector>

#include <d3dx10.h>
#include <d3d10.h>

#include "Engine/Interfaces/AGResource.h"

class AGSurface; 
class AGResourceManager; 

class AGTexture2D : public AGResource
{
	friend class AGResourceManager; 
	public:	
		void apply( ID3D10EffectShaderResourceVariable* var, AGSurface* surface );

		unsigned int getType() const; 

	private:
		AGTexture2D( const std::wstring& fileName );
		~AGTexture2D();

		std::vector< ID3D10ShaderResourceView* > m_views; 
};

#endif 