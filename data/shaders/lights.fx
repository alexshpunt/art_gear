
#define PointType 0
#define SpotType 1
#define DirType 2 

#define SpotRound 0 
#define SpotSquare 1

struct Light 
{
	float3 pos;
	float3 dir;
	float4 ambient;
	float4 diffuse;
	float4 att; 
	float intensity;
	float range;  
	float spotPower;  
	float hotspot;
	float falloff;

	int type; 
};

struct Surface 
{
	bool useSpecLevel; 
	bool useGloss; 

	float4 diffuse;
	float4 specLevel; 
	float4 gloss; 	
	float specPower; 

	float3 pos; 
	float3 normal; 
};

float4 parallelLight( Surface surface, Light light, float3 camPos )
{
	float4 litColor = float4( 0.0f, 0.0f, 0.0f, 1.0f ); 

	float3 lightVec = -light.dir; 

	//return surface.diffuse * light.diffuse * light.intensity;

	float4 ambient = surface.diffuse * light.ambient; 

	litColor += ambient; 

	float diffuseFactor = dot( lightVec, surface.normal ); 

	if( diffuseFactor > 0.0f )
	{
		float specPower = max( surface.specPower, 1.0f ); 
		float3 toEye = normalize( camPos - surface.pos ); 
		float3 reflLightVec = reflect( lightVec, surface.normal ); 
		reflLightVec = normalize( reflLightVec ); 
		float specFactor = pow( max( dot( reflLightVec, toEye ), 0.0f ), specPower ); 

		litColor += diffuseFactor * surface.diffuse * light.diffuse; 
		litColor += specFactor * surface.specLevel * surface.gloss;
	}
	litColor *= light.intensity; 
	return float4( max( ambient.x, litColor.x ), max( ambient.y, litColor.y ), max( ambient.z, litColor.z ), 1.0f );
}

float4 pointLight( Surface surface, Light light, float3 camPos )
{
	float4 litColor = float4( 0.0f, 0.0f, 0.0f, 1.0f ); 

	float3 lightVec = light.pos - surface.pos; 

	float distance = length( lightVec ); 

	if( distance > light.range * 2.0f )
		return surface.diffuse * light.ambient;

	lightVec /= distance; 

	float4 ambient = surface.diffuse * light.ambient; 

	litColor += ambient; 

	float diffuseFactor = dot( lightVec, surface.normal ); 

	if( diffuseFactor >= 0.0f ) 
	{
		float specPower = max( surface.specPower, 1.0f ); 
		float3 toEye = normalize( camPos - surface.pos ); 
		float3 reflLightVec = reflect( lightVec, surface.normal );
		float specFactor = pow( max( dot( reflLightVec, toEye ), 0.0f ), surface.specPower ); 

		litColor += diffuseFactor * surface.diffuse * light.diffuse; 
		litColor += specFactor * surface.specLevel * surface.gloss; 
	}
	litColor *= light.intensity; 

	litColor /= dot( light.att, float3( 1.0f, distance, distance * distance ) );
	
	return float4( max( ambient.x, litColor.x ), max( ambient.y, litColor.y ), max( ambient.z, litColor.z ), 1.0f );
}

float4 spotLight( Surface surface, Light light, float3 camPos )
{
	float4 litColor = pointLight( surface, light, camPos );

	float3 lightVec = normalize( light.pos - surface.pos ); 

	float s = pow( max( dot( lightVec, light.dir ), 0.0f ), light.spotPower ); 
	
	return litColor * s;  
}