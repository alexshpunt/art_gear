#include "AGLight.h"

AGLight::AGLight()
{ 
	setFalloff( 1.1f );
	setHotspot( 1.0f );
	setRange( 1.0f );
	setIntensity( 1.0f );
	setLightType( Point );
	setDiffuse( D3DXVECTOR4( 1.0f, 1.0f, 1.0f, 1.0f ) );
	setAmbient( D3DXVECTOR4( 1.0f, 1.0f, 1.0f, 1.0f ) );
	setAttitude( D3DXVECTOR4( 0.0f, 0.0f, 1.0f, 0.0f ) );
	setDirection( AGVec3( 0.0f, -1.0f, 0.0f ) );
	setPos( AGVec3( 0.0f, 0.0f, 0.0f ) );

	m_name = "Light";
}

AGLight::~AGLight()
{

}

void AGLight::setLightType(LightType type)
{
	m_desc.type = type; 
}

AGLight::LightType AGLight::getLightType() const
{
	return (LightType)m_desc.type; 
}

void AGLight::setIntensity(float intensity)
{
	m_desc.intensity = intensity; 
}

float AGLight::getIntensity() const
{
	return m_desc.intensity; 
}

void AGLight::setRange(float range)
{
	m_desc.range = range;
}

float AGLight::getRange() const
{
	return m_desc.range; 
}

void AGLight::setHotspot(float hotspot)
{
	m_desc.hotspotRadius = hotspot; 
}

float AGLight::getHotspot() const
{
	return m_desc.hotspotRadius;
}

void AGLight::setFalloff(float falloff)
{
	m_desc.falloffRadius = falloff; 
}

float AGLight::getFalloff() const
{
	return m_desc.falloffRadius; 
}

void AGLight::setSpotType(SpotType spotType)
{
	
}

AGLight::SpotType AGLight::getSpotType() const
{
	return (AGLight::SpotType)0; 
}

void AGLight::setDirection(AGVec3 dir)
{
	m_desc.dir = D3DXVECTOR4( dir, 1.0f ); 
}

AGVec3 AGLight::getDirection() const
{
	return m_desc.dir;  
}

AGLightDesc AGLight::getDesc() const
{
	return m_desc; 
}

void AGLight::setDiffuse(D3DXVECTOR4 diffuse)
{
	m_desc.diffuse = diffuse; 
}

D3DXVECTOR4 AGLight::getDiffuse() const
{
	return m_desc.diffuse; 
}

void AGLight::setAmbient(D3DXVECTOR4 ambient)
{
	m_desc.ambient = ambient;
}

D3DXVECTOR4 AGLight::getAmbient() const
{
	return m_desc.ambient;
}

void AGLight::setAttitude(D3DXVECTOR4 att)
{
	m_desc.attitude = att; 
}

D3DXVECTOR4 AGLight::getAttitude() const
{
	return m_desc.attitude; 
}

void AGLight::setPos(AGVec3 pos)
{
	m_desc.pos = D3DXVECTOR4( pos, 1.0f );
}

AGVec3 AGLight::getPos() const
{
	return m_desc.pos; 
}


