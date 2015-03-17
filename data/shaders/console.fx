Texture2D test; 

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

SamplerState samLinear
{
    Filter = ANISOTROPIC;
    AddressU = CLAMP;
    AddressV = CLAMP;
};

float4 VS( float4 pos : POSITION ) : SV_POSITION
{
	return pos;
}

//
// Pixel Shader
//
float4 PS( float4 pos : SV_POSITION ) : SV_Target
{
	return float4( 0.3f, 0.3f, 0.4f, 0.5f );
}


technique10 Render
{
    pass P0
    {
	SetVertexShader( CompileShader( vs_4_0, VS() ) );
	SetGeometryShader( NULL );
	SetPixelShader( CompileShader( ps_4_0, PS() ) );
	SetBlendState( AlphaBlending, float4( 0.0f, 0.0f, 0.0f, 0.0f ), 0xFFFFFFFF );
    }
}
