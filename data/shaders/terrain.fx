Texture2D txHeight; 
Texture2D txDiff;
Texture2D txRock;
Texture2DArray txMaps; 

float brushRadius;
float3 cursorPos; 

RasterizerState rs 
{
	CullMode = Front; 
	FillMode = WireFrame;
};

SamplerState samLinear
{
	Filter = ANISOTROPIC;
};

SamplerState indexMapSampler
{
	Filter = MIN_MAG_MIP_POINT;
	AddressU = Clamp;
	AddressV = Clamp;
};

SamplerState texMapSampler
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
	float4 norm : NORMAL0;
	float3 binorm : BINORMAL0;
	float3 tang : TANGENT0; 
	float2 uv : UV0;	
	float3 pos1 : POS1; 
};

struct PSOutput 
{
	float4 diffuse : SV_Target0;
	float4 normal : SV_Target1; 
	float4 depth : SV_Target2; 
};

PS_INPUT VS( VS_INPUT input )
{
	PS_INPUT output = (PS_INPUT)0;
	input.pos.w = 1.0f; 

	output.pos1 = input.pos; 

	output.pos = input.pos; 
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

	float k = 10;
	
	//float4 dif = txMaps.Sample( samLinear, float3( input.uv * k, 0 ) );
	float4 dif = txMaps.Sample( samLinear, float3( input.uv * k, 0 ) );
	dif = lerp( dif, txMaps.Sample( samLinear, float3( input.uv * k, 1 ) ), txDiff.Sample( texMapSampler, input.uv ).r );
	dif = lerp( dif, txMaps.Sample( samLinear, float3( input.uv * k, 2 ) ), txRock.Sample( texMapSampler, input.uv ).r );

	output.diffuse = dif;

	//output.diffuse = float4( txHeight.Sample( samLinear, input.uv ).r, txRock.Sample( samLinear, input.uv ).r, txDiff.Sample( samLinear, input.uv ).r, 1.0f );

	float x = input.pos1.x - cursorPos.x; 
	float y = input.pos1.z - cursorPos.z;

	float radius = sqrt( x * x + y * y );

	if( radius < brushRadius && radius > brushRadius - 0.05f )
	{
		output.diffuse = float4( 0.0f, 1.0f, 0.0f, 1.0f );
	}

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
