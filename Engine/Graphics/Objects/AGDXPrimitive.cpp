#include "AGDXPrimitive.h"

#include <string>

#include <math.h>
#include "Managers/AGLogger.h"
#include "AGDXCamera.h"

using namespace std;

AGDXPrimitive::AGDXPrimitive(ID3D10Device* device) : AGDXMovable()
{
	wstring fileName = L"data/shaders/difprim.fx";

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

	m_worldVar = m_effect->GetVariableByName( "mtxWorld" )->AsMatrix();
	m_viewVar = m_effect->GetVariableByName( "mtxView" )->AsMatrix();
	m_projectionVar = m_effect->GetVariableByName( "mtxProj" )->AsMatrix();

	m_technique = m_effect->GetTechniqueByName( "Render" );

	D3D10_INPUT_ELEMENT_DESC layout[] = 
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D10_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",   0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D10_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = 2; 

	D3D10_PASS_DESC passDesc; 
	m_technique->GetPassByIndex( 0 )->GetDesc( &passDesc );
	hr = device->CreateInputLayout( layout, numElements, passDesc.pIAInputSignature, passDesc.IAInputSignatureSize, &m_inputLayout );

	if( FAILED( hr ) )
	{
		AGError() << "Couldn't create input layout";
		return;
	}

	device->IASetInputLayout( m_inputLayout );
}

AGDXPrimitive::~AGDXPrimitive()
{

}
