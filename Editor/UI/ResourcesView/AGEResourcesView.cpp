#include "AGEResourcesView.h"

#include <QDebug>
#include <QDir>
#include <QListWidgetItem>
#include <QFileInfo>

#include "Engine/Managers/AGResourceManager.h"

class AGEResourceViewItem : public QListWidgetItem 
{
	public:
		AGEResourceViewItem( QFileInfo& info ) : m_info( info )
		{}

		const QFileInfo& getInfo() const
		{ 
			return m_info;
		}

	private:
		QFileInfo& m_info; 
};

void AGEResourcesView::init()
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

	m_dialog = new QDialogButtonBox( QDialogButtonBox::Ok | QDialogButtonBox::Cancel );

	m_toolbar = new QToolBar; 
	m_toolbar->addAction( "Up" );

	m_preview = new AGEResourcePreview;
	m_preview->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );

	m_horLayout = new QHBoxLayout;
	m_horLayout->addWidget( m_listWidget );
	m_horLayout->addWidget( m_preview );
	m_horLayout->setSpacing( 2 );

	m_vertLayout = new QVBoxLayout( this ); 
	m_vertLayout->addWidget( m_toolbar );
	m_vertLayout->addWidget( m_label );
	m_vertLayout->addLayout( m_horLayout );
	m_vertLayout->addWidget( m_dialog );
	m_vertLayout->setSpacing( 2 );

	m_texturePreview = new QGraphicsView;
	m_texturePreview->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );

	m_scene = new QGraphicsScene; 
	m_texturePreview->setScene( m_scene );
	m_horLayout->addWidget( m_texturePreview );

	connect( m_listWidget, SIGNAL( itemDoubleClicked( QListWidgetItem* ) ), this, SLOT( itemDoubleClicked( QListWidgetItem* ) ) );

	resize( 640, 480 );
}

void AGEResourcesView::openFormMesh()
{
	close(); 
	m_mode = Mesh;
	m_preview->setHidden( false );
	m_texturePreview->setHidden( true );
	m_listWidget->clear(); 

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
	show(); 
}

void AGEResourcesView::update()
{
	m_preview->update();
}

void AGEResourcesView::resizeEvent(QResizeEvent *r)
{
	/*if( m_mode == Texture )
	{
		if( m_texturePreview->pixmap() )
		{
			QPixmap pixmap = *m_texturePreview->pixmap();	
			pixmap = pixmap.scaled( m_texturePreview->width(), m_texturePreview->width() );
			m_texturePreview->setPixmap( pixmap );
		}
	}*/
	
}

void AGEResourcesView::itemDoubleClicked(QListWidgetItem* item)
{
	if( m_mode == Mesh )
	{
		m_preview->setMesh( AGResourceManager::getInstance().getMesh( item->text().toStdString() + ".AGMSH" ) );
	}
	else if( m_mode == Texture )
	{
		QPixmap image( QDir::currentPath() + "/data/textures/" + item->text() );
		image = image.scaledToWidth( m_texturePreview->width() );
		m_scene->addPixmap( image );
	}
	
}

void AGEResourcesView::openForTexture(const QString& string)
{
	close(); 
	m_listWidget->clear();

	m_mode = Texture;

	m_preview->setHidden( true );
	m_texturePreview->setHidden( false );

	m_label->setText( "Textures" );
	QDir dir = QDir::currentPath() + "/data/textures/"; 
	QStringList folders = dir.entryList( QDir::Filter::Dirs );
	for( int i = 0; i < folders.size(); i++ )
	{
		QString entryName = "/" + folders[ i ]; 
		if( entryName.endsWith( '.' ) )
		{
			continue;
		}

		QFileInfo fileInfo( dir.path() + entryName );
		QIcon icon( QDir::currentPath() + "/data/system/folder.png" );
		AGEResourceViewItem* item = new AGEResourceViewItem( fileInfo );
		item->setIcon( icon );
		item->setText( folders[ i ] );
		m_listWidget->addItem( item );
		m_listWidget->setIconSize( QSize( 48, 48 ) );	
	}
	QStringList entries = dir.entryList( QStringList() << "*.png" << "*.jpg" << "*.dds" << "*.tga" );
	for( int i = 0; i < entries.size(); i++ )
	{
		QString entryName = "/" + entries[ i ]; 

		QFileInfo fileInfo( dir.path() + entryName );
		QIcon icon( QDir::currentPath() + "/data/textures/" + entries[ i ] );
		AGEResourceViewItem* item = new AGEResourceViewItem( fileInfo );
		item->setIcon( icon );
		item->setText( entries[ i ] );
		m_listWidget->addItem( item );
		m_listWidget->setIconSize( QSize( 48, 48 ) );	
	}
	show();
}


