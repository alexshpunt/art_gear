#include "AGEResourcePreview.h"

#include <QResizeEvent>
#include "Engine/Graphics/Objects/AGCamera.h"

AGEResourcePreview::AGEResourcePreview() : AGSurface()
{
	setMinimumSize( 100, 100 );
	resize( 800, 600 );
	setAttribute( Qt::WA_PaintOnScreen );
	setAttribute( Qt::WA_NativeWindow );

	setup( 800, 600, (HWND)winId(), false );

	m_camera->setPos( AGVec3( 0.0f, 5.0f, -10.0f ) );
	this->setSurfaceMode( AGSurface::Simple );

	m_mesh = nullptr;
}

AGEResourcePreview::~AGEResourcePreview()
{

}

QPaintEngine* AGEResourcePreview::paintEngine() const
{
	return nullptr; 
}

void AGEResourcePreview::resizeEvent(QResizeEvent* event)
{
	resizeSurface( event->size().width(), event->size().height() );
}

void AGEResourcePreview::setMesh(AGMesh* mesh)
{
	m_mesh = mesh;
}

void AGEResourcePreview::update()
{
	this->clearRenderTargets();
	this->setRenderTargets(); 
	if( m_mesh )
	{
		m_mesh->draw( this );
	}
	this->present();
	this->swapChainPresent(); 
}

