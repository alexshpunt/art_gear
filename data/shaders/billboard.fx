matrix mtxView;
matrix mtxProj; 

Texture2D txDiff; 

bool isLit; 

float3 cameraPos;

SamplerState linSam
{
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = Wrap;
	AddressV = Wrap; 
};

RasterizerState Culling
{
	CullMode = None; 
};

struct VSIn
{
	float3 center : POSITION; 
	float2 size : SIZE; 
};

struct VSOut
{
	float3 center : POSITION;
	float2 size : SIZE; 
};

struct GSOut
{
	float4 pos : SV_POSITION; 
	float3 normal : NORMAL; 
	float2 uv : UV; 
	uint primID : SV_PrimitiveID;  
};

struct PSOut 
{
	float4 diffuse : SV_Target0;
	float4 normal : SV_Target1; 
	float4 pos : SV_Target2; 
	float4 gloss : SV_Target3; 
	float4 spec : SV_Target4;
};

VSOut VS( VSIn input )
{
	VSOut output;

	output.center = input.center; 
	output.size = input.size; 

	return output;
}

[maxvertexcount( 4 )]
void GS( point VSOut gIn[ 1 ],
	uint primID : SV_PrimitiveID,
	inout TriangleStream< GSOut > triStream )
{
	float halfWidth = gIn[ 0 ].size.x * 0.5f; 
	float halfHeight = gIn[ 0 ].size.y * 0.5f; 

	float4 vertices[ 4 ];
	vertices[ 0 ] = float4( -halfWidth, -halfHeight, 0.0f, 1.0f );
	vertices[ 1 ] = float4(  halfWidth, -halfHeight, 0.0f, 1.0f );
	vertices[ 2 ] = float4( -halfWidth,  halfHeight, 0.0f, 1.0f );
	vertices[ 3 ] = float4(  halfWidth,  halfHeight, 0.0f, 1.0f );   

	float2 uv[ 4 ];
	uv[ 0 ] = float2( 0.0f, 1.0f );
	uv[ 1 ] = float2( 1.0f, 1.0f );
	uv[ 2 ] = float2( 0.0f, 0.0f ); 
	uv[ 3 ] = float2( 1.0f, 0.0f ); 

	float3 up = float3( 0.0f, 1.0f, 0.0f ); 
	float3 look = cameraPos - gIn[ 0 ].center; 
	look.y = 0.0f;
	look = normalize( look ); 
	float3 right = cross( up, look ); 

	float4x4 mtxWorld; 
	mtxWorld[ 0 ] = float4( right, 0.0f );
	mtxWorld[ 1 ] = float4( up, 0.0f );
	mtxWorld[ 2 ] = float4( look, 0.0f );
	mtxWorld[ 3 ] = float4( gIn[ 0 ].center, 1.0f ); 

	float4x4 mtxWVP = mul( mtxWorld, mtxView );
	mtxWVP = mul( mtxWVP, mtxProj ); 

	GSOut gsOut; 
	for( int i = 0; i < 4; i++ )
	{
		gsOut.pos = mul( vertices[ i ], mtxWVP );
		gsOut.normal = look; 
		gsOut.uv = uv[ i ]; 
		gsOut.primID = primID; 

		triStream.Append( gsOut ); 
	}

}

PSOut PS( GSOut input ) : SV_Target
{
	PSOut output = (PSOut)0; 

	output.diffuse = txDiff.Sample( linSam, input.uv ); 

	if( output.diffuse.w < 0.8f ) 
	{
		discard;
	}	 
	output.diffuse.w = 0.0f; 
	output.pos.w = 0.1f; 
	output.normal = float4( input.normal, 1.0f ); 

	return output; 
}


technique10 Render
{
    pass P0
    {
	SetVertexShader( CompileShader( vs_4_0, VS() ) );
	SetGeometryShader( CompileShader( gs_4_0, GS() ) );
	SetPixelShader( CompileShader( ps_4_0, PS() ) ); 
    }
}
