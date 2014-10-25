#include "AGGraphics.h"

#include "Managers/AGLogger.h"
#include "Subsystems/DirectX10/AGDX10SubSys.h"

AGGraphics::AGGraphics()
{
	m_subSystem = nullptr; 
	/*m_window = new AGWindow; 
	m_window->show();*/
	m_window = nullptr; 
	AGSucces() << "Graphics system was created";
}

AGGraphics::~AGGraphics()
{
	delete m_window; 
	delete m_subSystem; 
}

void AGGraphics::setAGWindow(AGWindow* window)
{
	m_window = window;
	//AGDX10SubSys::getInstance().initialize( m_window );
}

void AGGraphics::update()
{
	switch( m_mode )
	{
		case DirectX10:
			/*if( m_window )
				AGDX10SubSys::getInstance().update();*/
		break;
		case DirectX11:
			AGSucces() << "Graphics systems mode was changed to DX11";
		break;
		case OpenGL3:
			AGSucces() << "Graphics systems mode was changed to OGL3";
		break;
		case OpenGL4:
			AGSucces() << "Graphics systems mode was changed to OGL4";
		break; 
	}
}

void AGGraphics::shutdown()
{
	AGSucces() << "Graphics system was shutdowned";
}

void AGGraphics::setMode(Modes mode)
{
	m_mode = mode; 
	switch( mode )
	{
		case DirectX10:
		//	AGDX10SubSys::getInstance().initialize( m_window ); 
			AGSucces() << "Graphics systems mode was changed to DX10";
		break;
		case DirectX11:
			AGSucces() << "Graphics systems mode was changed to DX11";
		break;
		case OpenGL3:
			AGSucces() << "Graphics systems mode was changed to OGL3";
		break;
		case OpenGL4:
			AGSucces() << "Graphics systems mode was changed to OGL4";
		break; 
	}
}

AGGraphics::Modes AGGraphics::getMode() const
{
	return m_mode;
}

AGWindow* AGGraphics::getMainWindow() const
{
	return m_window;
}



