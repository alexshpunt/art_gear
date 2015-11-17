#ifndef AGE_TRANSFORMPANEL_H 
#define AGE_TRANSFORMPANEL_H 

#include <QFrame>
#include <QLineEdit>
#include <QCheckBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "AGESidePanel.h"

#include "Interfaces/AGObject.h"

#include "Functors/AGGameObjectNotifyFunctor.h"

#include "Objects/AGGameObject.h"

#include "ui_AGETransformPanel.h"

class AGETransformPanelNotifyer;

class AGETransformPanel : public AGESidePanelWidget, public AGObject
{
	Q_OBJECT 
	friend class AGETransformPanelNotifyer;

	public:
		AGETransformPanel();
		~AGETransformPanel();

		void setGameObject( AGGameObject* gameObject ) override; 
		char* getName() const override; 

	private slots:	
		void nameChanged( const QString& text );
		void visiableChanged( int state ); 
		
		void spinBoxPosXChanged( double value ); 
		void spinBoxPosYChanged( double value ); 
		void spinBoxPosZChanged( double value ); 

		void spinBoxRotXChanged( double value ); 
		void spinBoxRotYChanged( double value ); 
		void spinBoxRotZChanged( double value ); 

		void spinBoxScaleXChanged( double value ); 
		void spinBoxScaleYChanged( double value ); 
		void spinBoxScaleZChanged( double value ); 

	private:
		Ui::ui_AGTransformPanel m_ui; 

		QVBoxLayout* m_mainLayout; 
		QHBoxLayout* m_layout; 

		QLabel* m_panelName; 

		QLineEdit* m_nameEdit; 
		QLabel* m_nameLabel;

		QCheckBox* m_visiableCheckBox; 
		QLabel* m_visiableLabel; 

		AGGameObject* m_gameObject; 

		AGETransformPanelNotifyer* m_notifyer; 

		bool m_changeGameObject; 
};

class AGETransformPanelNotifyer : public AGGameObjectNotifyFunctor
{
	public:
		AGETransformPanelNotifyer( AGETransformPanel* panel ); 

		void operator()( AGGameObject::Change change ); 
	private:
		AGETransformPanel* m_panel; 
};

#endif 