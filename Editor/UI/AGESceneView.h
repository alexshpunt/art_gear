#ifndef AGE_SCENEVIEW_H
#define AGE_SCENEVIEW_H

#include <string>

#include <QFrame>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QVBoxLayout>
#include <QLineEdit>

#include "Graphics/Objects/AGELight.h"

#include "Objects/AGGameObject.h"

class AGESceneViewItem : public QTreeWidgetItem
{
	enum AGEItemType{ GameObject, Light };
	public:
		AGESceneViewItem( AGGameObject* gameObject );
		AGESceneViewItem( AGELight* light );
		~AGESceneViewItem(); 

	private:
		AGEItemType m_type; 
		void* m_data; 
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