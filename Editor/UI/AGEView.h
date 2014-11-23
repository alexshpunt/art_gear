#ifndef AGE_VIEW_H
#define AGE_VIEW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "AGEWindow.h"

class AGEViewTop;
class AGEViewBottom; 
class AGDXScene;
class ID3D10Device;

class AGEView : public QWidget 
{
	Q_OBJECT
	public:
		AGEView();
		~AGEView();

		void update();

		AGEWindow* getViewport();

	private:
		QVBoxLayout m_layout; 
		AGEViewTop* m_top;
		AGEViewBottom* m_bottom; 

		AGEWindow m_window; 
};

#endif 