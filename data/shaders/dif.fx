Texture2D txDiff; 

RasterizerState rs 
{
	CullMode = Front; 
	FillMode = WireFrame;
};

SamplerState samLinear
{
    Filter = ANISOTROPIC;
    AddressU = WRAP;
    AddressV = WRAP;
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
	float4 norm : NORMAL0;
	float3 binorm : BINORMAL0;
	float3 tang : TANGENT0; 
	float2 uv : UV0;	
};

struct PSOutput 
{
	float4 diffuse : SV_Target0;
	float4 normal : SV_Target1; 
	float4 depth : SV_Target2; 
};

float2 noise1(in float2 uv) {
    float noiseX = (frac(sin(dot(uv, float2(12.9898,78.233) * 2.0)) * 43758.5453));
    float noiseY = sqrt(1 - noiseX * noiseX);
    return float2(noiseX, noiseY);
}

PS_INPUT VS( VS_INPUT input )
{
	PS_INPUT output;
	input.pos.w = 1.0f; 

	float3 hm = txDiff.SampleLevel( samLinear, input.uv, 0.0f ); 
	float height = ( hm.x + hm.y + hm.z ) / 3;

	output.pos = input.pos; 

	if( height > 0.8 )
	{
		height *= 2.0f; 
	}

	output.pos.y += height*5;

	output.pos = mul( output.pos, mtxWorld );
	output.binorm = output.pos; 
	output.pos = mul( output.pos, mtxView );
	output.pos = mul( output.pos, mtxProj );
	output.norm = float4( input.norm, 0.0f );

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
	//output.normal = 2.0*txNorm.Sample( samLinear, input.uv ) - 1.0f;
	output.normal = input.norm; 
	output.depth = float4( input.binorm, 1.0f ); 
	output.depth.w = input.pos.z / input.pos.w; 

	return output;
}

PSOutput PS1( PS_INPUT input )
{
	PSOutput output = (PSOutput)0;

	output.diffuse = float4( 1.0f, 1.0f, 1.0f, 1.0f ); 
	output.normal = input.norm; 
	output.depth = float4( input.binorm, 1.0f ); 
	output.depth.w = input.pos.z / input.pos.w; 

	return output;
}

technique10 Render
{
    pass P0
    {
	SetVertexShader( CompileShader( vs_4_0, VS() ) );
	SetGeometryShader( NULL );
	SetPixelShader( CompileShader( ps_4_0, PS() ) );
	//SetRasterizerState( rs ); 
    }
     pass P1
    {
	SetVertexShader( CompileShader( vs_4_0, VS() ) );
	SetGeometryShader( NULL );
	SetPixelShader( CompileShader( ps_4_0, PS1() ) );
	//SetRasterizerState( rs ); 
    }
}
