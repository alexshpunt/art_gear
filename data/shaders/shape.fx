matrix mtxWorld;
matrix mtxView;
matrix mtxProj; 

RasterizerState rs 
{
	CullMode = None; 
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

struct VS_INPUT
{
	float4 pos : POSITION;
	float4 color : COLOR;
};

struct PS_INPUT 
{
	float4 pos : SV_POSITION;	
	float4 color : COLOR0;  
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
	output.pos = mul( output.pos, mtxView );
	output.pos = mul( output.pos, mtxProj );

	output.color = input.color; 

	return output;
}

PSOutput PS( PS_INPUT input )
{
	PSOutput output = (PSOutput)0;

	output.diffuse = input.color; 
	output.diffuse.w = 0.0f; 

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
}
