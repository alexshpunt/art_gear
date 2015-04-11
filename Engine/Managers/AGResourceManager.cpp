#include "AGResourceManager.h"

#include "Engine/Graphics/Objects/AGMesh.h"

#include "Engine/Graphics/AGGraphics.h"
#include "Engine/Managers/AGLogger.h"

#include  "Engine/Graphics/Objects/Textures/AGTexture2D.h"

#include <windows.h>

#include <assert.h>

void AGResourceManager::initShaders()
{
	assert( m_strategy );

	m_strategy->initShaders(); 
}

AGShader* AGResourceManager::getShader(const std::wstring& shaderName)
{
	assert( m_strategy );
	
	return m_strategy->getShader( shaderName );	
}

AGMesh* AGResourceManager::getMesh( const std::string& fileName )
{
	assert( m_strategy );

	return m_strategy->getMesh( fileName );
}

AGTexture2D* AGResourceManager::getTexture( const std::wstring& fileName )
{
	assert( m_strategy );

	return m_strategy->getTexture( fileName );
}

void AGResourceManager::releaseResource(AGResource* res, const std::wstring& name, unsigned int type)
{
	assert( m_strategy );

	if( type == AGResourceType::Texture )
	{
		auto iter =  m_strategy->m_textures.find( name ); 

		if( iter == m_strategy->m_textures.end() )
		{
			return;
		}

		m_strategy->m_textures.erase( iter );
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
		auto iter = m_strategy->m_meshes.find( name ); 

		if( iter == m_strategy->m_meshes.end() )
		{
			return;
		}

		m_strategy->m_meshes.erase( iter );
		delete res; 
	}
}

void AGResourceManager::init()
{
	m_strategy = nullptr; 
}

void AGResourceManager::setStrategy(AGResourceManagerStrategy* strategy)
{
	if( m_strategy )
	{
		delete m_strategy; 
		m_strategy = nullptr; 
	}

	m_strategy = strategy; 
}


AGResourceManagerStrategy::~AGResourceManagerStrategy()
{
	
}

void AGResourceManagerStrategy::initShaders()
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

AGShader* AGResourceManagerStrategy::getShader(const std::wstring& shaderName)
{
	auto iter = m_effects.find( shaderName );

	if( iter == m_effects.end() )
		return nullptr; 
	return iter->second;
}

AGMesh* AGResourceManagerStrategy::getMesh(const std::string& fileName)
{
	auto iter = m_meshes.find( fileName ); 

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

AGTexture2D* AGResourceManagerStrategy::getTexture(const std::wstring& fileName)
{
	auto iter = m_textures.find( fileName ); 

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
