#include "AGRenderer.h"

#include "Graphics/AGGraphics.h"
#include "Graphics/Objects/AGDXMesh.h"
#include "Graphics/Interfaces/AGSurface.h"
#include "Graphics/Objects/Manipulators/AGDXAxis.h"

#include "Objects/AGObject.h"

AGRenderer::AGRenderer(AGObject* object) : AGComponent( object )
{
	m_mesh = nullptr;
	ID3D10Device* device =  (*AGGraphics::getInstance().getSurfaces().begin())->getDevice();
	m_boundingBox = new AGDXBoundingBox( D3DXVECTOR3( 1.0f, 1.0f, 1.0f ), D3DXVECTOR3( 0.0f, 0.0f, 0.0f ), device );
	m_axises = new AGDXAxises( device );
	m_axises->setObject( object );
	m_isSelected = false; 
	AGGraphics::getInstance().addRenderer( this ); 
}

AGRenderer::~AGRenderer()
{
	delete m_boundingBox; 
	AGGraphics::getInstance().removeRenderer( this ); 
}

void AGRenderer::onSceneInit()
{

}

void AGRenderer::onSceneUpdate()
{

}

void AGRenderer::onSceneFixedUpdate()
{

}

void AGRenderer::setMesh(AGDXMesh* mesh)
{
	m_mesh = mesh; 
}

AGDXMesh* AGRenderer::getMesh() const
{
	return m_mesh; 
}

float AGRenderer::intersect(D3DXVECTOR3 rayOrigin, D3DXVECTOR3 rayDir)
{
	if( m_mesh )
		return m_mesh->intersect( rayOrigin, rayDir );
	else 
		return m_boundingBox->intersect( rayOrigin, rayDir );
}

void AGRenderer::setSelected(bool value)
{
	m_isSelected = value;
	m_object->setSelected( value );
}

bool AGRenderer::isSelected() const
{
	return m_isSelected;
}

void AGRenderer::draw( AGDXSurface* surface )
{
	AGVec3 pos = m_object->getPos(); 
	AGVec3 rot = m_object->getRotation();
	AGVec3 pivot = m_object->getPivot();
	if( m_mesh )
	{
		m_mesh->setAngle( rot.x, rot.y, rot.z );
		m_mesh->setPos( pos.x, pos.y, pos.z );
		m_mesh->draw( surface );
	}
	else
	{
		m_boundingBox->setPos( pos.x, pos.y, pos.z );
		m_boundingBox->draw( surface ); 
	}
	if( m_isSelected )
		m_axises->draw( surface );
}

void AGRenderer::loadMeshFrom(const string& fileName, ID3D10Device* device )
{
	m_mesh = new AGDXMesh;
	m_mesh->loadFrom( fileName, device );
}

