#ifndef AGE_VIEW_H
#define AGE_VIEW_H

#include <QFrame>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QResizeEvent>
#include <QPushButton>
#include <QSpacerItem>
#include <QComboBox>
#include <QStringList>
#include <QDebug>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QLineEdit>
#include <QSizePolicy>
#include <QLabel>

#include <Engine/Graphics/Objects/AGCamera.h>

#include "AGEWindow.h"

class AGEViewTop;
class AGEViewBottom; 
class AGScene;
class ID3D10Device;

class AGEView : public QFrame 
{
	Q_OBJECT
	public:
		AGEView();
		~AGEView();

		void update();
		void updateTop(); 

		AGEWindow* getViewport();

	protected:
		void mouseMoveEvent(QMouseEvent *ev);
		void focusInEvent(QFocusEvent *);
		void focusOutEvent(QFocusEvent *);

	private:
		QVBoxLayout m_layout; 
		AGEViewTop* m_top;

		AGEWindow m_window; 
};

class AGEViewTop : public QWidget
{
	friend class AGEView; 
	Q_OBJECT 
	public:	
		AGEViewTop( AGEView* view );
		~AGEViewTop();

	protected slots:
		void fovSpinBoxValueChanged( int value );
		void renderModeComboBoxChanged( int i );
		void cameraModeComboBoxChanged( int i );
		void maximizedButtonClicked( bool value ); 

	private:
		AGEView* m_view; 
		QLabel* m_label; 
		QComboBox* m_renderModeComboBox; 
		QComboBox* m_cameraModeComboBox;
		QSpinBox* m_fovSpinBox; 
		QPushButton* m_button; 
		QHBoxLayout m_layout; 
		QSpacerItem* m_spacerItem; 
};

#endif 