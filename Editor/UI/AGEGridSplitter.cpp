#include "AGEGridSplitter.h"

#include <windows.h>

#include <QPainter>
#include <QSizeF>

#include "Engine/Graphics/AGGraphics.h"

#include "Engine/Managers/AGInputManager.h"
#include "Engine/Managers/AGLogger.h"

AGEGridSplitter::AGEGridSplitter( AGEView* lefttop, AGEView* righttop, AGEView* leftbot, AGEView* rightbot )
{
	setMouseTracking( true );

	m_lefttop = lefttop;
	m_righttop = righttop;
	m_leftbot = leftbot;
	m_rightbot = rightbot;

	m_lefttop->setParent( this );
	m_righttop->setParent( this );
	m_leftbot->setParent( this );
	m_rightbot->setParent( this );

	QSize winSize = size(); 
	QPoint center( winSize.width() / 2, winSize.height() / 2 ); 
	int side = 4; 
	m_centerRect.setRect( center.x() - side, center.y() - side, side * 2, side * 2 );
	m_vertRect.setRect( 0, center.y() - side, winSize.width(), side * 2 );
	m_horRect.setRect( center.x() - side, 0, side * 2, winSize.height() ) ;

	m_leftTopRect.setRight( m_horRect.left() );
	m_leftTopRect.setBottom( m_vertRect.top() );

	m_rightTopRect.setLeft( m_horRect.right() );
	m_rightTopRect.setBottom( m_vertRect.top() );
	m_rightTopRect.setRight( winSize.width() );

	m_leftBotRect.setRight( m_horRect.left() );
	m_leftBotRect.setTop( m_vertRect.bottom() );
	m_leftBotRect.setBottom( winSize.height() );

	m_rightBotRect.setRight( winSize.width() );
	m_rightBotRect.setLeft( m_horRect.right() );
	m_rightBotRect.setTop( m_vertRect.bottom() );
	m_rightBotRect.setBottom( winSize.height() );

	m_maxim = nullptr;  

	m_horValue = 0.5f; 
	m_vertValue = 0.5f;
}

AGEGridSplitter::~AGEGridSplitter()
{

}

void AGEGridSplitter::update()
{
	QSize winSize = size(); 

	AGEView* views[] = { m_rightbot, m_righttop, m_leftbot, m_lefttop };
	QRect* rects[] = { &m_rightBotRect, &m_rightTopRect, &m_leftBotRect, &m_leftTopRect };
	AGEView* maxView = nullptr; 

	for( int i = 0; i < 4; i++ )
	{
		if( views[ i ]->getViewport()->isMaximizedMode() )
		{
			maxView = views[ i ]; 
			break; 
		}
	}

	if( maxView )
	{
		if( !m_maxim )
		{
			for( int i = 0; i < 4; i++ )
			{
				if( views[ i ] != maxView )
				{
					views[ i ]->hide(); 
					views[ i ]->getViewport()->setMaximizedMode( false );
				}
			}
			QRect r = rect(); 
			maxView->setGeometry( r ); 
			r = maxView->getViewport()->rect(); 
			maxView->getViewport()->resizeSurface( r.width(), r.height() );
			maxView->update(); 
			m_maxim = maxView; 
		}
		return; 
	}
	else
	{
		for( int i = 0; i< 4; i++ )
		{
			views[ i ]->setHidden( false );
			views[ i ]->setGeometry( *( rects[ i ] ) );
		}
		m_maxim = nullptr; 
	}

	if( m_manip == AGEGridSplitterManipulator::None )
	{
		/*m_rightbot->update();
		m_righttop->update();
		m_lefttop->update();
		m_leftbot->update();*/
		return; 
	}

	if( m_manip == AGEGridSplitterManipulator::Hor )
	{
		float x = m_mousePos.x() - 4;
		x /= winSize.width();  
		if( x > 0.1f && x < 0.9 )
		{
			m_horValue = x; 
			m_horRect.setX( m_mousePos.x() - 4 );
			m_horRect.setWidth( 8 ); 
			m_centerRect.setX( m_mousePos.x() - 4 );
			m_centerRect.setWidth( 8 );
		}
	}
	else if( m_manip == AGEGridSplitterManipulator::Vert )
	{
		m_vertRect.setY( m_mousePos.y() - 4 );
		m_vertRect.setHeight( 8 ); 
		m_centerRect.setY( m_mousePos.y() - 4 );
		m_centerRect.setHeight( 8 );
	}
	else if( m_manip == AGEGridSplitterManipulator::Center )
	{
		m_horRect.setX( m_mousePos.x() - 4 );
		m_horRect.setWidth( 8 ); 
		m_centerRect.setX( m_mousePos.x() - 4 );
		m_centerRect.setWidth( 8 );

		m_vertRect.setY( m_mousePos.y() - 4 );
		m_vertRect.setHeight( 8 ); 
		m_centerRect.setY( m_mousePos.y() - 4 );
		m_centerRect.setHeight( 8 );
	}

	m_lefttop->setGeometry( m_leftTopRect );
	m_righttop->setGeometry( m_rightTopRect );
	m_leftbot->setGeometry( m_leftBotRect );
	m_rightbot->setGeometry( m_rightBotRect );

	m_rightTopRect.setLeft( m_horRect.right() );
	m_rightTopRect.setBottom( m_vertRect.top() );
	m_rightTopRect.setRight( winSize.width() );

	m_leftBotRect.setRight( m_horRect.left() );
	m_leftBotRect.setTop( m_vertRect.bottom() );
	m_leftBotRect.setBottom( winSize.height() );

	m_leftTopRect.setRight( m_horRect.left() );
	m_leftTopRect.setBottom( m_vertRect.top() );

	m_rightBotRect.setRight( winSize.width() );
	m_rightBotRect.setLeft( m_horRect.right() );
	m_rightBotRect.setTop( m_vertRect.bottom() );
	m_rightBotRect.setBottom( winSize.height() );
}

