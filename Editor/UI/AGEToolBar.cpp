#include "AGEToolBar.h"

#include <QDebug>
#include <QPixmap>

#define INIT_BUTTON( name, textName ) m_##name##Icon = QIcon( QString( ":/AGEditor/ToolBar/") + QString( textName ) + QString( ".png" ) ); \
				      m_##name##IconChecked = QIcon( QString( ":/AGEditor/ToolBar/") + QString( textName ) + QString( "_activ.png" ) ); \
				      m_##name.setIcon( m_##name##Icon ); \
				      m_##name.setIconSize( QSize( 30, 30 ) ); \
				      m_##name.setMaximumSize( 30, 30 ); \
				      m_##name.setCheckable( true ); \
				      connect( &m_##name, SIGNAL( toggled( bool ) ), this, SLOT( name##Toggled( bool ) ) ); \
				      m_layout.addWidget( &m_##name ); \


AGEToolBar::AGEToolBar()
{
	m_prevBtn = nullptr;
	setLayout( &m_layout );	
	m_layout.setSpacing( 1 );
	m_layout.setMargin( 1 );

	m_spacer = new QSpacerItem( 1920, 30, QSizePolicy::Maximum, QSizePolicy::Maximum );

	INIT_BUTTON( btnMirror, "mirror" );
	INIT_BUTTON( btnMove, "move" );
	INIT_BUTTON( btnRotate, "rotate" );
	INIT_BUTTON( btnX, "X" );
	INIT_BUTTON( btnY, "Y" );
	INIT_BUTTON( btnZ, "Z" );
	INIT_BUTTON( btnXZ, "XZ" );

	m_layout.addSpacerItem( m_spacer );

	setFrameStyle( QFrame::Panel | QFrame::Plain );
	setLineWidth( 1 );
	setStyleSheet( "color: black; background: rgb( 68, 68, 68 );" );
	setMaximumHeight( 35 );
}

AGEToolBar::~AGEToolBar()
{
}

void AGEToolBar::btnMirrorToggled(bool checked)
{
	if( checked )
	{
		m_btnMirror.setIcon( m_btnMirrorIconChecked );	
		if( m_prevBtn )
		{
			m_prevBtn->setChecked( false );
		}
		m_prevBtn = &m_btnMirror;
	}
	else
	{
		m_btnMirror.setIcon( m_btnMirrorIcon );
	}
}

void AGEToolBar::btnMoveToggled(bool checked)
{
	if( checked )
	{
		m_btnMove.setIcon( m_btnMoveIconChecked );	
		if( m_prevBtn )
		{
			m_prevBtn->setChecked( false );
		}
		m_prevBtn = &m_btnMove;
	}
	else
	{
		m_btnMove.setIcon( m_btnMoveIcon );
	}
}

void AGEToolBar::btnRotateToggled(bool checked)
{
	if( checked )
	{
		m_btnRotate.setIcon( m_btnRotateIconChecked );	
		if( m_prevBtn )
		{
			m_prevBtn->setChecked( false );
		}
		m_prevBtn = &m_btnRotate;
	}
	else
	{
		m_btnRotate.setIcon( m_btnRotateIcon );
	}
}

void AGEToolBar::btnXToggled(bool checked)
{
	if( checked )
	{
		m_btnX.setIcon( m_btnXIconChecked );	
		if( m_prevBtn )
		{
			m_prevBtn->setChecked( false );
		}
		m_prevBtn = &m_btnX;
	}
	else
	{
		m_btnX.setIcon( m_btnXIcon );
	}
}

void AGEToolBar::btnYToggled(bool checked)
{
	if( checked )
	{
		m_btnY.setIcon( m_btnYIconChecked );	
		if( m_prevBtn )
		{
			m_prevBtn->setChecked( false );
		}
		m_prevBtn = &m_btnY;
	}
	else
	{
		m_btnY.setIcon( m_btnYIcon );
	}
}

void AGEToolBar::btnZToggled(bool checked)
{
	if( checked )
	{
		m_btnZ.setIcon( m_btnZIconChecked );	
		if( m_prevBtn )
		{
			m_prevBtn->setChecked( false );
		}
		m_prevBtn = &m_btnZ;
	}
	else
	{
		m_btnZ.setIcon( m_btnZIcon );
	}
}

void AGEToolBar::toggleButton(QPushButton* button, bool checked)
{

}

void AGEToolBar::btnXZToggled(bool checked)
{
	if( checked )
	{
		m_btnXZ.setIcon( m_btnXZIconChecked );	
		if( m_prevBtn )
		{
			m_prevBtn->setChecked( false );
		}
		m_prevBtn = &m_btnXZ;
	}
	else
	{
		m_btnXZ.setIcon( m_btnXZIcon );
	}
}

