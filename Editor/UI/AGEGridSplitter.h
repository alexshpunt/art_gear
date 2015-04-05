#ifndef AGE_GRIDSPLITTER_H
#define AGE_GRIDSPLITTER_H

#include <QRect>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QWidget>

#include <Editor/UI/AGEView.h>

enum AGEGridSplitterManipulator{ Center, Vert, Hor, None };

class AGEGridSplitter : public QWidget
{
	friend class AGEGridOverlay; 
	Q_OBJECT
	public:
		AGEGridSplitter( AGEView* lefttop, AGEView* righttop, AGEView* leftbot, AGEView* rightbot );
		~AGEGridSplitter();

		void update(); 

	protected:
		void resizeEvent(QResizeEvent *ev );
		void mouseMoveEvent(QMouseEvent *ev);
		void mouseReleaseEvent(QMouseEvent *ev);
	private:
		QPoint m_mousePos; 

		AGEView* m_lefttop;
		AGEView* m_righttop;
		AGEView* m_leftbot;
		AGEView* m_rightbot;

		AGEView* m_maxim; 

		QGridLayout* m_layout; 

		AGEGridSplitterManipulator m_manip; 

		QRect m_leftTopRect;
		QRect m_rightTopRect; 
		QRect m_leftBotRect;
		QRect m_rightBotRect; 

		QRect m_centerRect; 
		QRect m_vertRect;
		QRect m_horRect; 

		float m_horValue; 
		float m_vertValue; 
};

#endif 