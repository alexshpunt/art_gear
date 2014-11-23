#ifndef AGE_WINDOW_H
#define AGE_WINDOW_H

#include <d3d10.h>
#include <d3dx10.h>
#include <QWidget>

#include "Engine/Graphics/AGWindow.h"
#include "Engine/Graphics/Interfaces/AGSurface.h"

class AGDXMesh;
class AGDXScene; 
class AGDXCamera; 

class AGEWindow : public QWidget, public AGDXSurface
{
	Q_OBJECT
	public:
		AGEWindow();
		~AGEWindow();

		QPaintEngine* paintEngine() const; 
	protected:
		void paintEvent( QPaintEvent* event );
		void resizeEvent( QResizeEvent* event );
		bool nativeEvent( const QByteArray &eventType, void *message, long *result );
	private:
		
};

#endif 