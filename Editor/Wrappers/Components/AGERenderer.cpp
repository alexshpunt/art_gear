#include "AGERenderer.h"

#include "UI/ResourcesView/AGEResourcesView.h"

class AGEMeshWidget
{
	public:
		AGEMeshWidget()
		{
			m_layout = new QHBoxLayout;
			m_layout->setSpacing( 4 );
			m_label = new QLabel( "Mesh: " );
			m_button = new QPushButton( "none" );	
			m_layout->addWidget( m_label );
			m_layout->addWidget( m_button );
		}
		~AGEMeshWidget()
		{

		}

		QHBoxLayout* m_layout; 
		QLabel* m_label;
		QPushButton* m_button; 
};

AGERendererWidget::AGERendererWidget()
{
	m_layout = new QVBoxLayout( this );
	m_layout->setSpacing( 2 );
	m_meshWidget = new AGEMeshWidget;
	
	m_layout->addLayout( m_meshWidget->m_layout );

	m_mapWidgets.push_back( new AGEMapWidget( "Ambient" ) );
	m_mapWidgets.push_back( new AGEMapWidget( "Diffuse" ) );
	m_mapWidgets.push_back( new AGEMapWidget( "Specular Color" ) );
	m_mapWidgets.push_back( new AGEMapWidget( "Specular Level" ) );
	m_mapWidgets.push_back( new AGEMapWidget( "Glossiness" ) );
	m_mapWidgets.push_back( new AGEMapWidget( "Self-Illumination" ) );
	m_mapWidgets.push_back( new AGEMapWidget( "Opacity" ) );
	m_mapWidgets.push_back( new AGEMapWidget( "Filter Color" ) );
	m_mapWidgets.push_back( new AGEMapWidget( "Bump" ) );
	m_mapWidgets.push_back( new AGEMapWidget( "Reflection" ) );
	m_mapWidgets.push_back( new AGEMapWidget( "Refraction" ) );
	m_mapWidgets.push_back( new AGEMapWidget( "Normals" ) );

	m_label = new QLabel( "Maps: " );
	m_layout->addWidget( m_label );
	
	m_sep1 = new QFrame;
	m_sep1->setFrameStyle( QFrame::HLine | QFrame::Sunken );
	m_sep2 = new QFrame;
	m_sep2->setFrameStyle( QFrame::HLine | QFrame::Sunken );

	m_layout->addWidget( m_sep1 );
	for( AGEMapWidget* widget : m_mapWidgets )
	{
		m_layout->addLayout( widget->m_layout );
	}
	m_layout->addWidget( m_sep2 );
}

AGERendererWidget::~AGERendererWidget()
{

}


AGEMapWidget::AGEMapWidget(const QString& map)
{
	m_layout = new QHBoxLayout;

	m_label = new QLabel( map );
	m_label->setMaximumWidth( 100 );
	m_spinBox = new QSpinBox;
	m_spinBox->setRange( 0, 100 );
	m_spinBox->setMaximumWidth( 50 );
	m_button = new QPushButton( "none" );

	m_layout->addWidget( m_label );
	m_layout->addWidget( m_spinBox );
	m_layout->addWidget( m_button );

	QSpacerItem* spacer = new QSpacerItem( 15, 0 );
	m_layout->addSpacerItem( spacer );

	QPixmap image( QDir::currentPath() + "/data/textures/344.jpg" );
	image = image.scaled( 48, 48 );
	m_preview = new QLabel;
	m_preview->setMaximumWidth( 48 );
	m_preview->setPixmap( image );
	m_layout->addWidget( m_preview );

	QSpacerItem* endSpacer = new QSpacerItem( 15, 0 );
	m_layout->addSpacerItem( endSpacer ); 

	connect( m_button, SIGNAL( pressed() ), this, SLOT( mapButtonPressed() ) );
	//connect( m_button, SIGNAL( pressed() ), this, SLOT( mapButtonPressed() ) );
}

AGEMapWidget::~AGEMapWidget()
{

}

void AGEMapWidget::mapButtonPressed()
{
	AGEResourcesView::getInstance().openForTexture();
}