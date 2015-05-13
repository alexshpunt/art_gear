#ifndef AGE_RESOURCESVIEW_H
#define AGE_RESOURCESVIEW_H

#include <QToolBar>
#include <QString>
#include <QWidget>
#include <QListWidget>
#include <QListView>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QDialogButtonBox>
#include <QGraphicsView>
#include <QGraphicsScene>

#include "AGEResourcePreview.h"

#include "Engine/Graphics/Objects/AGMesh.h"
#include "Engine/Graphics/Objects/AGShader.h"
#include "Engine/Graphics/Objects/Textures/AGTexture2D.h"

#include "Engine/Patterns/Singleton.h"

class AGEResourcesView : public QWidget 
{
	Q_OBJECT
	DECLARE_SINGLETON_INIT( AGEResourcesView )
	public:
		void openFormMesh(); 
		void openForTexture( const QString& string = QString() ); 
		void update();

		void resizeEvent(QResizeEvent *r);

	public slots:
		void itemDoubleClicked( QListWidgetItem* item );
	private:
		void init();

		enum Mode{ Mesh, Texture };

		Mode m_mode; 

		QGraphicsView* m_texturePreview; 
		QGraphicsScene* m_scene; 
		AGEResourcePreview* m_preview; 
		QDialogButtonBox* m_dialog;
		QLabel* m_label; 
		QListWidget* m_listWidget; 
		QHBoxLayout* m_horLayout;
		QVBoxLayout* m_vertLayout; 
		QToolBar* m_toolbar; 
};

#endif 