#ifndef AGEDITOR_H
#define AGEDITOR_H

#include <string>
#include <QtWidgets/QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSplitter>

#include "UI/AGEView.h"
#include "UI/AGEToolBar.h"
#include "UI/AGESceneView.h"
#include "ui_ageditor.h"

#include "Engine/Patterns/Singleton.h"

class AGScene;
class AGObject; 
class AGDXCamera; 

class AGEditor : public QMainWindow
{
	Q_OBJECT
	public:
		AGEditor();
		~AGEditor();

		int run( QApplication& app ); 

		void newAction(); 

	protected:
		void closeEvent(QCloseEvent *e);
		bool nativeEvent( const QByteArray &eventType, void *message, long *result );
	private:
		bool m_run; 
		Ui::AGEditorClass ui;
		AGEView* m_view;

		QVBoxLayout* m_mainVLayout;
		QHBoxLayout* m_mainHLayout; 
		QSplitter* m_splillter; 

		AGEToolBar* m_toolBar; 

		AGObject* m_object; 
		AGScene* m_scene;
};

#endif // AGEDITOR_H
