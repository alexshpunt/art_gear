#ifndef AGE_SCENELOADINGWIDGET_H
#define AGE_SCENELOADINGWIDGET_H

#include <QWidget>

#include <string>

#include "ui_AGSceneLoadingWidget.h"
#include "ui_AGLoadingWidget.h"

#include "Engine/Patterns/Singleton.h"

///////////////////////////////////////////////////////////////////////////
///������ ����� ������������ ����� ������ � ����� �������� ������
///������ ���������� �������� �������� � ����� ����� 
///������ ���������� �������� �������� ����������� �������, � ����� 
///����������� � ������� ������ ����� ������ ����������� 
///////////////////////////////////////////////////////////////////////////
class AGESceneLoadingWidget : public QWidget
{
	DECLARE_SINGLETON_INIT( AGESceneLoadingWidget )
	public:
		void resetAndShow();
		void setTotalProgress( int progress );
		void setLocalProgress( int progress );
		void setLabel( const std::string& label );

	private:
		void init(); 

		Ui::AGSceneLoadingWidget m_ui;
};

///////////////////////////////////////////////////////////////////////////
///������ ����� ������������ ����� ������ � ����� �������� �����
///���������� �������� �������� ����������� �������, � ����� 
///����������� � ������� ������ ����� ������ ����������� 
///////////////////////////////////////////////////////////////////////////
class AGELoadingWidget : public QWidget
{
	DECLARE_SINGLETON_INIT( AGELoadingWidget )
	public:
		void resetAndShow();
		void setProgress( int progress );
		void addProgress( int progress );
		int getProgress(); 
		void setLabel( const std::string& label );
		void setLabel( const std::wstring& label );

	private:
		void init();

		Ui::AGLoadingWidget m_ui; 
};

#endif 