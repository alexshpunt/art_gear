#include "AGESidePanel.h"

AGESidePanel::AGESidePanel()
{
	m_layout = new QVBoxLayout; 
	m_transformPanel = new AGETransformPanel; 
	m_widget = new AGERendererWidget; 
	//m_layout->addWidget( m_transformPanel );
	m_spacer = new QSpacerItem( 0, 100, QSizePolicy::Minimum, QSizePolicy::MinimumExpanding  ); 
	setLayout( m_layout );
	setFixedWidth( 400 );
	setFrameStyle( QFrame::StyledPanel );
	this->setAnimated( true );
	this->setIndentation( 13 );

	m_item = new QTreeWidgetItem( this );
	m_item->setText( 0, "Transform" );
	m_item->setFlags( 0 );
	m_item->setTextAlignment( 0, Qt::AlignCenter );
	m_item->setBackgroundColor( 0, QColor( 62, 62, 62 ) );
	m_widgetItem = new QTreeWidgetItem( m_item );
	m_widgetItem->setFlags( 0 );
	this->setItemWidget( m_widgetItem, 0, m_transformPanel );

	/*m_item1 = new QTreeWidgetItem( this );
	m_item1->setText( 0, "Renderer" );
	m_item1->setFlags( 0 );
	m_item1->setTextAlignment( 0, Qt::AlignCenter );
	m_item1->setBackgroundColor( 0, QColor( 62, 62, 62 ) );
	m_widgetItem1 = new QTreeWidgetItem( m_item1 );
	m_widgetItem1->setFlags( 0 );
	this->setItemWidget( m_widgetItem1, 0, m_widget );*/

	this->setHeaderHidden( true );

	m_layout->addSpacerItem( m_spacer );
	this->expandAll();
}

AGESidePanel::~AGESidePanel()
{

}

void AGESidePanel::setGameObject( AGGameObject* gameObject )
{
	m_transformPanel->setGameObject( gameObject );
}
