#include "AGResourceManager.h"

#include "Engine/Graphics/Objects/AGMesh.h"

#include "Engine/Graphics/AGGraphics.h"
#include "Engine/Managers/AGLogger.h"

#include  "Engine/Graphics/Objects/Textures/AGTexture2D.h"

#include <windows.h>

void AGResourceManager::initShaders()
{
	HANDLE findHandle = INVALID_HANDLE_VALUE; 
	WIN32_FIND_DATA findData; 

	findHandle = FindFirstFile( L"data\\shaders\\*.*", &findData );

	if( findHandle == INVALID_HANDLE_VALUE )
	{
		AGError() << "Error while finding first file in data/shaders/" << (int)GetLastError(); 
		FindClose( findHandle );
		return; 
	}

	AGDebug() << "List of shaders: "; 
	do
	{
		if( ~( findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) && ( findData.cFileName[ 0 ] != '.' ) )
		{
			std::wstring shaderName = findData.cFileName; 

			AGShader* shader = new AGShader( shaderName );
			
			shaderName = shaderName.substr( 0, shaderName.find( L"." ) );
			m_effects[ shaderName ] = shader;

			AGDebug() << "Shader: " << shaderName; 
		}
	}
	while( FindNextFile( findHandle, &findData ) );
	FindClose( findHandle );
}

AGShader* AGResourceManager::getShader(const std::wstring& shaderName)
{
	std::map< std::wstring, AGShader* >::iterator iter = m_effects.find( shaderName );

	if( iter == m_effects.end() )
		return nullptr; 
	return iter->second;
}

AGMesh* AGResourceManager::getMesh( const std::string& fileName )
{
	std::map< std::string, AGMesh* >::iterator iter = m_meshes.find( fileName ); 

	AGMesh* mesh = nullptr; 

	if( iter == m_meshes.end() )
	{
		mesh = new AGMesh( fileName );
		m_meshes[ fileName ] = mesh; 
	}
	else 
	{
		mesh = iter->second; 
	}
	return mesh; 
}

AGTexture2D* AGResourceManager::getTexture( const std::wstring& fileName )
{
	std::map< std::wstring, AGTexture2D* >::iterator iter = m_textures.find( fileName ); 

	AGTexture2D* texture = nullptr; 

	if( iter == m_textures.end() )
	{
		texture = new AGTexture2D( fileName );
		m_textures[ fileName ] = texture; 
	}
	else 
	{
		texture = iter->second; 
	}
	return texture; 
}

void AGResourceManager::releaseResource(AGResource* res, const std::wstring& name, unsigned int type)
{
	if( type == AGResourceType::Texture )
	{
		std::map< std::wstring, AGTexture2D* >::iterator iter = m_textures.find( name ); 

		if( iter == m_textures.end() )
		{
			return;
		}

		m_textures.erase( iter );
		delete res; 
	}
	else if( type == AGResourceType::Shader )
	{
		
	}
}

void AGResourceManager::releaseResource(AGResource* res, const std::string& name, unsigned int type)
{
	if( type == AGResourceType::Mesh )
	{
		std::map< std::string, AGMesh* >::iterator iter = m_meshes.find( name ); 

		if( iter == m_meshes.end() )
		{
			return;
		}

		m_meshes.erase( iter );
		delete res; 
	}
}

