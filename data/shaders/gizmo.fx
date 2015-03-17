Texture2D txIcon; 

matrix mtxWorld;
matrix mtxView;
matrix mtxProj; 

SamplerState samLinear
{
    Filter = ANISOTROPIC;
    AddressU = CLAMP;
    AddressV = CLAMP;
};

RasterizerState Culling
{
	CullMode = None; 
};

BlendState AlphaBlending
{
    BlendEnable[0] = TRUE;
    SrcBlend = SRC_ALPHA;
    DestBlend = INV_SRC_ALPHA;
    BlendOp = ADD;
    SrcBlendAlpha = ZERO;
    DestBlendAlpha = ZERO;
    BlendOpAlpha = ADD;
    RenderTargetWriteMask[0] = 0x0F;
};

struct VS_INPUT
{
	float4 pos : POSITION;
	float2 uv : TEXCOORD;
};

struct PS_INPUT 
{
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD0;
};

PS_INPUT VS( VS_INPUT input )
{
	PS_INPUT output;
	output.pos = mul( input.pos, mtxWorld );
	output.pos = mul( output.pos, mtxView );
	output.pos = mul( output.pos, mtxProj );
	output.uv = input.uv; 

	return output;
}

float4 PS( PS_INPUT input ) : SV_Target
{
	return txIcon.Sample( samLinear, input.uv );
}


technique10 Render
{
    pass P0
    {
	SetVertexShader( CompileShader( vs_4_0, VS() ) );
	SetGeometryShader( NULL );
	SetPixelShader( CompileShader( ps_4_0, PS() ) );
	SetRasterizerState( Culling ); 
	SetBlendState( AlphaBlending, float4( 0.0f, 0.0f, 0.0f, 0.0f ), 0xFFFFFFFF );
    }
}
