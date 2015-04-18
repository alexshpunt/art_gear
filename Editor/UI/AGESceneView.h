#ifndef AGE_SCENEVIEW_H
#define AGE_SCENEVIEW_H

#include <string>

#include <QFrame>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QVBoxLayout>
#include <QLineEdit>

#include "Graphics/Objects/AGELight.h"

class AGEGameObject; 

class AGESceneViewItem : public QTreeWidgetItem
{
	public:
		AGESceneViewItem( AGEGameObject* gameObject );
		~AGESceneViewItem(); 

	private:
		AGEGameObject* m_gameObject; 
}; 

class AGESceneView : public QFrame
{
	public:
		AGESceneView();
		~AGESceneView();

		void addItem( AGESceneViewItem* item );

	private:
		QVBoxLayout* m_layout; 
		QLineEdit* m_searchEdit; 
		QTreeWidget* m_sceneView; 
};

#endif 