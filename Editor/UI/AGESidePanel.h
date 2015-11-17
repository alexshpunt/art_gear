#ifndef AGE_SIDEPANEL_H
#define AGE_SIDEPANEL_H

#include <QWidget>
#include <QFrame>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QVBoxLayout>
#include <QSpacerItem>

#include <string>
#include <list>

#include "Objects/AGGameObject.h"

#include "Editor/Wrappers/Components/AGERenderer.h"

/*!
 * @class AGESidePanelWidget
 * @brief Должен быть наследован всем виджетами, которые могут находится на боковй панели
 */
class AGESidePanelWidget : public QFrame
{
	Q_OBJECT
	public:
		virtual void setGameObject( AGGameObject* gameObject ) = 0; 
		virtual char* getName() const = 0; 
};

/*!
 * @struct AGESidePanelItem  
 * @brief Структура для хранения виджетов в боковой панели
 */ 
struct AGESidePanelItem 
{
	QTreeWidgetItem* item;
	QTreeWidgetItem* widgetItem;
	AGESidePanelWidget* widget; 
};

/*!
 * @class AGESidePanel 
 * @brief Класс представляющий боковую панель редактора
 */ 
class AGESidePanel : public QTreeWidget
{
	Q_OBJECT

	public:
		AGESidePanel();
		~AGESidePanel();
	
		void setGameObject( AGGameObject* gameObject );
		void addWidget( AGESidePanelWidget* widget ); 
		void removeWidget( AGESidePanelWidget* widget );

	private:
		QVBoxLayout* m_layout;
		QSpacerItem* m_spacer; 

		std::list< AGESidePanelItem* > m_widgets; 

};

#endif 