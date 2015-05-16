#include "AGEditor.h"

#include <QElapsedTimer>

#include "Engine/Managers/AGInputManager.h"
#include "Engine/Managers/AGTimeManager.h"
#include "Engine/Managers/AGGraphicsSettings.h"
#include "Managers/AGEStateManager.h"
#include "Engine/Managers/AGLogger.h"
#include "Engine/Graphics/AGGraphics.h"
#include "Engine/Graphics/Objects/AGMesh.h"
#include "Engine/Graphics/Objects/AGCamera.h"
#include "Engine/Graphics/Components/AGRenderer.h"
#include "Engine/Managers/AGResourceManager.h"
#include "Engine/Objects/AGGameScene.h"
#include "Engine/Objects/AGGameObject.h"

#include "Editor/Wrappers/Objects/AGEGameScene.h"
#include "Editor/Wrappers/Objects/AGEGameObject.h"

#include "Engine/AGEngine.h"

#include "Editor/Graphics/Manipulators/Dragger/AGDragger.h"
#include "Editor/Graphics/Manipulators/Rotater/AGRotater.h"
#include "Editor/Graphics/Manipulators/Scaler/AGScaler.h"

#include "Editor/Graphics/Objects/AGELight.h"

#include "Engine/Graphics/Objects/AGLight.h"

#include "Engine/Graphics/Managers/AGDebugManager.h"
#include "Editor/Managers/AGEResMngrStrategy.h"
#include "Engine/Graphics/Objects/AGBillboard.h"
#include "Engine/Graphics/Objects/AGTer.h"

#include "UI/AGELoadingWidgets.h"

#include <thread>
#include <future>

AGEditor::AGEditor()
{
#ifdef _DEBUG
	AGLogger::getInstance().setMode( AGLogger::Terminal );
#endif 

	setAttribute( Qt::WA_NativeWindow );
	setFocusPolicy( Qt::StrongFocus );
	setFocus();

	ui.setupUi(this);

	m_leftTopView = new AGEView;
	m_rightTopView = new AGEView;
	m_leftBotView = new AGEView; 
	m_rightBotView = new AGEView; 
	m_gridSplitter = new AGEGridSplitter( m_leftTopView, m_rightTopView, m_leftBotView, m_rightBotView );  
	m_toolBar = new AGEToolBar;
	m_sidePanel = new AGESidePanel; 
	m_sceneView = new AGESceneView; 
	m_mainHLayout = new QHBoxLayout; 
	m_mainVLayout = new QVBoxLayout; 

	m_mainVLayout->addWidget( m_toolBar );
	m_mainVLayout->setSpacing( 5 );
	m_mainVLayout->setMargin( 1 );

	m_mainHLayout->addWidget( m_sceneView );
	m_mainHLayout->addWidget( m_gridSplitter );
	m_mainHLayout->addWidget( m_sidePanel );

	m_mainVLayout->addLayout( m_mainHLayout );

	ui.centralWidget->setLayout( m_mainVLayout );
	m_run = false; 

	/*m_resourcesView = new AGEResourcesView;
	m_resourcesView->openFormMesh();
	m_resourcesView->show();*/
}

AGEditor::~AGEditor()
{

}

