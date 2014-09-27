#ifndef AG_GRAPHICS_H
#define AG_GRAPHICS_H

#include "AGWindow.h"
#include "Interfaces/AGAbstractSystem.h"
#include "Subsystems/AGAbstractSubSystem.h"

class AGGraphics : public AGAbstractSystem
{
	public:
		enum Modes{ DirectX10, DirectX11, OpenGL3, OpenGL4 };

		AGGraphics();
		~AGGraphics();

		void update();
		void shutdown();

		void setMode( Modes mode );
		Modes getMode() const; 

	private:
		AGAbstractSubsystem* m_subSystem; 
		Modes m_mode; 
		AGWindow* m_window; 
};

#endif 