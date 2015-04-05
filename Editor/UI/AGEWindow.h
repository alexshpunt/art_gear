#ifndef AGE_WINDOW_H
#define AGE_WINDOW_H

#include <d3d10.h>
#include <d3dx10.h>
#include <QKeyEvent>
#include <QWidget>

#include "Engine/Graphics/AGWindow.h"
#include "Engine/Graphics/Interfaces/AGSurface.h"

class AGMesh;
class AGScene; 
class AGCamera; 

class AGEWindow : public QWidget, public AGSurface
{
	Q_OBJECT
	public:
		AGEWindow();
		~AGEWindow();
		void update(); 
		QPaintEngine* paintEngine() const; 

	protected:
		void resizeEvent( QResizeEvent* event );
		bool nativeEvent( const QByteArray &eventType, void *message, long *result );	

};

#endif 