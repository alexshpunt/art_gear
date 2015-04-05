#include "AGESidePanel.h"

AGESidePanel::AGESidePanel()
{
	m_layout = new QVBoxLayout; 
	m_transformPanel = new AGETransformPanel; 
	m_transformPanel1 = new AGETransformPanel;
	//m_layout->addWidget( m_transformPanel );
	m_spacer = new QSpacerItem( 0, 100, QSizePolicy::Minimum, QSizePolicy::MinimumExpanding  ); 
	setLayout( m_layout );
	setFixedWidth( 400 );
	setFrameStyle( QFrame::StyledPanel );
	this->setAnimated( true );
	
	m_item = new QTreeWidgetItem( this );
	m_item->setText( 0, "Transform" );
	m_item->setFlags( 0 );
	m_item->setTextAlignment( 0, Qt::AlignCenter );
	m_item->setBackgroundColor( 0, QColor( 62, 62, 62 ) );
	m_widgetItem = new QTreeWidgetItem( m_item );
	m_widgetItem->setFlags( 0 );
	this->setItemWidget( m_widgetItem, 0, m_transformPanel );

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
