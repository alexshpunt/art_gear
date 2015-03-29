#ifndef AG_LIGHT_H
#define AG_LIGHT_H

#include "Graphics/Interfaces/AGPrimitive.h"

#include "Graphics/Objects/Shapes/AGConeShape.h"
#include "Graphics/Objects/Shapes/AGBoxShape.h"
#include "Graphics/Objects/Shapes/AGLine.h"

#include "Engine/Interfaces/AGObject.h"
#include "Engine/Interfaces/AGMovable.h"

struct AGLightDesc 
{
	AGVec3 pos;
	float z0; 
	AGVec3 dir; 
	float z1;
	AGColor ambient; 
	AGColor diffuse; 
	AGVec3 attitude; 
	float z2; 
	float intensity; 
	float range; 
	float spotPower;
	float hotspotRadius;
	float falloffRadius; 

	int type; 
};

class AGLight : public AGObject
{
	public:
		enum LightType { Point, Spot, Directional, Daylight, Skylight };
		enum SpotType { Circle, Rectangle };

		AGLight();
		~AGLight();

		void setPos( const AGVec3& pos );
		const AGVec3& getPos() const; 

		void setDirection( const AGVec3& dir );
		const AGVec3& getDirection() const; 

		void setLightType( LightType type );
		LightType getLightType() const; 

		void setIntensity( float intensity ); 
		float getIntensity() const;
		
		void setDiffuse( const AGColor& diffuse );
		const AGColor& getDiffuse() const;

		void setAmbient( const AGColor& ambient );
		const AGColor& getAmbient() const; 

		void setAttitude( const AGVec3& att );
		const AGVec3& getAttitude() const; 

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