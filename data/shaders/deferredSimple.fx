Texture2D txDiffuse;
Texture2D txPos;

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

	float4 color = txDiffuse.Sample( samLinear, psIn.tex ); 

	return color; 
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