#include "AGETransformPanel.h"

#include "Managers/AGLogger.h"
#include "Managers/AGEStateManager.h"

#include "Math/AGMath.h"

AGETransformPanel::AGETransformPanel()
{
	m_ui.setupUi( this ); 
	this->setFixedWidth( 349 );

	m_notifyer = new AGETransformPanelNotifyer( this );

	m_nameEdit = new QLineEdit; 
	m_panelName = new QLabel( "Transform" ); 
	m_nameLabel = new QLabel( "Name: " );
	m_layout = new QHBoxLayout; 
	m_mainLayout = new QVBoxLayout; 

	m_visiableCheckBox = new QCheckBox; 
	m_visiableLabel = new QLabel( "Visiable: " ); 

	m_layout->addWidget( m_nameLabel );
	m_layout->addWidget( m_nameEdit );
	m_layout->addWidget( m_visiableLabel );
	m_layout->addWidget( m_visiableCheckBox );

	m_mainLayout->addLayout( m_layout );
	m_mainLayout->addWidget( m_ui.verticalLayoutWidget );
	
	this->setLayout( m_mainLayout );
	m_mainLayout->setSizeConstraint(QLayout::SetMinimumSize);
	setStyleSheet( "color: white" );

	m_gameObject = nullptr; 
	
	m_nameEdit->setText( "-" );
	m_visiableCheckBox->setCheckState( Qt::Unchecked );

	m_ui.spinBoxPosX->setEnabled(false);
	m_ui.spinBoxPosY->setEnabled(false);
	m_ui.spinBoxPosZ->setEnabled(false);

	m_ui.spinBoxRotX->setEnabled(false);
	m_ui.spinBoxRotY->setEnabled(false);
	m_ui.spinBoxRotZ->setEnabled(false);

	m_ui.spinBoxScaleX->setEnabled(false);
	m_ui.spinBoxScaleY->setEnabled(false);
	m_ui.spinBoxScaleZ->setEnabled(false);

	connect( m_nameEdit, SIGNAL( textChanged( const QString& ) ), this, SLOT( nameChanged( const QString& ) ) );

	connect( m_ui.spinBoxPosX, SIGNAL( valueChanged( double ) ), this, SLOT( spinBoxPosXChanged( double ) ) );
	connect( m_ui.spinBoxPosY, SIGNAL( valueChanged( double ) ), this, SLOT( spinBoxPosYChanged( double ) ) );
	connect( m_ui.spinBoxPosZ, SIGNAL( valueChanged( double ) ), this, SLOT( spinBoxPosZChanged( double ) ) );

	connect( m_ui.spinBoxRotX, SIGNAL( valueChanged( double ) ), this, SLOT( spinBoxRotXChanged( double ) ) );
	connect( m_ui.spinBoxRotY, SIGNAL( valueChanged( double ) ), this, SLOT( spinBoxRotYChanged( double ) ) );
	connect( m_ui.spinBoxRotZ, SIGNAL( valueChanged( double ) ), this, SLOT( spinBoxRotZChanged( double ) ) );

	connect( m_ui.spinBoxScaleX, SIGNAL( valueChanged( double ) ), this, SLOT( spinBoxScaleXChanged( double ) ) );
	connect( m_ui.spinBoxScaleY, SIGNAL( valueChanged( double ) ), this, SLOT( spinBoxScaleYChanged( double ) ) );
	connect( m_ui.spinBoxScaleZ, SIGNAL( valueChanged( double ) ), this, SLOT( spinBoxScaleZChanged( double ) ) );

	m_changeGameObject = false; 
}

AGETransformPanel::~AGETransformPanel()
{
	delete m_notifyer; 
}

