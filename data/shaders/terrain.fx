Texture2D txHeight; 
Texture2D txDiff;
Texture2D txRock;
Texture2DArray txMaps; 

RasterizerState rs 
{
	CullMode = Front; 
	FillMode = WireFrame;
};

SamplerState samLinear
{
	Filter = ANISOTROPIC ;
	AddressU = Wrap;
	AddressV = Wrap;
};

SamplerState otherSampler
{

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
	float rockK : ROCKK; 
	float leftK : LEFTK;
	int   leftT : LEFTT;
	float upK : UPK; 
	int   upT : UPT;
	int   curT : CURT;
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

	const float blendRadius = 0.004;

	float4 curTemp = txHeight.Sample( samLinear, input.uv ); 
	float4 curIndex = txRock.Sample( samLinear, input.uv ); 

	int xIndex = curIndex.x * 255 / 10 - 2; 
	int yIndex = curIndex.y * 255 / 10 - 2;

	//int curT = curTemp.x * 255 / 10 - 2;

	float k = 20;

	output.diffuse += txMaps.Sample( samLinear, float3( input.uv * k, xIndex ) ) * curTemp.r;
	output.diffuse += txMaps.Sample( samLinear, float3( input.uv * k, yIndex ) ) * curTemp.g;
	//output.diffuse += txMaps.Sample( samLinear, float3( input.uv * k * 1.4, 2 ) ) * curTemp.b;
	output.diffuse.a = 1.0f;

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
	SetBlendState( AlphaBlending, float4( 0.0f, 0.0f, 0.0f, 0.0f ), 0xFFFFFFFF );
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
