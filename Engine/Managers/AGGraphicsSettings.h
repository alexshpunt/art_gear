#ifndef AG_GRAPHICSSETTINGS_H
#define AG_GRAPHICSSETTINGS_H

#include "Patterns/Singleton.h"
#include "Math/AGMath.h"

class AGGraphicsSettings 
{
	DECLARE_SINGLETON_INIT( AGGraphicsSettings )
	public:
		enum GraphicsSystem { DX, OGL };

		void setScreenWidth( int width );
		int getScreenWidth() const;

		void setScreenHeight( int height );
		int getScreenHeight() const; 

		AGSize getSize();

		float getAspectRatio(); 

		void setGraphicsSystem( GraphicsSystem graphicsSystem );
		GraphicsSystem getGraphicsSystem() const; 

		void setBackgroundColor( const AGPoint3& color );
		void setBackgroundColor( float r, float g, float b );
		AGPoint3 getBackgroundColor() const; 

	private:
		void init();

		float m_screenWidth;
		float m_screenHeight; 
		AGPoint3 m_backgroundColor; 

		GraphicsSystem m_system; 
};

#endif 