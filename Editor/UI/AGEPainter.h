#ifndef AGE_PAINTER_H
#define AGE_PAINTER_H

#include <QListWidget>
#include <QListWidgetItem>

#include <string>

#include "AGESidePanel.h"
#include "ui_AGPainter.h"

#include "Engine/Graphics/Objects/Textures/AGTexture2D.h"

class AGEPainter; 

class AGEMaterialsView : public QListWidget
{
	Q_OBJECT
	public:
		AGEMaterialsView( AGEPainter* painter );
		~AGEMaterialsView();

	public slots:
		void itemClicked( QListWidgetItem *item );
		void itemDoubleClicked( QListWidgetItem* item );

	private:
		AGEPainter* m_painter; 
}; 

class AGEMaterialsViewItem : public QListWidgetItem 
{
	public:	
		AGEMaterialsViewItem( const std::wstring& materialName );
		~AGEMaterialsViewItem();

		const std::wstring& getName() const; 
		AGTexture2D* getTexture(); 

	private:
		AGTexture2D* m_texture;
		std::wstring m_materialName; 
};

class AGTerrain; 

class AGEPainter : public AGESidePanelWidget
{
	Q_OBJECT
	public:
		AGEPainter( AGTerrain* terrain );
		~AGEPainter(); 
	
		void setGameObject( AGGameObject* gameObject ) override;
		char* getName() const override; 

		void addMaterial( const std::wstring& matName );

	public slots:
		void radiusSliderChanged( int value );
		void radiusSpinBoxChanged( double value ); 
		void hardnessSliderChanged( int value );
		void hardnessSpinBoxChanged( double value );
		void saturationSliderChanged( int value );
		void colorButtonPressed();
		void resetButtonPressed();
		void saveButtonPressed(); 
		void addButtonPressed();
		void removeButtonPressed(); 
	private:
		Ui::AGPainter m_ui;
		AGTerrain* m_terrain; 
};

#endif
