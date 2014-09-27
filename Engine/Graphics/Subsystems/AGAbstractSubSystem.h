#ifndef AG_ABSTRACTSUBSYSTEM_H
#define AG_ABSTRACTSUBSYSTEM_H

#include "Graphics/AGWindow.h"

class AGAbstractSubsystem
{
	public:
		AGAbstractSubsystem( AGWindow* window ); 
		virtual ~AGAbstractSubsystem();

		virtual void initialize() = 0;
		virtual void update() = 0; 

	protected:
		AGWindow* m_window;
};

#endif 