void AGETransformPanel::setGameObject(AGGameObject* gameObject)
{
	if( m_gameObject == gameObject )
		return; 

	if( m_gameObject )
	{
		m_gameObject->unregisterNotifyFunctor( m_notifyer );
	}

	m_gameObject = gameObject; 

	if( !gameObject )
	{
		m_nameEdit->setText( "-" );
		m_visiableCheckBox->setCheckState( Qt::Unchecked );
		
		m_ui.spinBoxPosX->setValue( 0.0 ); 
		m_ui.spinBoxPosY->setValue( 0.0 ); 
		m_ui.spinBoxPosZ->setValue( 0.0 ); 

		m_ui.spinBoxRotX->setValue( 0.0 ); 
		m_ui.spinBoxRotY->setValue( 0.0 ); 
		m_ui.spinBoxRotZ->setValue( 0.0 ); 

		m_ui.spinBoxScaleX->setValue( 0.0 ); 
		m_ui.spinBoxScaleY->setValue( 0.0 ); 
		m_ui.spinBoxScaleZ->setValue( 0.0 ); 

		m_ui.spinBoxPosX->setEnabled(false);
		m_ui.spinBoxPosY->setEnabled(false);
		m_ui.spinBoxPosZ->setEnabled(false);

		m_ui.spinBoxRotX->setEnabled(false);
		m_ui.spinBoxRotY->setEnabled(false);
		m_ui.spinBoxRotZ->setEnabled(false);

		m_ui.spinBoxScaleX->setEnabled(false);
		m_ui.spinBoxScaleY->setEnabled(false);
		m_ui.spinBoxScaleZ->setEnabled(false);

		return; 
	}

	if( !m_ui.spinBoxPosX->isEnabled() )
	{
		m_ui.spinBoxPosX->setEnabled(true);
		m_ui.spinBoxPosY->setEnabled(true);
		m_ui.spinBoxPosZ->setEnabled(true);

		m_ui.spinBoxRotX->setEnabled(true);
		m_ui.spinBoxRotY->setEnabled(true);
		m_ui.spinBoxRotZ->setEnabled(true);

		m_ui.spinBoxScaleX->setEnabled(true);
		m_ui.spinBoxScaleY->setEnabled(true);
		m_ui.spinBoxScaleZ->setEnabled(true);
	}

	m_gameObject->registerNotifyFunctor( m_notifyer );

	m_nameEdit->setText( &m_gameObject->getName()[0] );
	m_visiableCheckBox->setCheckState( Qt::Checked );

	AGEStateManager::CoordSystem coordSystem = AGEStateManager::getInstance().getCoordSystem(); 

	AGVec3 pos = coordSystem == AGEStateManager::World ? m_gameObject->getWorldPos() : m_gameObject->getLocalPos(); 
	AGVec3 rot = coordSystem == AGEStateManager::World ? m_gameObject->getWorldRot() : m_gameObject->getLocalRot(); 
	AGVec3 scale = coordSystem == AGEStateManager::World ? m_gameObject->getWorldScale() : m_gameObject->getLocalScale(); 

	m_ui.spinBoxPosX->setValue( pos.x ); 
	m_ui.spinBoxPosY->setValue( pos.y ); 
	m_ui.spinBoxPosZ->setValue( pos.z ); 

	m_ui.spinBoxRotX->setValue( AGMath::toDegrees( rot.x ) ); 
	m_ui.spinBoxRotY->setValue( AGMath::toDegrees( rot.y ) ); 
	m_ui.spinBoxRotZ->setValue( AGMath::toDegrees( rot.z ) ); 

	m_ui.spinBoxScaleX->setValue( scale.x ); 
	m_ui.spinBoxScaleY->setValue( scale.y ); 
	m_ui.spinBoxScaleZ->setValue( scale.z ); 
}

void AGETransformPanel::nameChanged(const QString& text)
{
	if( !m_gameObject )
		return; 

	if( !m_changeGameObject )
	{
		m_changeGameObject = true; 
		return; 
	}

	m_gameObject->setName( text.toLocal8Bit().constData() ); 
}

void AGETransformPanel::visiableChanged(int state)
{
	if( !m_gameObject )
		return; 

	if( !m_changeGameObject )
	{
		m_changeGameObject = true; 
		return; 
	}
}

