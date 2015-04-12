#include "AGEResourcesView.h"

#include <QDebug>
#include <QDir>
#include <QListWidgetItem>
#include <QFileInfo>

#include "Engine/Managers/AGResourceManager.h"

AGEResourcesView::AGEResourcesView()
{
	this->setStyleSheet( "background: rgb( 80, 80, 80 ); color: white; " );
	m_listWidget = new QListWidget; 
	m_listWidget->setStyleSheet( 
		"\
		 QListWidget\
		 {\
			show-decoration-selected: 1;\
			background: rgb( 80, 80, 80 ); color: white;\
			font: 10pt \"Leelawadee\";\
		 }\
		 QListWidget::item \
		 {\
			border: 2px;\
			border-style: solid;\
			border-color: rgb( 70, 70, 70 );\
			background: rgb( 90, 90, 90 );\
		 }\
		 "
	);
	m_listWidget->setSelectionMode( QAbstractItemView::NoSelection );
	m_label = new QLabel; 
	m_label->setStyleSheet( 
		"background: rgb( 60, 60, 60 );\
		 color: white; \
		 font: 10pt \"Leelawadee\";\
		"
	);
	m_preview = new AGEResourcePreview;
	m_preview->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
	m_horLayout = new QHBoxLayout;
	m_horLayout->addWidget( m_listWidget );
	m_horLayout->addWidget( m_preview );
	m_horLayout->setSpacing( 2 );
	m_vertLayout = new QVBoxLayout( this ); 
	m_vertLayout->addWidget( m_label );
	m_vertLayout->addLayout( m_horLayout );
	m_dialog = new QDialogButtonBox( QDialogButtonBox::Ok | QDialogButtonBox::Cancel );
	m_vertLayout->addWidget( m_dialog );
	m_vertLayout->setSpacing( 2 );

	connect( m_listWidget, SIGNAL( itemDoubleClicked( QListWidgetItem* ) ), this, SLOT( itemDoubleClicked( QListWidgetItem* ) ) );

	resize( 640, 480 );
}

AGEResourcesView::~AGEResourcesView()
{
}

void AGEResourcesView::openFormMesh()
{
	m_label->setText( "Meshes" );
	QDir dir = QDir::currentPath() + "/data/meshes/";
	QStringList entry = dir.entryList( QStringList() << "*.agmsh" );
	for( int i = 0; i < entry.size(); i++ )
	{ 
		QListWidgetItem* item = new QListWidgetItem;
		QString previewName = "/" + entry[ i ].split( "." ).at( 0 ) + ".png"; 
		QIcon icon( dir.path() + previewName );
		if( !QFileInfo().exists( dir.path() + previewName ) )
		{
			icon = QIcon( QDir::currentPath() + "/data/system/default.png" );
		}
		item->setIcon( icon );
		item->setText( entry.at( i ).split( "." ).at( 0 ) );
		m_listWidget->addItem( item ); 
		m_listWidget->setIconSize( QSize( 48, 48 ) );
	}
}

void AGEResourcesView::update()
{
	m_preview->update();
}

void AGEResourcesView::itemDoubleClicked(QListWidgetItem* item)
{
	m_preview->setMesh( AGResourceManager::getInstance().getMesh( item->text().toStdString() + ".AGMSH" ) );
}

