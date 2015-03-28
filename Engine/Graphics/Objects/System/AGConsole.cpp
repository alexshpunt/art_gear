#include "AGConsole.h"

#include <string>
#include <time.h>

#include "Graphics/Interfaces/AGSurface.h"
#include "Managers/AGConsoleManager.h"
#include "Managers/AGLogger.h"

using namespace std;

#define LOGICAL_TO_PIXELS 1.6451612903225806451612903225806
#define FONT_HEIGHT 16 

AGConsole::AGConsole(  ID3D10Device* device  )
{
	wstring fileName = L"data/shaders/console.fx";

	int shadersFlags = D3D10_SHADER_ENABLE_STRICTNESS | D3D10_SHADER_DEBUG; 
#ifdef _DEBUG
	shadersFlags |= D3D10_SHADER_DEBUG; 
#endif 
	ID3D10Blob* blob; 
	
	HRESULT hr = S_OK; 
	hr = D3DX10CreateEffectFromFile( 
		&fileName[0], NULL, NULL, "fx_4_0", shadersFlags,
		 NULL, device, NULL, NULL, &m_effect, &blob, NULL 
	);  
	if( FAILED( hr ) )
	{
		AGError() << "Couldn't load dx10 shader: " << fileName;
		if( blob )
			AGError() << (char*)blob->GetBufferPointer();
		return; 
	}

	m_technique = m_effect->GetTechniqueByName( "Render" );
	m_var = m_effect->GetVariableByName( "test" )->AsShaderResource();

	D3D10_INPUT_ELEMENT_DESC layout[] = 
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D10_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = 1; 

	D3D10_PASS_DESC passDesc; 
	m_technique->GetPassByIndex( 0 )->GetDesc( &passDesc );
	hr = device->CreateInputLayout( layout, numElements, passDesc.pIAInputSignature, passDesc.IAInputSignatureSize, &m_inputLayout );

	if( FAILED( hr ) )
	{
		AGError() << "Couldn't create input layout";
		return;
	}

	device->IASetInputLayout( m_inputLayout );

	AGVec3 vertices[] = 
	{
		AGVec3( -1.0f, 1.0f, 0.5f ), AGVec3( 1.0f, 1.0f, 0.5f ), AGVec3( -1.0f, 0.0f, 0.5f ),
		AGVec3( 1.0f, 1.0f, 0.5f ), AGVec3( 1.0f, 0.0f, 0.5f ), AGVec3( -1.0f, 0.0f, 0.5f ),
	};

	D3D10_BUFFER_DESC buffDesc; 

	buffDesc.Usage = D3D10_USAGE_DEFAULT; 
	buffDesc.ByteWidth = sizeof( vertices ); 
	buffDesc.CPUAccessFlags = 0;
	buffDesc.MiscFlags = 0;
	buffDesc.BindFlags = D3D10_BIND_VERTEX_BUFFER; 

	D3D10_SUBRESOURCE_DATA subresData; 
	subresData.pSysMem = vertices;

	hr = device->CreateBuffer( &buffDesc, &subresData, &m_vertexBuffer );

	if( FAILED( hr ) )
	{
		AGError() << "Couldn't create vertex buffer";
		return; 
	}

	D3DX10_FONT_DESC fontDesc;

	fontDesc.CharSet = OUT_DEFAULT_PRECIS;
	wcscpy_s( fontDesc.FaceName, 32, L"Consolas" );
	fontDesc.Height = FONT_HEIGHT;
	fontDesc.Width = 0;
	fontDesc.Weight = 0;
	fontDesc.MipLevels = 1;
	fontDesc.Italic = false;
	fontDesc.Quality = DEFAULT_QUALITY; 
	fontDesc.PitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;

	D3DX10CreateFontIndirect( device, &fontDesc, &m_font );

	m_dTickCount = m_tickCount = 0; 
	m_cursor = true; 
}

AGConsole::~AGConsole()
{

}

void AGConsole::draw( AGSurface* surface )
{
	ID3D10Device* device = surface->getDevice(); 

	device->IASetInputLayout( m_inputLayout );

	UINT stride = sizeof( AGVec3 );
	UINT offset = 0; 
	device->IASetVertexBuffers( 0, 1, &m_vertexBuffer, &stride, &offset );

	D3D10_TECHNIQUE_DESC desc; 
	m_technique->GetDesc( &desc );

	for( int i = 0; i < desc.Passes; i++ )
	{
		m_technique->GetPassByIndex( i )->Apply( 0 );
		device->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
		device->Draw( 6, 0 );
	}

	D3DXCOLOR fontColor( 1.0f, 1.0f, 1.0f, 0.5f );

	list< string > strings = AGConsoleManager::getInstance().getStrings(); 

	int count = 0; 
	int consoleHeight = surface->getHeight() / 2; 
	count = consoleHeight / 16 - 1;

	for( string str : strings )
	{
		if( count < 0 )
			break; 
		RECT rect = { 0, count * FONT_HEIGHT - 6, 0, 0 }; 	
		m_font->DrawTextA( 0, &str[0], -1, &rect, DT_NOCLIP, fontColor );	
		count--; 
	}
		

	RECT rect1 = { 0, surface->getHeight() / 2 - FONT_HEIGHT, 0, 0 }; 

	int ticks = GetTickCount(); 

	if( m_tickCount == 0 )
	{
		m_tickCount = ticks; 
	}

	int period = 500; 

	if( ticks > m_tickCount + period )
	{

		m_cursor = true; 
		m_tickCount = ticks; 
	}
	else if( ticks > m_tickCount + period / 2 )
	{
		m_cursor = false; 
	}

	string inputLine = ">" + AGConsoleManager::getInstance().getInputLine(); 
	inputLine +=  m_cursor ? "" : "_";

	m_font->DrawTextA( 0, &inputLine[0], -1, &rect1, DT_NOCLIP, fontColor );	
}

void AGConsole::setTexture(ID3D10ShaderResourceView* texture)
{
	m_var->SetResource( texture );
}

