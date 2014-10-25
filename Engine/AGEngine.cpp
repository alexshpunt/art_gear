#include "AGEngine.h"

#include "Managers/AGEventHandler.h"
#include "Managers/AGLogger.h"
#include "Graphics/AGGraphics.h"
#include "Math/AGSize.h"

AGEngine::AGEngine()
{

}

AGEngine::~AGEngine()
{

}

void AGEngine::initialize()
{
#ifdef _DEBUG
	AGLogger::getInstance().initialize();
	AGLogger::getInstance().setMode( AGLogger::Terminal );
#endif 
	m_graphics.setMode( AGGraphics::DirectX10 ); 
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
	shutdown(); 
	return 0;
}

void AGEngine::processEvents()
{
	MSG msg = {}; 
	if( PeekMessage( &msg, 0, 0, 0, PM_REMOVE ) )
	{
		TranslateMessage( &msg );
		DispatchMessage( &msg );
	}
	{
		update(); 
	}
}

void AGEngine::update()
{
	m_graphics.update();
}

void AGEngine::shutdown()
{
	AGSucces() << "AGEngine was succesfully shutdowned";
}

AGGraphics& AGEngine::getGraphicsSystem()
{
	return m_graphics; 
}



