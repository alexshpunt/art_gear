#ifndef AGE_TOOLBAR_H
#define AGE_TOOLBAR_H

#include <QWidget>
#include <QFrame>
#include <QPushButton>
#include <QToolButton>
#include <QSpacerItem>
#include <QComboBox>
#include <QIcon>
#include <QHBoxLayout>

//������ ��� �������� ������ �� �������, ������ ���� ������, ������ � ��� � ������ ����������. ��, ��� ���� ������ ��� ������ ���
//� ��� �������, ��� ��� ����� ����� ����������� ���, ����� ������ ������ ����� �������. 
#define BUTTON_CREATE( name ) QPushButton name; \
			      QIcon name##Icon; \
			      QIcon name##IconChecked; \

//������ �������� ������ ���: ������ ��� � ������� Qt ����������� ����������� ��������� ������ ������ � ������ ��� �������, � ��� ��� �����
class AGEToolBar : public QFrame
{
	Q_OBJECT
	public:
		AGEToolBar();
		~AGEToolBar();

	private slots:
		void btnMirrorToggled( bool checked );
		void btnMoveToggled( bool checked );
		void btnRotateToggled( bool checked );
		void btnScaleToggled( bool checked );
		void btnXToggled( bool checked );
		void btnYToggled( bool checked );
		void btnZToggled( bool checked );
		void btnXZToggled( bool checked );
		
		void coordSystemStateActivated( const QString& state );

	private:
		void toggleButton( QPushButton* button, bool checked );

		QSpacerItem* m_spacer;
		QHBoxLayout m_layout;

		QPushButton* m_prevBtn; 

		BUTTON_CREATE( m_btnMirror );
		BUTTON_CREATE( m_btnMove );
		BUTTON_CREATE( m_btnRotate );
		BUTTON_CREATE( m_btnScale );
		BUTTON_CREATE( m_btnX );
		BUTTON_CREATE( m_btnY );
		BUTTON_CREATE( m_btnZ );
		BUTTON_CREATE( m_btnXZ );

		QComboBox* m_comboBox; 
};

#endif 