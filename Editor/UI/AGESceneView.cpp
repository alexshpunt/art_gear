#include "AGESceneView.h"

#include "Engine/Graphics/Objects/AGLight.h"

#include "Editor/Wrappers/Objects/AGEGameObject.h"

AGESceneViewItem::AGESceneViewItem( AGEGameObject* gameObject )
{
	m_gameObject = gameObject;
	this->setText( 0, gameObject->getName().c_str() );
}

AGESceneViewItem::~AGESceneViewItem()
{

}

AGESceneView::AGESceneView()
{
	m_layout = new QVBoxLayout; 
	m_searchEdit = new QLineEdit( "Type filter..." ); 
	m_sceneView = new QTreeWidget; 

	m_layout->addWidget( m_searchEdit );
	m_layout->addWidget( m_sceneView );

	this->setFrameStyle( QFrame::StyledPanel );
	this->setFixedWidth( 200 );
	this->setLayout( m_layout );
	m_sceneView->setHeaderHidden( true );
}

AGESceneView::~AGESceneView()
{

}

void AGESceneView::addItem(AGESceneViewItem* item)
{
	m_sceneView->addTopLevelItem( item ); 
}

