#ifndef AGE_RESOURCESVIEW_H
#define AGE_RESOURCESVIEW_H

#include <QWidget>
#include <QListWidget>
#include <QListView>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QDialogButtonBox>

#include "AGEResourcePreview.h"

#include "Engine/Graphics/Objects/AGMesh.h"
#include "Engine/Graphics/Objects/AGShader.h"
#include "Engine/Graphics/Objects/Textures/AGTexture2D.h"

class AGEResourcesView : public QWidget 
{
	Q_OBJECT
	public:
		AGEResourcesView();
		~AGEResourcesView();

		void openFormMesh(); 
		void update();

	public slots:
		void itemDoubleClicked( QListWidgetItem* item );
	private:
		AGEResourcePreview* m_preview; 
		QDialogButtonBox* m_dialog;
		QLabel* m_label; 
		QListWidget* m_listWidget; 
		QHBoxLayout* m_horLayout;
		QVBoxLayout* m_vertLayout; 
};

#endif 