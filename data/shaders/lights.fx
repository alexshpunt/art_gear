
#define PointType 0
#define SpotType 1
#define DirType 2 

#define SpotRound 0 
#define SpotSquare 1

struct Light 
{
	float4 pos;
	float4 dir;
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

	litColor += surface.diffuse * light.ambient; 

	float diffuseFactor = dot( lightVec, surface.normal ); 

	if( diffuseFactor > 0.0f )
	{
		float specPower = max( surface.specPower, 1.0f ); 
		float3 toEye = normalize( camPos - surface.pos ); 
		float3 reflLightVec = reflect( -lightVec, surface.normal ); 
		reflLightVec = normalize( reflLightVec ); 
		float specFactor = pow( max( dot( reflLightVec, toEye ), 0.0f ), 32.0f ); 

		litColor += diffuseFactor * surface.diffuse * light.diffuse; 
		litColor += specFactor * surface.specLevel * surface.gloss; 
	}
	return litColor; 
}

float4 pointLight( Surface surface, Light light, float3 camPos )
{
	float4 litColor = float4( 0.0f, 0.0f, 0.0f, 1.0f ); 

	float3 lightVec = light.pos - surface.pos; 

	float distance = length( lightVec ); 

	if( distance > light.range )
		return float4( 0.0f, 0.0f, 0.0f, 1.0f ); 

	lightVec /= distance; 

	litColor += surface.diffuse * light.ambient; 

	float diffuseFactor = dot( lightVec, surface.normal ); 

	if( diffuseFactor > 0.0f ) 
	{
		float specPower = max( surface.specPower, 1.0f ); 
		float3 toEye = normalize( camPos - surface.pos ); 
		float3 reflLightVec = reflect( light.dir, surface.normal );
		float specFactor = pow( max( dot( reflLightVec, toEye ), 0.0f ), 2.0f ); 

		litColor += diffuseFactor * surface.diffuse * light.diffuse; 
		litColor += specFactor * surface.specLevel * surface.gloss; 
	}
	return litColor / dot( light.att, float3( 1.0f, distance, distance*distance ) ); 
}

float4 spotLight( Surface surface, Light light, float3 camPos )
{
	float4 litColor = pointLight( surface, light, camPos );

	float3 lightVec = normalize( light.pos - surface.pos ); 

	float s = pow( max( dot( -lightVec, light.dir ), 0.0f ), light.spotPower ); 
	
	return litColor * s;  
}