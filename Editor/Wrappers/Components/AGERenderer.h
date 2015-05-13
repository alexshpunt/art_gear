#ifndef AGE_RENDERER_H
#define AGE_RENDERER_H

#include <list>

#include <QObject>
#include <QFrame>
#include <QWidget>
#include <QVBoxLayout>
#include <QPixmap>
#include <QLabel>
#include <QDir>
#include <QString>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSpinBox>
#include <QSpacerItem>

#include "Editor/Wrappers/Components/AGEComponent.h"

class AGEMapWidget; 
class AGEMeshWidget; 

class AGEMapWidget : public QObject
{
	Q_OBJECT
	public:
		AGEMapWidget( const QString& map );
		~AGEMapWidget();

		QHBoxLayout* m_layout; 
		QLabel* m_label;
		QLabel* m_preview;
		QSpinBox* m_spinBox;
		QPushButton* m_button; 

	private slots: 
		void mapButtonPressed();

};

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