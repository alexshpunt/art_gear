matrix mtxWorld;
matrix mtxView;
matrix mtxProj; 

float3 cameraPos;
bool fading;

RasterizerState Culling
{
	CullMode = None; 
};

struct VS_INPUT
{
	float4 pos : POSITION;
	float4 clr : COLOR;
};

struct PS_INPUT 
{
	float4 pos : SV_POSITION;
	float4 clr : COLOR; 
};

PS_INPUT VS( VS_INPUT input )
{
	PS_INPUT output;
	output.pos = mul( input.pos, mtxWorld );

	float dist = length( output.pos - cameraPos );

	if( fading && dist > 1.05 )
		input.clr.a = 0.1;

	output.pos = mul( output.pos, mtxView );
	output.pos = mul( output.pos, mtxProj );
	output.clr = input.clr; 

	return output;
}

float4 PS( PS_INPUT input ) : SV_Target
{
	return input.clr;
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
