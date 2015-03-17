#ifndef AG_RESOURCEMANAGER_H
#define AG_RESOURCEMANAGER_H

#include <string>
#include <map>
#include <list>

#include <d3dx10.h>
#include <d3d10.h>

#include "Engine/Graphics/Objects/AGShader.h"

#include "Patterns/Singleton.h"

class AGMesh;
class AGTexture2D; 
class AGResource; 

class AGResourceManager 
{
	DECLARE_SINGLETON( AGResourceManager )
	public:
		enum AGResourceType{ Mesh, Texture, Shader };
		
		void initShaders(); 
		AGShader* getShader( const std::wstring& shaderName );

		AGMesh* getMesh( const std::string& fileName );
		AGTexture2D* getTexture( const std::wstring& fileName );

		void releaseResource( AGResource* res, const std::wstring& name, unsigned int type );
		void releaseResource( AGResource* res, const std::string& name, unsigned int type );
	private:
		std::map< std::wstring, AGShader* > m_effects; 
		std::map< std::string, AGMesh* > m_meshes; 
		std::map< std::wstring, AGTexture2D* > m_textures; 
};

#endif 