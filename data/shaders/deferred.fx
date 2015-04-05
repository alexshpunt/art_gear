#include "lights.fx" 

Texture2D txDiffuse;
Texture2D txNormal;
Texture2D txPos;
Texture2D txGloss;  
Texture2D txSpec; 

Light light; 

float3 camPos; 

SamplerState samLinear
{
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};

struct PSIn
{
	float4 pos : SV_POSITION;
	float2 tex : TEXCOORD0; 
};

PSIn VS( float4 Pos : POSITION, float2 Tex : TEXCOORD )
{
	PSIn psIn;
	psIn.pos = Pos;
	psIn.tex = Tex;
	return psIn;
}

float4 PS( PSIn psIn ) : SV_Target
{
	float4 pos = txPos.Sample( samLinear, psIn.tex ); 

	if( pos.w == 1.0f )
		discard;
	
	float4 diffuse = txDiffuse.Sample( samLinear, psIn.tex ); 
	float4 gloss = txGloss.Sample( samLinear, psIn.tex );
	float4 specLvl = txSpec.Sample( samLinear, psIn.tex );
	float4 normal = txNormal.Sample( samLinear, psIn.tex );

	Surface surface; 
	surface.useSpecLevel = true; 
	surface.useGloss = true; 
	surface.diffuse = diffuse; 
	surface.specLevel = specLvl; 
	surface.gloss = gloss;
	surface.specPower = 12.0f; 
	surface.pos = float3( pos.x, pos.y, pos.z );
	surface.normal = float3( normal.x, normal.y, normal.z ); 

	return float4( diffuse.x, diffuse.y, diffuse.z, 1.0f );

	if( diffuse.w < 0.001f ) //Objects should be lighted 
	{
		return float4( diffuse.x, diffuse.y, diffuse.z, 1.0f );  
	}

	if( light.type == DirType ) //Parallel
	{
		return parallelLight( surface, light, camPos ); 
	}
	if( light.type == PointType ) //Point 
	{
		return pointLight( surface, light, camPos );
	}
	if( light.type == SpotType ) //SpotLight 
	{
		return spotLight( surface, light, camPos );
	}

	return float4( 1.0f, 0.0f, 0.0f, 1.0f ); 
}

technique10 Render
{
	pass P0
	{
		SetVertexShader( CompileShader( vs_4_0, VS() ) );
		SetGeometryShader( NULL );
		SetPixelShader( CompileShader( ps_4_0, PS() ) );
	}
}