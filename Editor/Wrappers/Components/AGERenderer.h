#ifndef AGE_RENDERER_H
#define AGE_RENDERER_H

#include <list>

#include <QFrame>
#include <QWidget>
#include <QVBoxLayout>
#include <QPixmap>
#include <QLabel>

#include "Editor/Wrappers/Components/AGEComponent.h"

class AGEMapWidget; 
class AGEMeshWidget; 

class AGERendererWidget : public QWidget
{
	Q_OBJECT
	public:
		AGERendererWidget();
		~AGERendererWidget(); 

	private:
		QVBoxLayout* m_layout;
		QLabel* m_label;
		QFrame* m_sep1;
		QFrame* m_sep2; 
		std::list< AGEMapWidget* > m_mapWidgets;
		AGEMeshWidget* m_meshWidget; 
};


#endif 