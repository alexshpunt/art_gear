#include "AGAxis.h"

#include "Engine/Managers/AGLogger.h"
#include "Engine/Objects/AGGameObject.h"
#include "Engine/Math/AGMath.h"
#include "Engine/Graphics/Interfaces/AGSurface.h"
#include "Engine/Graphics/Objects/AGCamera.h"
#include "Engine/Graphics/Interfaces/AGMovable.h"

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
		{ AGVec3( 0.0f, 0.0f, 0.0f ), red },
		{ AGVec3( len, 0.0f, 0.0f ), red },
		{ AGVec3( 0.0f, 0.0f, 0.0f ), green },
		{ AGVec3( 0.0f, len, 0.0f ), green },
		{ AGVec3( 0.0f, 0.0f, 0.0f ), blue },
		{ AGVec3( 0.0f, 0.0f, len ), blue },
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

	AGVec3 camEye = camera->getPos(); 
	AGVec3 objPos = m_object->getLocalPos(); 
	AGVec3 objPivot = m_object->getPivot();
	AGVec3 at( objPos.x, objPos.y, objPos.z ); 
	AGVec3 camAt = camera->getTarget(); 
	AGVec3 dir = camEye - at; 
	D3DXVec3Normalize( &dir, &dir );
	dir = camEye - dir * 1.5f; 
	setLocalPos( dir );

	AGEStateManager::CoordSystem system = AGEStateManager::getInstance().getCoordSystem(); 

	m_shader->setWorldMatrix( system == AGEStateManager::World ? getLocalMatrix() : getResultMatrix() );

	AGInputLayout* inputLayout = AGGraphics::getInstance().getInputLayout( device );

	if( !inputLayout )
	{
		AGError() << "Cant get input layout for device " << AGCurFileFunctionLineSnippet; 
		return; 
	}

	device->IASetInputLayout( inputLayout->colorVertexInputLayout );

	UINT stride = sizeof( AGPrimitiveVertex );
	UINT offset = 0; 
	device->IASetVertexBuffers( 0, 1, &vbo, &stride, &offset );
	device->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_LINELIST );

	m_shader->applySurface( surface );
	m_vertexBuffer->apply( surface );

	while( m_shader->applyNextPass() )
	{	
		device->Draw( 2, 0 );
		device->Draw( 2, 2 );
		device->Draw( 2, 4 );
	}

	vbo->Release(); 
}

float AGAxises::intersect(const AGVec3& rayOrigin, const AGVec3& rayDir)
{
	return -1.0f; 
}

AGVec3 AGAxises::getAxis()
{
	return AGVec3( 0.0f, 0.0f, 0.0f );
}

