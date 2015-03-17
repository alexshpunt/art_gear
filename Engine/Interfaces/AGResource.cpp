#include "AGResource.h"

#include "Engine/Managers/AGResourceManager.h"

AGResource::AGResource()
{
	m_refsCount = 0; 
	m_isValid = false; 
}

AGResource::~AGResource()
{

}

void AGResource::incRef()
{
	m_refsCount++; 
}

void AGResource::decRef()
{
	if( m_refsCount > 0 )
		m_refsCount--; 
	if( m_refsCount == 0 )
		AGResourceManager::getInstance().releaseResource( this, getName(), getType() );
}

void AGResource::setName(const std::wstring& name)
{
	m_name = name; 
}

const std::wstring& AGResource::getName() const
{
	return m_name; 
}

bool AGResource::isValid() const
{
	return m_isValid; 
}

AGResource& AGResource::operator=(const AGResource& res)
{
	return *this; 
}


AGResPtr::AGResPtr()
{
	m_res = nullptr; 
}

AGResPtr::~AGResPtr()
{
	if( m_res )
		m_res->decRef(); 
}

AGResPtr::AGResPtr( AGResource& res)
{
	m_res = &res; 
	res.incRef(); 
}

AGResPtr::AGResPtr(AGResource* res)
{
	m_res = res;
	if( res )
		res->incRef(); 
}

AGResPtr& AGResPtr::operator=( AGResource& res )
{
	if( m_res )
	{
		m_res->decRef(); 
	}
	m_res = &res; 
	res.incRef(); 
	return *this;
}

AGResPtr& AGResPtr::operator=(AGResource* res)
{
	if( m_res )
	{
		m_res->decRef(); 
	}
	m_res = res; 
	if( res )
		res->incRef();
	return *this; 
}

bool AGResPtr::isNull() const
{
	return m_res;
}

AGResource* AGResPtr::getData() const
{
	return m_res; 
}
