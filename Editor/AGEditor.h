#ifndef AGEDITOR_H
#define AGEDITOR_H

#include <string>
#include <QWidget>
#include <QDockWidget>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QKeyEvent>
#include <QHBoxLayout>
#include <QSplitter>

#include "UI/AGEView.h"
#include "UI/AGEToolBar.h"
#include "UI/AGESceneView.h"
#include "UI/AGESidePanel.h"
#include "UI/AGEGridSplitter.h"
#include "ui_ageditor.h"

#include "Engine/Patterns/Singleton.h"

#include "Editor/Graphics/Manipulators/Dragger/AGDragger.h"

#include <Engine/Graphics/Objects/AGLight.h>
#include "Graphics/Manipulators/Dragger/AGArrow.h"

class AGGameScene;
class AGGameObject; 
class AGCamera; 

class AGEditor : public QMainWindow
{
	Q_OBJECT
	public:
		AGEditor();
		~AGEditor();

		int run( QApplication& app ); 

		void newAction(); 
		void createObjAction();
		void deleteObjAction(); 

		void createLight();
		void deleteLight(); 

	protected:
		void closeEvent(QCloseEvent *e);
		void keyPressEvent(QKeyEvent *e);
		bool nativeEvent( const QByteArray &eventType, void *message, long *result );
	private: 

		bool m_run; 
		Ui::AGEditorClass ui;
		
		int m_curFrame; 
		int m_curTime; 

		AGEView* m_rightTopView;
		AGEView* m_leftTopView;
		AGEView* m_rightBotView;
		AGEView* m_leftBotView;
		AGEGridSplitter* m_gridSplitter; 

		QVBoxLayout* m_mainVLayout;
		QHBoxLayout* m_mainHLayout; 

		AGEToolBar* m_toolBar; 
		
		QDockWidget* m_viewportDock;
		QDockWidget* m_sidePanelDock;
		QDockWidget* m_sceneViewDock; 
		QDockWidget* m_toolBarDock;

		AGESidePanel* m_sidePanel;
		AGESceneView* m_sceneView; 

		AGGameObject* m_object; 
		AGGameScene* m_scene;

		AGDragger* m_dragger; 

		AGLight* m_light; 

		QApplication* m_app; 
};

#endif // AGEDITOR_H
