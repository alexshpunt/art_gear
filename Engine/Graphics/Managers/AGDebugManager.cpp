#include "AGDebugManager.h"

#include <vector>

#include <Graphics/AGGraphics.h>

#include "Utils/AGConversion.h"

class AGDebugManagerPrivate 
{
	public:
		AGSurface* surface; 
		AGColor color; 

		std::vector< ID3DX10Font* > devices; 
};

void AGDebugManager::init()
{
	m_p = new AGDebugManagerPrivate; 

	list< AGSurface* > surfaces = AGGraphics::getInstance().getSurfaces(); 

	D3DX10_FONT_DESC fontDesc; 
	fontDesc.Height = 16; 
	fontDesc.Width = 0;
	fontDesc.Weight = 0;
	fontDesc.MipLevels = 1;
	fontDesc.Italic = false;
	fontDesc.CharSet = OUT_DEFAULT_PRECIS;
	fontDesc.Quality = DEFAULT_QUALITY; 
	fontDesc.PitchAndFamily = DEFAULT_PITCH; 

	wcscpy_s( fontDesc.FaceName, L"Arial" );

	m_p->devices.resize( surfaces.size() );

	for( AGSurface* surface : surfaces )
	{
		D3DX10CreateFontIndirect( surface->getDevice(), &fontDesc, &m_p->devices.at( surface->getId() ) ); 
	}
}

void AGDebugManager::setCurrentSurface(AGSurface* surface)
{
	m_p->surface = surface; 
}

void AGDebugManager::setTextColor(const AGColor& color)
{
	m_p->color = color; 
}

void AGDebugManager::drawText(AGRect rect, wchar_t* text, AGSurface* surface)
{
	const AGColor& color = m_p->color; 

	m_p->devices.at( surface->getId() )->DrawTextW( 0, text, -1,
		&AGConversion::toWinAPIRect( rect ), DT_NOCLIP, AGConversion::toD3DXColor( color ) );
}

void AGDebugManager::drawText(AGRect rect, std::wstring& text, AGSurface* surface)
{
	const AGColor& color = m_p->color; 

	m_p->devices.at( surface->getId() )->DrawTextW( 0, text.c_str(), -1,
		&AGConversion::toWinAPIRect( rect ), DT_NOCLIP, AGConversion::toD3DXColor( color ) );
}

void AGDebugManager::drawText(AGRect rect, int value, AGSurface* surface)
{
	const AGColor& color = m_p->color; 

	m_p->devices.at( surface->getId() )->DrawTextW( 0, std::to_wstring( value ).c_str(), -1,
		&AGConversion::toWinAPIRect( rect ), DT_NOCLIP, AGConversion::toD3DXColor( color ) );
}

