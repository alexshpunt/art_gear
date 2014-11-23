#include "AGEView.h"

#include <QDebug>
#include <QSizePolicy>
#include <QLabel>

class AGEViewTop : public QWidget
{
	public:	
		AGEViewTop()
		{
			m_label.setText( "Top" );
			m_layout.addWidget( &m_label );
			setMaximumHeight( 30 );
			setStyleSheet( "background: rgb( 70, 70, 70 )");
			setLayout( &m_layout );
		}
		~AGEViewTop()
		{
		}

	private:
		QLabel m_label; 
		QHBoxLayout m_layout; 
};

class AGEViewBottom : public QWidget
{
	public:
		AGEViewBottom()
		{
			m_label.setText( "Bottom" );
			m_layout.addWidget( &m_label );
			setMaximumHeight( 30 );
			setStyleSheet( "background: rgb( 70, 70, 70 )");
			setLayout( &m_layout );
		}
		~AGEViewBottom()
		{
		}

	private:
		QLabel m_label; 
		QHBoxLayout m_layout;
};

AGEView::AGEView()
{
	m_top = new AGEViewTop;
	m_bottom = new AGEViewBottom;
	 
	m_layout.addWidget( m_top );
	m_layout.addWidget( &m_window );
	m_layout.addWidget( m_bottom );
	m_layout.setSpacing( 1 );
	setLayout( &m_layout );
	m_layout.setMargin( 1 );
}

AGEView::~AGEView()
{
}

void AGEView::update()
{
	m_window.update();
	QWidget::update();
}

AGEWindow* AGEView::getViewport()
{
	return &m_window;
}
