#include "AGEView.h"

#include <QSpacerItem>
#include <QComboBox>
#include <QStringList>
#include <QDebug>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QLineEdit>
#include <QSizePolicy>
#include <QLabel>

#include "Engine/Graphics/AGGraphics.h"

AGEView::AGEView()
{
	m_top = new AGEViewTop( this );

	setMinimumSize( 50, 50 );
	setFocusPolicy( Qt::ClickFocus );
	QSizePolicy sizePolicy;
	sizePolicy.setVerticalPolicy( QSizePolicy::Expanding );
	sizePolicy.setHorizontalPolicy( QSizePolicy::Expanding );
	setSizePolicy( sizePolicy );
	setMouseTracking( true );
	m_layout.addWidget( m_top );
	m_layout.addWidget( &m_window );
	m_layout.setSpacing( 0 );
	setLayout( &m_layout );
	m_layout.setMargin( 0 );
	setStyleSheet( "color: rgb( 50, 50, 50 )" );
	setFrameStyle( QFrame::Box );
	setLineWidth( 2 );

	m_top->m_fovSpinBox->setValue( m_window.getCamera()->getFov() ); 
	m_top->m_cameraModeComboBox->setCurrentIndex( m_window.getCameraMode() );
	m_top->m_renderModeComboBox->setCurrentIndex( m_window.getSurfaceMode() );
}

AGEView::~AGEView()
{
}

void AGEView::update()
{
	m_window.update();
	QWidget::update();
}

AGEWindow* AGEView::getViewport()
{
	return &m_window;
}

void AGEView::mouseMoveEvent(QMouseEvent *ev)
{
	setCursor( Qt::ArrowCursor );
}

void AGEView::focusInEvent(QFocusEvent *)
{
	setStyleSheet( "color: rgb( 116, 121, 87 )" );
	AGGraphics::getInstance().setFocusSurface( &m_window );
}

void AGEView::focusOutEvent(QFocusEvent *)
{
	setStyleSheet( "color: rgb( 50, 50, 50 )" );
	AGGraphics::getInstance().setFocusSurface( nullptr );
}

void AGEView::updateTop()
{
	if( m_window.getCamera()->getFov() != m_top->m_fovSpinBox->value() )
		m_top->m_fovSpinBox->setValue( m_window.getCamera()->getFov() ); 

	if( m_window.getCameraMode() != m_top->m_cameraModeComboBox->currentIndex() )
		m_top->m_cameraModeComboBox->setCurrentIndex( m_window.getCameraMode() );

	if( m_window.getSurfaceMode() != m_top->m_renderModeComboBox->currentIndex() )
		m_top->m_renderModeComboBox->setCurrentIndex( m_window.getSurfaceMode() );
}


AGEViewTop::AGEViewTop(AGEView* view)
{
	m_view = view; 

	m_label = new QLabel( this ); 
	m_label->setText( "Fov: " );
	setMaximumHeight( 40 );
	setStyleSheet( "background: rgb( 70, 70, 70 ); color: white");
	setLayout( &m_layout );
	m_renderModeComboBox = new QComboBox( this );
	m_renderModeComboBox->addItems( QStringList() << "Wireframe" << "Simple" << "Shaded" << "Edged Faces" );

	m_cameraModeComboBox = new QComboBox( this );
	m_cameraModeComboBox->addItems( QStringList() << "Perspective" << "Orthographics" << "Top" << 
		"Bottom" << "Left" << "Right" << "Back" << "Front" );

	m_layout.addWidget( m_renderModeComboBox );
	m_layout.addWidget( m_cameraModeComboBox );

	m_fovSpinBox = new QSpinBox; 
	m_fovSpinBox->setRange( 10, 120 ); 
	m_fovSpinBox->setSingleStep( 1 ); 

	m_layout.addWidget( m_label );
	m_layout.addWidget( m_fovSpinBox );

	m_button = new QPushButton; 
	m_button->setCheckable( true );
	m_layout.addWidget( m_button );

	m_spacerItem = new QSpacerItem( 1000, 40 );
	m_layout.addSpacerItem( m_spacerItem );

	connect( m_fovSpinBox, SIGNAL( valueChanged( int ) ), this, SLOT( fovSpinBoxValueChanged( int ) ) );
	connect( m_cameraModeComboBox, SIGNAL( currentIndexChanged( int ) ),
		this, SLOT( cameraModeComboBoxChanged( int ) ) );
	connect( m_renderModeComboBox, SIGNAL( currentIndexChanged( int ) ),
		this, SLOT( renderModeComboBoxChanged( int ) ) );
	connect( m_button, SIGNAL( clicked( bool ) ), this, SLOT( maximizedButtonClicked( bool ) ) );
}

AGEViewTop::~AGEViewTop()
{

}

void AGEViewTop::fovSpinBoxValueChanged(int value)
{
	AGCamera* camera = m_view->getViewport()->getCamera(); 
	if( !camera )
		return; 

	camera->setFov( value );
}

void AGEViewTop::renderModeComboBoxChanged( int i )
{
	AGEWindow* window = m_view->getViewport(); 

	window->setSurfaceMode( (AGSurface::AGSurfaceMode)i );
}

void AGEViewTop::cameraModeComboBoxChanged( int i )
{
	AGEWindow* window = m_view->getViewport(); 
	window->setCameraMode( (AGSurface::AGSurfaceCameraMode)i );

}

void AGEViewTop::maximizedButtonClicked(bool value)
{
	m_view->getViewport()->setMaximizedMode( value );
}
