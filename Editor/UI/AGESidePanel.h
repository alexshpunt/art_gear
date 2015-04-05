#ifndef AGE_SIDEPANEL_H
#define AGE_SIDEPANEL_H

#include <QFrame>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QVBoxLayout>
#include <QSpacerItem>

#include "AGETransformPanel.h"

#include "Objects/AGGameObject.h"

class AGESidePanel : public QTreeWidget
{
	Q_OBJECT

	public:
		AGESidePanel();
		~AGESidePanel();
	
		void setGameObject( AGGameObject* gameObject );

	private:
		QVBoxLayout* m_layout;
		QSpacerItem* m_spacer; 

		QTreeWidgetItem* m_item; 
		QTreeWidgetItem* m_widgetItem; 
		AGETransformPanel* m_transformPanel;  

		QTreeWidgetItem* m_item1; 
		QTreeWidgetItem* m_widgetItem1; 
		AGETransformPanel* m_transformPanel1; 
};

#endif 