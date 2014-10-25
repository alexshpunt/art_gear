#ifndef AGEDITOR_H
#define AGEDITOR_H

#include <QtWidgets/QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "UI/AGEView.h"
#include "UI/AGEToolBar.h"
#include "ui_ageditor.h"

#include "Engine/Patterns/Singleton.h"

class AGDX10Scene;
class AGDX10Camera;
class AGDX10Mesh;

class AGEditor : public QMainWindow
{
	Q_OBJECT
	public:
		AGEditor();
		~AGEditor();

		int run( QApplication& app ); 

	protected:
		void closeEvent(QCloseEvent *e);
		bool nativeEvent( const QByteArray &eventType, void *message, long *result );

	private:
		bool m_run; 
		Ui::AGEditorClass ui;
		AGEView* m_view;

		QVBoxLayout m_mainVLayout;
		QHBoxLayout m_mainHLayout; 

		AGEToolBar m_toolBar; 

		AGDX10Camera* m_camera;
		AGDX10Mesh* m_mesh;
		AGDX10Scene* m_scene; 
};

#endif // AGEDITOR_H
