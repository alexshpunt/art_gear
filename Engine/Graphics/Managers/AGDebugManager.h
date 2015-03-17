#ifndef AG_DEBUGMANAGER_H
#define AG_DEBUGMANAGER_H

#include <string>

#include "Graphics/Interfaces/AGSurface.h"

#include "Math/AGMath.h"

#include "Patterns/Singleton.h"

class AGDebugManagerPrivate; 

class AGDebugManager 
{
	DECLARE_SINGLETON( AGDebugManager );
	public:
		void init(); 

		void setCurrentSurface( AGSurface* surface );
		void setTextColor( const AGColor& color );

		void drawText( AGRect rect, wchar_t* text, AGSurface* surface );
		void drawText( AGRect rect, std::wstring& text, AGSurface* surface );
		void drawText( AGRect rect, int value, AGSurface* surface );

	private:
		AGDebugManagerPrivate* m_p; 
};

#endif 