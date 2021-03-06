#include "AGEngine.h"

#include "Managers/AGConsoleManager.h"
#include "Managers/AGInputManager.h"
#include "Managers/AGEventHandler.h"
#include "Managers/AGLogger.h"
#include "Graphics/AGGraphics.h"
#include "Math/AGSize.h"

#include "Objects/AGGameScene.h"

void AGEngine::init()
{
	m_scene = nullptr;
}

int AGEngine::run()
{
	AGSucces() << "AGEngine starts working";
	MSG msg = {}; 
	while( msg.message != WM_QUIT )
	{
		if( PeekMessage( &msg, 0, 0, 0, PM_REMOVE ) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
		{
			update(); 
		}
	}
	return 0;
}

void AGEngine::update()
{
	if( AGEStateManager::getInstance().isConsoleMode() && AGInput().isCharInput() )
	{
		AGConsoleManager::getInstance().pushChar( AGInput().getCharInput() ); 
	}
	if( m_scene )
	{
		m_scene->update(); 
	}
	AGGraphics::getInstance().update();
}

void AGEngine::setScene(AGGameScene* scene)
{
	m_scene = scene; 
}

AGGameScene* AGEngine::getScene() const
{
	return m_scene; 
}


