#include "AGGraphics.h"

#include "Managers/AGLogger.h"
#include "Subsystems/DirectX10/AGDX10SubSys.h"

AGGraphics::AGGraphics()
{
	m_subSystem = nullptr; 
	m_window = new AGWindow; 
	m_window->show();

	AGSucces() << "Graphics system was created";
}

AGGraphics::~AGGraphics()
{
	delete m_window; 
	delete m_subSystem; 
}

void AGGraphics::update()
{
	if( m_subSystem )
	{
		m_subSystem->update(); 
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
			m_subSystem = new AGDX10SubSys( m_window ); 
			m_subSystem->initialize();
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

