#include "AGEView.h"

#include <QDebug>
#include <QSizePolicy>
#include <QLabel>

class AGEViewTop : public QWidget
{
	public:	
		AGEViewTop()
		{
			m_label = new QLabel( "Top" );
			m_layout = new QHBoxLayout; 
			m_layout->addWidget( m_label );
			setMaximumHeight( 30 );
			setStyleSheet( "background: rgb( 70, 70, 70 )");
			setLayout( m_layout );
		}
		~AGEViewTop()
		{
			delete m_label;
			delete m_layout; 
		}

	private:
		QLabel* m_label; 
		QHBoxLayout* m_layout; 
};

class AGEViewBottom : public QWidget
{
	public:
		AGEViewBottom()
		{
			m_label = new QLabel( "Bottom" );
			m_layout = new QHBoxLayout; 
			m_layout->addWidget( m_label );
			setMaximumHeight( 30 );
			setStyleSheet( "background: rgb( 70, 70, 70 )");
			setLayout( m_layout );
		}
		~AGEViewBottom()
		{
			delete m_label;
			delete m_layout; 
		}

	private:
		QLabel* m_label; 
		QHBoxLayout* m_layout;
};

AGEView::AGEView()
{
	m_top = new AGEViewTop;
	m_bottom = new AGEViewBottom;
	m_window = new AGEWindow; 
	m_layout = new QVBoxLayout; 

	m_layout->addWidget( m_top );
	m_layout->addWidget( m_window );
	m_layout->addWidget( m_bottom );
	m_layout->setSpacing( 1 );
	setLayout( m_layout );
	m_layout->setMargin( 1 );
}

AGEView::~AGEView()
{
	delete m_top;
	delete m_bottom;
	delete m_window;
	delete m_layout; 
}

void AGEView::update()
{
	m_window->update();
	QWidget::update();
}

void AGEView::setScene(AGDX10Scene* scene)
{
	m_window->setScene( scene );
}

ID3D10Device* AGEView::getDevice() const
{
	return m_window->getDevice(); 
}
