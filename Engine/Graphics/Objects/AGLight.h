#ifndef AG_LIGHT_H
#define AG_LIGHT_H

#include "Graphics/Interfaces/AGPrimitive.h"
#include "Graphics/Interfaces/AGMovable.h"

#include "Graphics/Objects/Shapes/AGConeShape.h"
#include "Graphics/Objects/Shapes/AGBoxShape.h"
#include "Graphics/Objects/Shapes/AGLine.h"

#include "Engine/Interfaces/AGObject.h"

struct AGLightDesc 
{
	D3DXVECTOR4 pos; 
	D3DXVECTOR4 dir; 
	D3DXVECTOR4 ambient; 
	D3DXVECTOR4 diffuse; 
	D3DXVECTOR4 attitude; 
	float intensity; 
	float range; 
	float spotPower;
	float hotspotRadius;
	float falloffRadius; 

	int type; 
};

class AGLight : public AGMovable, public AGObject
{
	public:
		enum LightType { Point, Spot, Directional, Daylight, Skylight };
		enum SpotType { Circle, Rectangle };

		AGLight();
		~AGLight();

		void setPos( AGVec3 pos );
		AGVec3 getPos() const; 

		void setDirection( AGVec3 dir );
		AGVec3 getDirection() const; 

		void setLightType( LightType type );
		LightType getLightType() const; 

		void setIntensity( float intensity ); 
		float getIntensity() const;
		
		void setDiffuse( D3DXVECTOR4 diffuse );
		D3DXVECTOR4 getDiffuse() const;

		void setAmbient( D3DXVECTOR4 ambient );
		D3DXVECTOR4 getAmbient() const; 

		void setAttitude( D3DXVECTOR4 att );
		D3DXVECTOR4 getAttitude() const; 

		void setRange( float range ); 
		float getRange() const;

		void setHotspot( float hotspot );
		float getHotspot() const;

		void setFalloff( float fallouf );
		float getFalloff() const; 

		void setSpotType( SpotType spotType );
		SpotType getSpotType() const; 

		AGLightDesc getDesc() const; 

	private:
		AGLightDesc m_desc;
};

#endif