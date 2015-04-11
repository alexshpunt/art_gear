#include "AGELoadingWidgets.h"

void AGESceneLoadingWidget::init()
{
	m_ui.setupUi( this );
}

void AGESceneLoadingWidget::setTotalProgress(int progress)
{
	m_ui.progressBar->setValue( progress );
}

void AGESceneLoadingWidget::setLocalProgress(int progress)
{
	m_ui.progressBar_2->setValue( progress );
}

void AGESceneLoadingWidget::setLabel(const std::string& label)
{
	m_ui.label->setText( label.c_str() );
}

void AGESceneLoadingWidget::resetAndShow()
{
	m_ui.progressBar->setValue( 0 );
	m_ui.progressBar_2->setValue( 0 );
	this->show(); 
}

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

void AGELoadingWidget::init()
{
	m_ui.setupUi( this );
}

void AGELoadingWidget::setProgress(int progress)
{
	m_ui.progressBar->setValue( progress );
}

void AGELoadingWidget::setLabel(const std::string& label)
{
	m_ui.label->setText( QString().fromStdString( label ) );
}

void AGELoadingWidget::setLabel(const std::wstring& label)
{
	m_ui.label->setText( QString().fromStdWString( label ) );
}

void AGELoadingWidget::resetAndShow()
{
	m_ui.progressBar->setValue( 0 );
	this->show(); 
}

void AGELoadingWidget::addProgress(int progress)
{
	m_ui.progressBar->setValue( m_ui.progressBar->value() + progress );
}

int AGELoadingWidget::getProgress()
{
	return m_ui.progressBar->value(); 
}
