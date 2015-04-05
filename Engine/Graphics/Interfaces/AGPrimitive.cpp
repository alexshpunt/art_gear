#include "AGPrimitive.h"

#include <string>

#include "Managers/AGLogger.h"

#include <Engine/Managers/AGResourceManager.h>

AGPrimitive::AGPrimitive()
{
	m_vertexBuffer = nullptr;
	m_indexBuffer = nullptr;

	m_shader = AGResourceManager::getInstance().getShader( L"primitive" );
}

AGPrimitive::~AGPrimitive()
{
	delete m_vertexBuffer;
	delete m_indexBuffer; 
}

