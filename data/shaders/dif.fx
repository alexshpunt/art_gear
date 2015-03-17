Texture2D txDiff; 

RasterizerState rs 
{
	CullMode = Back; 
	DepthBias = -1; 
};

SamplerState samLinear
{
    Filter = ANISOTROPIC;
    AddressU = CLAMP;
    AddressV = CLAMP;
};

BlendState AlphaBlending
{
    BlendEnable[0] = FALSE;
    SrcBlend = SRC_ALPHA;
    DestBlend = INV_SRC_ALPHA;
    BlendOp = ADD;
    SrcBlendAlpha = ZERO;
    DestBlendAlpha = ZERO;
    BlendOpAlpha = ADD;
    RenderTargetWriteMask[0] = 0x0F;
};

matrix mtxWorld;
matrix mtxView;
matrix mtxProj; 

struct VS_INPUT
{
	float4 pos : POSITION;
	float3 norm : NORMAL;
	float3 binorm : BINORMAL;
	float3 tang : TANGENT;
	float2 uv : UV; 
};

struct PS_INPUT 
{
	float4 pos : SV_POSITION;
	float2 uv : UV0;	
};

PS_INPUT VS( VS_INPUT input )
{
	PS_INPUT output;
	output.pos = mul( input.pos, mtxWorld );
	output.pos = mul( output.pos, mtxView );
	output.pos = mul( output.pos, mtxProj );

	float x = input.uv.x; 
	float y = 1 - input.uv.y;
	output.uv = float2( x, y ); 

	return output;
}


//
// Pixel Shader
//
float4 PS( PS_INPUT input ) : SV_Target
{
	return txDiff.Sample( samLinear, input.uv );    // Yellow, with Alpha = 1
}


technique10 Render
{
    pass P0
    {
	SetVertexShader( CompileShader( vs_4_0, VS() ) );
	SetGeometryShader( NULL );
	SetPixelShader( CompileShader( ps_4_0, PS() ) );
	SetRasterizerState( rs ); 
	SetBlendState( AlphaBlending, float4( 0.0f, 0.0f, 0.0f, 0.0f ), 0xFFFFFFFF );
    }
}
