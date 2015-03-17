Texture2D txDiff; 
Texture2D txSpecLvl;
Texture2D txGloss; 
Texture2D txNorm;

RasterizerState rs 
{
	CullMode = Back; 
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
	float4 normal : NORMAL0;
	float3 binorm : BINORMAL0;
	float3 tang : TANGENT0; 
	float2 uv : UV0;	
};

struct PSOutput 
{
	float4 diffuse : SV_Target0;
	float4 normal : SV_Target1; 
	float4 pos : SV_Target2; 
	float4 gloss : SV_Target3; 
	float4 spec : SV_Target4;
};

PS_INPUT VS( VS_INPUT input )
{
	PS_INPUT output;
	input.pos.w = 1.0f; 
	output.pos = mul( input.pos, mtxWorld );
	output.binorm = output.pos; 
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
PSOutput PS( PS_INPUT input )
{
	PSOutput output = (PSOutput)0;

	output.diffuse = txDiff.Sample( samLinear, input.uv );
	output.normal = 2.0*txNorm.Sample( samLinear, input.uv ) - 1.0f;
	if( output.diffuse.w <= 0.05 )
	{
		discard; 
	}
	output.diffuse.w = 1.0f; 
	output.pos = float4( input.binorm, 1.0f ); 
	output.pos.w = input.pos.z / input.pos.w; 
	output.spec = txSpecLvl.Sample( samLinear, input.uv );
	output.gloss = txGloss.Sample( samLinear, input.uv ); 

	return output;
}

PSOutput PS1( PS_INPUT input )
{
	PSOutput output = (PSOutput)0;

	output.diffuse = txDiff.Sample( samLinear, input.uv );
	output.diffuse = float4( 1.0f, 1.0f, 1.0f, output.diffuse.w );
	output.normal = 2.0*txNorm.Sample( samLinear, input.uv ) - 1.0f;
	if( output.diffuse.w <= 0.05 )
	{
		discard; 
	}
	output.pos = float4( input.binorm, 1.0f ); 
	output.pos.w = input.pos.z / input.pos.w; 
	output.spec = txSpecLvl.Sample( samLinear, input.uv );
	output.gloss = txGloss.Sample( samLinear, input.uv ); 
	output.diffuse = float4( 1.0f, 1.0f, 1.0f, 1.0f );

	return output;
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
    pass P1
    {
	SetVertexShader( CompileShader( vs_4_0, VS() ) );
	SetGeometryShader( NULL );
	SetPixelShader( CompileShader( ps_4_0, PS1() ) );
	SetRasterizerState( rs ); 
	SetBlendState( AlphaBlending, float4( 0.0f, 0.0f, 0.0f, 0.0f ), 0xFFFFFFFF );
    }
}