int AGEditor::run( QApplication& app )
{
	m_app = &app; 
	showMaximized();
	app.processEvents();
	
	AGGraphicsSettings::getInstance().setBackgroundColor( 0.22f, 0.22f, 0.22f );

	AGResourceManager::getInstance().setStrategy( new AGEResMngrStrategy( app ) );
	//AGResourceManager::getInstance().setStrategy( new AGResourceManagerStrategy() );

	ui.statusBar->showMessage( "Loading shaders" );
	AGResourceManager::getInstance().initShaders(); 
	ui.statusBar->showMessage( "Shaders are loaded" );

	m_leftBotView->getViewport()->setCameraMode( AGSurface::Left );
	m_leftTopView->getViewport()->setCameraMode( AGSurface::Top );
	m_rightTopView->getViewport()->setCameraMode( AGSurface::Front );

	m_leftBotView->getViewport()->setSurfaceMode( AGSurface::Wireframe );
	m_leftTopView->getViewport()->setSurfaceMode( AGSurface::Wireframe );
	m_rightTopView->getViewport()->setSurfaceMode( AGSurface::Wireframe );

	m_leftBotView->updateTop();
	m_leftTopView->updateTop();
	m_rightTopView->updateTop();

	//Существуют весь цикл работы программы, поэтому не нужно бояться утечек 
	AGGraphics::getInstance().addManipulator( new AGDragger );
	AGGraphics::getInstance().addManipulator( new AGRotater );
	AGGraphics::getInstance().addManipulator( new AGScaler  );

	AGGraphics::getInstance().createRasterizeStates(); 
	AGGraphics::getInstance().update(); 
	m_light = new AGLight; 

	m_scene = nullptr;
	newAction(); 	

	m_curFrame = 0;
	m_curTime = 0;

	m_run = true;
	QElapsedTimer timer; 
	
	/*ui.statusBar->showMessage( "Loading mesh data" );
	createObjAction();

	m_object->getRenderer()->setMesh( AGResourceManager::getInstance().getMesh( "trash.agmsh" ) );
	createLight();
	ui.statusBar->showMessage( "Ready" );*/
	m_rightBotView->getViewport()->setMaximizedMode( true );
	AGDebugManager::getInstance().init(); 

	/*AGRenderer* r = new AGRenderer( nullptr );
	r->setMesh( AGResourceManager::getInstance().getMesh( "skybox.agmsh" ) );
	r->setWorldPos( AGVec3( 0.0f, 0.0f, 0.0f ) );

	AGGraphics::getInstance().addRenderer( r );*/
	AGGraphics::getInstance().addClickableObject( new AGTer() );

	while( m_run )
	{
		app.processEvents();

		m_gridSplitter->update();

		timer.restart(); 

		//m_resourcesView->update();
		AGGraphics::getInstance().update(); 

		double dt = timer.restart() / 1000.0; 

		if( timeGetTime() >= m_curTime + 1000 )
		{
			AGGraphics::getInstance().setFPS( m_curFrame );
			m_curFrame = 0;
			m_curTime = timeGetTime(); 
		} 
		else
		{
			m_curFrame++; 
		}
		AGTimeManager::getInstance().setDeltaTime( dt );
		AGInput().update();
		AGEngine::getInstance().update(); 
		if( !AGInput().isButtonPressed( "RMB" ) && !AGInput().isButtonPressed( "MMB" ) && !AGInput().isButtonPressed( "LMB" ) )
		{
			AGEStateManager::getInstance().setRotating( false );
		}
		//m_sidePanel->setGameObject( m_scene->getSelectedObject() ); 
	}
	AGESceneLoadingWidget::getInstance().close();

	return 0;
}

void AGEditor::newAction()
{
	if( m_scene )
	{
		delete m_scene; 
	}
	m_scene = new AGEGameScene( "Default" );

}

void AGEditor::closeEvent(QCloseEvent *e)
{
	m_run = false; 
}

bool AGEditor::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
	MSG* msg = (MSG*)message; 
	unsigned int key = ( unsigned int )msg->wParam; 
	switch( msg->message )
	{
		break;
		case WM_KEYDOWN:
			AGInput().setKeyPressed( key, true );
		break;
		case WM_KEYUP:
			AGInput().setKeyPressed( key, false );
		break;
		case WM_MOUSEWHEEL:
			AGInput().setWheelDelta( GET_WHEEL_DELTA_WPARAM( msg->wParam ) );
		break; 
	}
	return false; 
}

void AGEditor::keyPressEvent(QKeyEvent *e)
{
	if( !AGEStateManager::getInstance().isConsoleMode() )
		return; 
	wchar_t c = e->text().toStdWString()[0];
	if( c == L'' )
		return; 
	if( e->nativeVirtualKey() == VK_OEM_3 )
		return;

	AGInput().setCharInput( c );
}

void AGEditor::createObjAction()
{
	/*m_object = m_scene->createObject( "Irish" );
	m_sceneView->addItem( m_object->getItem() );*/
}

void AGEditor::deleteObjAction()
{

}

void AGEditor::createLight()
{
	/*AGELight* light = new AGELight; 
	AGESceneViewItem* item = new AGESceneViewItem( light );
	light->getLight()->setLightType( AGLight::Point );
	m_sceneView->addItem( item ); */
}

void AGEditor::deleteLight()
{

}