void AGETransformPanel::spinBoxPosXChanged(double value)
{
	if( !m_gameObject )
		return; 
	
	if( !m_changeGameObject )
	{
		m_changeGameObject = true; 
		return; 
	}

	AGEStateManager::CoordSystem coordSystem = AGEStateManager::getInstance().getCoordSystem(); 
	switch( coordSystem )
	{
		case AGEStateManager::Local:
			m_gameObject->setLocalXPos( value );
		break;
		case AGEStateManager::World:
			m_gameObject->setWorldXPos( value ); 
		break; 
	}

}

void AGETransformPanel::spinBoxPosYChanged(double value)
{
	if( !m_gameObject )
		return; 
	
	if( !m_changeGameObject )
	{
		m_changeGameObject = true; 
		return; 
	}

	AGEStateManager::CoordSystem coordSystem = AGEStateManager::getInstance().getCoordSystem(); 
	switch( coordSystem )
	{
		case AGEStateManager::Local:
			m_gameObject->setLocalYPos( value );
		break;			      
		case AGEStateManager::World:   
			m_gameObject->setWorldYPos( value ); 
		break; 
	}
}

void AGETransformPanel::spinBoxPosZChanged(double value)
{
	if( !m_gameObject )
		return; 
	
	if( !m_changeGameObject )
	{
		m_changeGameObject = true; 
		return; 
	}

	AGEStateManager::CoordSystem coordSystem = AGEStateManager::getInstance().getCoordSystem(); 
	switch( coordSystem )
	{
		case AGEStateManager::Local:
			m_gameObject->setLocalZPos( value );
		break;
		case AGEStateManager::World:
			m_gameObject->setWorldZPos( value ); 
		break; 
	}
}

void AGETransformPanel::spinBoxRotXChanged(double value)
{
	if( !m_gameObject )
		return; 
	
	if( !m_changeGameObject )
	{
		m_changeGameObject = true; 
		return; 
	}

	AGEStateManager::CoordSystem coordSystem = AGEStateManager::getInstance().getCoordSystem(); 
	switch( coordSystem )
	{
		case AGEStateManager::Local:
			m_gameObject->setLocalXRot( AGMath::toRadians( value ) );
		break;
		case AGEStateManager::World:
			m_gameObject->setWorldXRot( AGMath::toRadians( value ) ); 
		break; 
	}
}

void AGETransformPanel::spinBoxRotYChanged(double value)
{
	if( !m_gameObject )
		return; 
	
	if( !m_changeGameObject )
	{
		m_changeGameObject = true; 
		return; 
	}

	AGEStateManager::CoordSystem coordSystem = AGEStateManager::getInstance().getCoordSystem(); 
	switch( coordSystem )
	{
		case AGEStateManager::Local:
			m_gameObject->setLocalYRot( AGMath::toRadians( value ) );
		break;
		case AGEStateManager::World:
			m_gameObject->setWorldYRot( AGMath::toRadians( value ) ); 
		break; 
	}
}

void AGETransformPanel::spinBoxRotZChanged(double value)
{
	if( !m_gameObject )
		return; 
	
	if( !m_changeGameObject )
	{
		m_changeGameObject = true; 
		return; 
	}

	AGEStateManager::CoordSystem coordSystem = AGEStateManager::getInstance().getCoordSystem(); 
	switch( coordSystem )
	{
		case AGEStateManager::Local:
			m_gameObject->setLocalZRot( AGMath::toRadians( value ) );
		break;
		case AGEStateManager::World:
			m_gameObject->setWorldZRot( AGMath::toRadians( value ) ); 
		break; 
	}
}

void AGETransformPanel::spinBoxScaleXChanged(double value)
{
	if( !m_gameObject )
		return; 
	
	if( !m_changeGameObject )
	{
		m_changeGameObject = true; 
		return; 
	}

	AGEStateManager::CoordSystem coordSystem = AGEStateManager::getInstance().getCoordSystem(); 
	switch( coordSystem )
	{
		case AGEStateManager::Local:
			m_gameObject->setLocalXScale( value );
		break;
		case AGEStateManager::World:
			m_gameObject->setWorldXScale( value ); 
		break; 
	}
}

