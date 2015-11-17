#include "AGESidePanel.h"

#include "AGETransformPanel.h"

AGESidePanel::AGESidePanel()
{
	m_layout = new QVBoxLayout; 
	m_spacer = new QSpacerItem( 0, 100, QSizePolicy::Minimum, QSizePolicy::MinimumExpanding  ); 
	setLayout( m_layout );
	setFixedWidth( 400 );
	setFrameStyle( QFrame::StyledPanel );
	this->setAnimated( true );
	this->setIndentation( 13 );
	this->setHeaderHidden( true );

	addWidget( new AGETransformPanel );

	m_layout->addSpacerItem( m_spacer );
}

AGESidePanel::~AGESidePanel()
{

}

void AGESidePanel::setGameObject( AGGameObject* gameObject )
{
}

void AGESidePanel::addWidget( AGESidePanelWidget* widget )
{
	QTreeWidgetItem* item = new QTreeWidgetItem( this );
	item->setText( 0, widget->getName() );
	item->setFlags( 0 );
	item->setTextAlignment( 0, Qt::AlignCenter );
	item->setBackgroundColor( 0, QColor( 62, 62, 62 ) );
	QTreeWidgetItem* widgetItem = new QTreeWidgetItem( item );
	widgetItem->setFlags( 0 );
	this->setItemWidget( widgetItem, 0, widget );

	AGESidePanelItem* sidePanelItem = new AGESidePanelItem;
	sidePanelItem->item = item; 
	sidePanelItem->widgetItem = widgetItem; 
	sidePanelItem->widget = widget; 

	m_widgets.push_back( sidePanelItem );
	this->expandAll();
}

void AGESidePanel::removeWidget( AGESidePanelWidget* widget )
{
	
}