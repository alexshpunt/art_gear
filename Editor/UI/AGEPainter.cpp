#include "AGEPainter.h"

#include "Engine/Graphics/Objects/AGTerrain.h"

AGEPainter::AGEPainter( AGTerrain* terrain ) : m_terrain( terrain )
{
	m_ui.setupUi( this );
	setLayout( m_ui.mainLayout );
}

AGEPainter::~AGEPainter()
{

}

void AGEPainter::setGameObject(AGGameObject* gameObject)
{

}

char* AGEPainter::getName() const 
{
	return "Painter";
}

void AGEPainter::addMaterial(const std::wstring& matName)
{

}

void AGEPainter::radiusSliderChanged(int value)
{

}

void AGEPainter::radiusSpinBoxChanged(double value)
{

}

void AGEPainter::hardnessSliderChanged(int value)
{

}

void AGEPainter::hardnessSpinBoxChanged(double value)
{

}

void AGEPainter::saturationSliderChanged(int value)
{

}

void AGEPainter::colorButtonPressed()
{

}

void AGEPainter::resetButtonPressed()
{

}

void AGEPainter::saveButtonPressed()
{

}

void AGEPainter::addButtonPressed()
{

}

void AGEPainter::removeButtonPressed()
{

}

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

AGEMaterialsView::AGEMaterialsView(AGEPainter* painter)
{

}

AGEMaterialsView::~AGEMaterialsView()
{

}

void AGEMaterialsView::itemClicked(QListWidgetItem *item)
{

}

void AGEMaterialsView::itemDoubleClicked(QListWidgetItem* item)
{

}

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

AGEMaterialsViewItem::AGEMaterialsViewItem(const std::wstring& materialName)
{
	m_materialName = materialName; 
}

AGEMaterialsViewItem::~AGEMaterialsViewItem()
{

}

const std::wstring& AGEMaterialsViewItem::getName() const
{
	return m_materialName; 
}

AGTexture2D* AGEMaterialsViewItem::getTexture()
{
	return m_texture; 
}
