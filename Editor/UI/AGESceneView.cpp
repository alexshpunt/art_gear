#include "AGESceneView.h"

#include "Engine/Graphics/Objects/AGLight.h"

AGESceneViewItem::AGESceneViewItem(AGGameObject* gameObject)
{
	this->setText( 0, &gameObject->getName()[0] ); 
	m_data = gameObject; 
	m_type = GameObject;
}

AGESceneViewItem::AGESceneViewItem(AGELight* light)
{
	this->setText( 0, &light->getLight()->getName()[0] ); 
	m_data = light;
	m_type = Light;
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

