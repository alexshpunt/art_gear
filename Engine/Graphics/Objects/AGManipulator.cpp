#include "AGManipulator.h"

#include "Math/AGMath.h"
#include "Graphics/Objects/AGCamera.h"
#include "Graphics/Interfaces/AGSurface.h"
#include "Managers/AGGraphicsSettings.h"

#include <Engine/Managers/AGLogger.h>

AGManipulator::AGManipulator()
{
	m_object = nullptr;
}

AGManipulator::~AGManipulator()
{

}

void AGManipulator::setObjects(list< AGGameObject* > objects)
{
	m_objects = objects; 
	m_object = nullptr; 
}

list< AGGameObject* > AGManipulator::getObjects() const
{
	return m_objects;
}

void AGManipulator::setObject(AGGameObject* object)
{
	m_object = object; 
}

AGGameObject* AGManipulator::getObject() const
{
	return m_object;
}

