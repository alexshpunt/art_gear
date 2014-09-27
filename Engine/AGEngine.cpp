#include "AGEngine.h"

#include "Managers/AGEventHandler.h"
#include "Managers/AGLogger.h"
#include "Graphics/AGGraphics.h"
#include "Math/AGSize.h"

AGEngine::AGEngine()
{
#ifdef _DEBUG
	AGLogger::getInstance().initialize();
	AGLogger::getInstance().setMode( AGLogger::Terminal );
#endif 
	AGGraphics* graphics = new AGGraphics;
	graphics->setMode( AGGraphics::DirectX10 ); 
	m_systems.push_back( graphics );

	AGSucces() << "AGEngine was created";
}

AGEngine::~AGEngine()
{
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

void AGEngine::update()
{
	for( int i = 0; i < m_systems.size(); i++ )
	{
		m_systems[ i ]->update(); 
	}
}

void AGEngine::shutdown()
{
	AGSucces() << "AGEngine was succesfully shutdowned";
}

