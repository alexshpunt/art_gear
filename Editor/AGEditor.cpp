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

#include "Engine/AGEngine.h"

#include "Editor/Graphics/Manipulators/Dragger/AGDragger.h"
#include "Editor/Graphics/Manipulators/Rotater/AGRotater.h"
#include "Editor/Graphics/Manipulators/Scaler/AGScaler.h"

#include "Editor/Graphics/Objects/AGELight.h"

#include "Engine/Graphics/Objects/AGLight.h"

#include "Engine/Graphics/Managers/AGDebugManager.h"

#include "Engine/Graphics/Objects/AGBillboard.h"

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

	AGGraphicsSettings::getInstance().setBackgroundColor( 0.22f, 0.22f, 0.22f );

	AGResourceManager::getInstance().initShaders(); 

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
	m_light = new AGLight; 

	m_scene = nullptr;
	newAction(); 	

	m_curFrame = 0;
	m_curTime = 0;
}

AGEditor::~AGEditor()
{

}

int AGEditor::run( QApplication& app )
{
	show();
	app.processEvents();

	m_run = true;
	QElapsedTimer timer; 
	
	ui.statusBar->showMessage( "Loading shaders" );
	ui.statusBar->showMessage( "Shaders are loaded" );

	ui.statusBar->showMessage( "Loading mesh data" );
	createObjAction();
	m_object->getRenderer()->setMesh( AGResourceManager::getInstance().getMesh( "trash.agmsh" ) );
	createLight();
	ui.statusBar->showMessage( "Ready" );

	AGDebugManager::getInstance().init(); 

	while( m_run )
	{
		app.processEvents();

		m_gridSplitter->update();

		timer.restart(); 

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
		if( !AGInput().isButtonPressed( "RMB" ) && !AGInput().isButtonPressed( "MMB" ) )
		{
			AGEStateManager::getInstance().setRotating( false );
		}
		m_sidePanel->setGameObject( m_scene->getSelectedObject() ); 
	}
	return 0;
}

void AGEditor::newAction()
{
	if( m_scene )
	{
		delete m_scene; 
	}
	m_scene = new AGGameScene( "Default" );

	AGEngine::getInstance().setScene( m_scene );
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
	m_object = m_scene->createObject( "Irish" );
	AGESceneViewItem* item = new AGESceneViewItem( m_object );
	m_sceneView->addItem( item );
}

void AGEditor::deleteObjAction()
{

}

void AGEditor::createLight()
{
	AGELight* light = new AGELight; 
	AGESceneViewItem* item = new AGESceneViewItem( light );
	light->getLight()->setLightType( AGLight::Daylight );
	m_sceneView->addItem( item ); 
}

void AGEditor::deleteLight()
{

}




