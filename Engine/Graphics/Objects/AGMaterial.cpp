#include "AGMaterial.h"

#include <windows.h>
#include <vector>

#include "Engine/Graphics/Objects/AGShader.h"
#include "Engine/Graphics/Interfaces/AGSurface.h"

#include "Engine/Managers/AGResourceManager.h"
#include "Engine/Graphics/AGGraphics.h"

#include "AGCamera.h"
#include "Managers/AGLogger.h"

#include "Engine/Graphics/Objects/Textures/AGTexture2D.h"

AGMaterial::AGMaterial()
{
	m_shader = nullptr; 

	m_surfaces = AGGraphics::getInstance().getSurfaces(); 

	/*for( int i = 0; i < 12; i++ )
	{
		m_resources[ i ] = nullptr; 
	}*/
}

AGMaterial::AGMaterial(AGMaterialLoadingData* data)
{
	m_shader = data->shader;
	for( int i = 0; i < 12; i++ )
	{
		m_resources[ i ] = AGResPtr( data->resources[ i ].getData() );
		m_textures[ i ] = data->textures[ i ];
	}
	//delete[] data->resources;
	m_surfaces = std::move( data->surfaces );
	m_type = data->type; 
}

AGMaterial::~AGMaterial()
{

}

const wstring& AGMaterial::getTexture( int index ) const
{
	if( index >= 0 && index < 12 )
		return m_textures[ index ];
	else 
		return m_textures[ 0 ];
}

void AGMaterial::loadFrom( ifstream& in )
{
	#define READ( a ) in.read( (char*)&a, sizeof( a ) )
	char buf[ 512 ];
	wchar_t wbuf[ 512 ];
	for( int i = 0; i < 12; i++ )
	{
		int len;
		READ( len );
		if( len > 511 )
		{
			AGError() << "Too long texture name"; 
			continue;
		}

		in.read( buf, len );
		buf[ len ] = '\0';
		mbstowcs( wbuf, buf, len + 1 ); 
		m_textures[ i ] = wbuf; 

		int zero; 
		READ( zero );
	}
	
	std::wstring fileName;

	const std::wstring shaderNames[] = 
	{
		L"amb",
		L"dif",
		L"spcclr",
		L"spclvl",
		L"gls",
		L"slfilm",
		L"opc",
		L"fltrclr",
		L"bmp",
		L"rfl",
		L"rfr",
		L"nrm"
	};

	for( int i = 0; i < 12; i++ )
	{
		std::wstring texture = m_textures[ i ];
		if( texture != L"NULL" )
		{
			fileName += shaderNames[ i ];
		}
	}

	m_shader = AGResourceManager::getInstance().getShader( fileName );

	list< AGSurface* > surfaces = AGGraphics::getInstance().getSurfaces(); 

	for( int i = 0; i < 12; i++ )
	{
		std::wstring textureName = m_textures[ i ];
		if( textureName != L"NULL" )
		{
			bool firstInit = true; 

			HANDLE texHandle; 

			int time = GetTickCount(); 

			AGTexture2D* texture = AGResourceManager::getInstance().getTexture( textureName );

			if( !texture->isValid() )
				return; 

			m_resources[ i ] = AGResPtr( texture ); 
		}
	}
}

void AGMaterial::apply()
{
	for( int i = 0; i < 12; i++ )
	{
		if( m_textures[ i ] != L"NULL" )
		{
			AGTexture2D* texture = (AGTexture2D*)m_resources[ i ].getData(); 
			for( AGSurface* surface : m_surfaces )
			{
				m_shader->setMap( i, texture, surface );
			}	
		}
	}
}

AGShader* AGMaterial::getShader() const
{
	return m_shader; 
}