void AGETransformPanel::spinBoxScaleYChanged(double value)
{
	if( !m_gameObject )
		return; 
	
	if( !m_changeGameObject )
	{
		m_changeGameObject = true; 
		return; 
	}

	AGEStateManager::CoordSystem coordSystem = AGEStateManager::getInstance().getCoordSystem(); 
	switch( coordSystem )
	{
		case AGEStateManager::Local:
			m_gameObject->setLocalYScale( value );
		break;
		case AGEStateManager::World:
			m_gameObject->setWorldYScale( value ); 
		break; 
	}
}

void AGETransformPanel::spinBoxScaleZChanged(double value)
{
	if( !m_gameObject )
		return; 
	
	if( !m_changeGameObject )
	{
		m_changeGameObject = true; 
		return; 
	}

	AGEStateManager::CoordSystem coordSystem = AGEStateManager::getInstance().getCoordSystem(); 
	switch( coordSystem )
	{
		case AGEStateManager::Local:
			m_gameObject->setLocalZScale( value );
		break;
		case AGEStateManager::World:
			m_gameObject->setWorldZScale( value ); 
		break; 
	}
}

AGETransformPanelNotifyer::AGETransformPanelNotifyer( AGETransformPanel* panel )
{
	m_panel = panel; 
}

void AGETransformPanelNotifyer::operator()( AGGameObject::Change change )
{
	if( !m_panel->m_gameObject )
		return; 

	AGVec3 vec;

	AGEStateManager::CoordSystem coordSystem = AGEStateManager::getInstance().getCoordSystem(); 

	if( coordSystem == AGEStateManager::World )
	{
		switch( change )
		{
			case AGGameObject::WorldPos:
				vec = m_panel->m_gameObject->getWorldPos(); 
				m_panel->m_ui.spinBoxPosX->setValue( vec.x ); 
				m_panel->m_ui.spinBoxPosY->setValue( vec.y ); 
				m_panel->m_ui.spinBoxPosZ->setValue( vec.z ); 
			break;
			case AGGameObject::WorldRot:
				vec = m_panel->m_gameObject->getWorldRot(); 
				m_panel->m_ui.spinBoxRotX->setValue( vec.x ); 
				m_panel->m_ui.spinBoxRotY->setValue( vec.y ); 
				m_panel->m_ui.spinBoxRotZ->setValue( vec.z ); 
			break;
			case AGGameObject::WorldScale:
				vec = m_panel->m_gameObject->getWorldScale(); 
				m_panel->m_ui.spinBoxScaleX->setValue( vec.x ); 
				m_panel->m_ui.spinBoxScaleY->setValue( vec.y ); 
				m_panel->m_ui.spinBoxScaleZ->setValue( vec.z ); 
			break;
		}
	}
	else if( coordSystem == AGEStateManager::Local )
	{
		switch( change )
		{
			case AGGameObject::LocalPos:
				vec = m_panel->m_gameObject->getLocalPos(); 
				m_panel->m_ui.spinBoxPosX->setValue( vec.x ); 
				m_panel->m_ui.spinBoxPosY->setValue( vec.y ); 
				m_panel->m_ui.spinBoxPosZ->setValue( vec.z ); 
			break;
			case AGGameObject::LocalRot:
				vec = m_panel->m_gameObject->getLocalRot(); 
				m_panel->m_ui.spinBoxRotX->setValue( vec.x ); 
				m_panel->m_ui.spinBoxRotY->setValue( vec.y ); 
				m_panel->m_ui.spinBoxRotZ->setValue( vec.z ); 
			break;
			case AGGameObject::LocalScale:
				vec = m_panel->m_gameObject->getLocalScale(); 
				m_panel->m_ui.spinBoxScaleX->setValue( vec.x ); 
				m_panel->m_ui.spinBoxScaleY->setValue( vec.y ); 
				m_panel->m_ui.spinBoxScaleZ->setValue( vec.z ); 
			break;
		}
	}

	switch( change )
	{
		case AGGameObject::Name:
			m_panel->m_nameEdit->setText( &(m_panel->m_gameObject->getName())[0] ); //std::string -> char*
		break;
		case AGGameObject::Visiable:

		break; 
	}
	
	m_panel->m_changeGameObject = true; 
}