void AGEGridSplitter::resizeEvent(QResizeEvent *ev)
{
	QSize winSize = size(); 
	QPoint center( winSize.width() / 2, winSize.height() / 2 ); 
	int side = 4; 
	m_centerRect.setRect( center.x() - side, center.y() - side, side * 2, side * 2 );
	m_vertRect.setRect( 0, center.y() - side, winSize.width(), side * 2 );
	m_horRect.setRect( center.x() - side, 0, side * 2, winSize.height() ) ;

	m_leftTopRect.setRight( m_horRect.left() );
	m_leftTopRect.setBottom( m_vertRect.top() );

	m_rightTopRect.setLeft( m_horRect.right() );
	m_rightTopRect.setBottom( m_vertRect.top() );
	m_rightTopRect.setRight( winSize.width() );

	m_leftBotRect.setRight( m_horRect.left() );
	m_leftBotRect.setTop( m_vertRect.bottom() );
	m_leftBotRect.setBottom( winSize.height() );

	m_rightBotRect.setRight( winSize.width() );
	m_rightBotRect.setLeft( m_horRect.right() );
	m_rightBotRect.setTop( m_vertRect.bottom() );
	m_rightBotRect.setBottom( winSize.height() );

	m_lefttop->setGeometry( m_leftTopRect );
	m_righttop->setGeometry( m_rightTopRect );
	m_leftbot->setGeometry( m_leftBotRect );
	m_rightbot->setGeometry( m_rightBotRect );

	m_lefttop->getViewport()->resizeSurface( m_leftTopRect.width(), m_leftTopRect.height() );
	m_leftbot->getViewport()->resizeSurface( m_leftBotRect.width(), m_leftBotRect.height() );
	m_righttop->getViewport()->resizeSurface( m_rightTopRect.width(), m_rightTopRect.height() );
	m_rightbot->getViewport()->resizeSurface( m_rightBotRect.width(), m_rightBotRect.height() );

	if( m_maxim )
	{
		QRect r = rect(); 
		m_maxim->setGeometry( r );
		r = m_maxim->getViewport()->rect(); 
		m_maxim->getViewport()->resizeSurface( r.width(), r.height() );
	}
}

void AGEGridSplitter::mouseMoveEvent(QMouseEvent *ev)
{
	QPoint mousePos = ev->pos(); 
	
	QPoint deltaMousePos = m_mousePos - mousePos; 
	m_mousePos = mousePos; 

	if( m_manip != AGEGridSplitterManipulator::None )
	{
		return; 
	}

	if( m_centerRect.contains( mousePos ) && m_manip )
	{
		setCursor( Qt::SizeAllCursor );
		if( ev->buttons() & Qt::LeftButton )
		{
			m_manip = AGEGridSplitterManipulator::Center; 
		}
	}
	else if( m_vertRect.contains( mousePos ) )
	{
		setCursor( Qt::SizeVerCursor );
		if( ev->buttons() & Qt::LeftButton )
		{
			m_manip = AGEGridSplitterManipulator::Vert; 
		}
	}
	else if( m_horRect.contains( mousePos ) )
	{
		setCursor( Qt::SizeHorCursor );
		if( ev->buttons() & Qt::LeftButton )
		{
			m_manip = AGEGridSplitterManipulator::Hor; 
		}
	}
	else 
	{
		setCursor( Qt::ArrowCursor );
	}
}

void AGEGridSplitter::mouseReleaseEvent(QMouseEvent *ev)
{
	AGEView* views[] = { m_rightbot, m_righttop, m_leftbot, m_lefttop };
	if( m_manip != None )
	{
		for( int i = 0; i < 4; i++ )
		{
			QRect r = views[ i ]->getViewport()->rect(); 
			views[ i ]->getViewport()->resizeSurface( r.width(), r.height() );
		}
	}

	m_manip = AGEGridSplitterManipulator::None; 
}