#include "AGEditor.h"

#include <QElapsedTimer>

#include "Managers/AGInputManager.h"
#include "Managers/AGTimeManager.h"
#include "Managers/AGStateManager.h"
#include "Managers/AGLogger.h"
#include "AGEngine.h"
#include "Graphics/AGGraphics.h"
#include "Graphics/Objects/AGDXMesh.h"
#include "Graphics/Objects/AGDXCamera.h"
#include "Graphics/Components/AGRenderer.h"
#include "Objects/AGScene.h"
#include "Objects/AGObject.h"

AGEditor::AGEditor()
{
#ifdef _DEBUG
	AGLogger::getInstance().setMode( AGLogger::Terminal );
#endif 

	setAttribute( Qt::WA_NativeWindow );
	ui.setupUi(this);

	m_view = new AGEView; 
	m_toolBar = new AGEToolBar;
	m_mainHLayout = new QHBoxLayout; 
	m_mainVLayout = new QVBoxLayout; 
	m_splillter = new QSplitter; 

	m_mainVLayout->addWidget( m_toolBar );
	m_mainVLayout->setSpacing( 1 );
	m_mainVLayout->setMargin( 1 );

	m_splillter->addWidget( m_view );

	m_mainVLayout->addWidget( m_splillter );

	ui.centralWidget->setLayout( m_mainVLayout );
	m_run = false; 

	AGGraphics::getInstance().setBackgroundColor( 0.22f, 0.22f, 0.22f );
	AGGraphics::getInstance().addSurface( m_view->getViewport() );

	m_scene = nullptr;
	newAction(); 	

	m_object = m_scene->createObject( "Irish" );
	m_object->getRenderer()->loadMeshFrom( "data/meshes/irish.agmsh", m_view->getViewport()->getDevice() );
	//m_object->setPivot( 2.0f, 2.0f, 2.0f );
	//m_object->setPos( 10.0f, 0.0f, 0.0f );
}

AGEditor::~AGEditor()
{

}

int AGEditor::run( QApplication& app )
{
	show();
	m_run = true;
	QElapsedTimer timer; 
	
	while( m_run )
	{
		app.processEvents();
		double dt = timer.restart() / 1000.0; 
		AGTimeManager::getInstance().setDeltaTime( dt );
		AGEngine::getInstance().update(); 
		m_view->update();
		AGInput().update();
		if( !AGInput().isButtonPressed( "RMB" ) && !AGInput().isButtonPressed( "LMB" ) )
		{
			AGStateManager::getInstance().setRotating( false );
		}
	}
	return 0;
}

void AGEditor::newAction()
{
	if( m_scene )
	{
		delete m_scene; 
	}
	m_scene = new AGScene( "Default" );
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




