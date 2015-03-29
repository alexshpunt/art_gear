#include "AGAxis.h"

#include "Engine/Managers/AGLogger.h"
#include "Engine/Objects/AGGameObject.h"
#include "Engine/Math/AGMath.h"
#include "Engine/Graphics/Interfaces/AGSurface.h"
#include "Engine/Graphics/Objects/AGCamera.h"
#include "Engine/Interfaces/AGMovable.h"

#include <Engine/Managers/AGResourceManager.h>

#include <Engine/Graphics/AGGraphics.h>

AGAxises::AGAxises()
{
	AGColor red  ( 0.798431372, 0.0f, 0.0f, 1.0f );
	AGColor green( 0.0f, 0.6117647058, 0.0f, 1.0f );
	AGColor blue ( 0.0f, 0.0f, 0.76470588233, 1.0f );
	
	float len = 0.25f; 

	AGPrimitiveVertex vertices[] = 
	{
		{ AGVec3( 0.0f, 0.0f, 0.0f ), red },  //0
		{ AGVec3( len, 0.0f, 0.0f ), red },   //1
		{ AGVec3( 0.0f, 0.0f, 0.0f ), green },//2
		{ AGVec3( 0.0f, len, 0.0f ), green }, //3
		{ AGVec3( 0.0f, 0.0f, 0.0f ), blue }, //4
		{ AGVec3( 0.0f, 0.0f, len ), blue },  //5
	};

	m_vertexBuffer = new AGBuffer< AGPrimitiveVertex >( vector< AGPrimitiveVertex >( vertices, vertices + 6 ), AGBufferType::Vertex );

	m_object = nullptr; 
}

AGAxises::~AGAxises()
{

}

void AGAxises::setObject(AGGameObject* object)
{
	m_object = object;
}

AGGameObject* AGAxises::getObject() const
{
	return m_object; 
}

void AGAxises::draw( AGSurface* surface )
{
	if( !m_object )
		return; 

	AGCamera* camera = surface->getCamera();
	ID3D10Device* device = surface->getDevice();

	assert( camera );
	assert( device );

	AGVec3 camEye = camera->getPos(); 
	AGVec3 objPos = m_object->getLocalPos(); 
	AGVec3 objPivot = m_object->getPivot();
	AGVec3 at( objPos.x, objPos.y, objPos.z ); 
	AGVec3 camAt = camera->getTarget(); 
	AGVec3 dir = ( camEye - at ).normilized();
	dir = camEye - dir * 1.5f; 
	setLocalPos( dir );

	AGInputLayout* inputLayout = AGGraphics::getInstance().getInputLayout( device );
	assert( inputLayout );
	device->IASetInputLayout( inputLayout->colorVertexInputLayout );

	AGEStateManager::CoordSystem system = AGEStateManager::getInstance().getCoordSystem(); 
	m_shader->setWorldMatrix( system == AGEStateManager::World ? getLocalMatrix() : getResultMatrix() );
	m_shader->apply( surface );
	m_vertexBuffer->apply( surface );

	while( m_shader->applyNextPass() )
	{	
		device->Draw( 2, 0 );
		device->Draw( 2, 2 );
		device->Draw( 2, 4 );
	}
}

float AGAxises::intersect(const AGVec3& rayOrigin, const AGVec3& rayDir)
{
	return -1.0f; 
}

AGVec3 AGAxises::getAxis()
{
	return AGVec3( 0.0f, 0.0f, 0.0f );
}

