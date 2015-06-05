/*Texture2D txIndex; 
Texture2DArray txArray; 

RasterizerState rs 
{
	CullMode = Front; 
	FillMode = WireFrame;
};

SamplerState samLinear
{
    Filter = ANISOTROPIC;
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
};

struct PSOutput 
{
	float4 diffuse : SV_Target0;
	float4 normal : SV_Target1; 
	float4 depth : SV_Target2; 
};

PS_INPUT VS( VS_INPUT input )
{
	PS_INPUT output;
	input.pos.w = 1.0f; 

	float3 hm = txHeight.SampleLevel( samLinear, input.uv, 0 ); 
	float height = (hm.x + hm.y + hm.z)/3;

	output.pos = input.pos; 

	if( height > 0.001 )
	{
		output.pos.y = height * 10; 

		float4 wBinormal = mul( float4( input.binorm, 1.0f ), mtxWorld );
		float4 wTang = mul( float4( input.tang, 1.0f ), mtxWorld );
		float4 wPos = mul( output.pos, mtxWorld );

		float3 binormal = wBinormal.xyz - abs( wPos.xyz ); 
		binormal = normalize( binormal.xyz );
		float3 normal = cross( wTang.xyz, binormal.xyz );
		output.norm = float4( normal, 1.0f );

		output.rockK = 0.0f;
		float kheight = 0.6;
		if( height > kheight )
		{
			output.rockK = (height - kheight)/( 1.0f - kheight );
		}

	}
	output.pos = mul( output.pos, mtxWorld );
	output.binorm = output.pos; 
	output.pos = mul( output.pos, mtxView );
	output.pos = mul( output.pos, mtxProj );
	//output.norm = float4( input.norm, 0.0f );

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

	float4 rockDif = txRock.Sample( samLinear, input.uv*40 );
	float4 grassDif = txDiff.Sample( samLinear, input.uv*40 );
	if( input.rockK > 0.0f )
	{
		input.rockK *= 2.0f;
		//output.diffuse = rockDif * input.rockK + grassDif* (1 - input.rockK );
		output.diffuse = rockDif;
	}
	else
	{
		output.diffuse = grassDif;
	}
	//output.normal = 2.0*txNorm.Sample( samLinear, input.uv ) - 1.0f;
	output.normal = input.norm; 
	//output.diffuse = output.normal;
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
}*/
