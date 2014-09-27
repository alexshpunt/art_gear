#include "AGAbstractSubSystem.h"

AGAbstractSubsystem::AGAbstractSubsystem(AGWindow* window) : m_window( window )
{
}

AGAbstractSubsystem::~AGAbstractSubsystem()
{
	delete m_window; 
}

