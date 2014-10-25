#include "AGEditor.h"

#include <QLayout>
#include <QDebug>
#include <QPushButton>
#include <QElapsedTimer>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "Managers/AGInputManager.h"
#include "Managers/AGTimeManager.h"
#include "Managers/AGLogger.h"
#include "Graphics/Subsystems/DirectX10/Objects/AGDX10Camera.h"
#include "Graphics/Subsystems/DirectX10/Objects/AGDX10Scene.h"
#include "Graphics/Subsystems/DirectX10/Objects/AGDX10Mesh.h"

AGEditor::AGEditor()
{
	AGLogger::getInstance().setMode( AGLogger::Console );
	AGLogger::getInstance().initialize(); 

	setAttribute( Qt::WA_NativeWindow );
	ui.setupUi(this);
	m_view = new AGEView; 

	m_mainVLayout.addWidget( &m_toolBar );
	m_mainVLayout.setSpacing( 1 );
	m_mainVLayout.setMargin( 1 );

	m_mainHLayout.addWidget( m_view );
	m_mainHLayout.setSpacing( 1 );
	m_mainHLayout.setMargin( 1 );

	m_mainVLayout.addLayout( &m_mainHLayout );

	ui.centralWidget->setLayout( &m_mainVLayout );
	m_run = false; 

	m_scene = new AGDX10Scene;
	m_mesh = new AGDX10Mesh;
	m_camera = new AGDX10Camera; 

	m_mesh->loadFrom( "data/meshes/irish.agmsh", m_view->getDevice() );
	m_scene->addCamera( m_camera );
	m_scene->addMesh( m_mesh );

	m_view->setScene( m_scene );
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
		m_view->update();
	}
	return 0;
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




