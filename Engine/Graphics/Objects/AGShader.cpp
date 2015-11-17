#include "AGShader.h"

#include "Engine/Managers/AGLogger.h"

#include "Engine/Graphics/Objects/AGCamera.h"

#include "Engine/Graphics/AGGraphics.h"

AGShader::AGShader( const std::wstring& shaderName )
{
	m_type = 0; 
	
	m_surfaces = AGGraphics::getInstance().getSurfaces();

	int shadersFlags = D3D10_SHADER_ENABLE_STRICTNESS; 
#ifdef _DEBUG
	//shadersFlags |= D3D10_SHADER_DEBUG; 
#endif 
	ID3D10Blob* blob; 
	HRESULT hr = S_OK; 

	const wstring mapNames[] = 
	{
		L"amb",
		L"dif",
		L"spcclr",
		L"spclvl",
		L"gls",
		L"slfilm",
		L"opc",
		L"fltrclr",
		L"bmp",
		L"rfl",
		L"rfr",
		L"nrm"
	};

	const int mapTypes[] = 
	{
		AGShaderMap::Amb,
		AGShaderMap::Dif,
		AGShaderMap::SpecColor,
		AGShaderMap::SpecLvl,
		AGShaderMap::Gloss,
		AGShaderMap::SelfIllum,
		AGShaderMap::Opacity,
		AGShaderMap::FilterColor,
		AGShaderMap::Bump,
		AGShaderMap::Reflaction,
		AGShaderMap::Refraction,
		AGShaderMap::Normals
	};

	std::wstring tempStr = shaderName; 
	tempStr = tempStr.substr( 0, tempStr.find( L"." ) );
	int curMap = 0;
	int findPos = -1; 


	if( shaderName == L"billboard.fx" )
	{
		m_type |= AGShaderMap::Dif; 
	}
	else 
	{
		for( int i = 0; i < 12; i++ )
		{
			findPos = tempStr.find( mapNames[ i ] );
			if( findPos != std::wstring::npos )
			{
				m_type |= mapTypes[ i ];
				tempStr = tempStr.substr( findPos + mapNames[ i ].length() );
			}
		}
	}

	const string textResourcesNames[] = 
	{
		"txAmb",
		"txDiff",
		"txSpecClr",
		"txSpecLvl",
		"txGloss",
		"txSelfIllum",
		"txOpac",
		"txFiltClr",
		"txBump",
		"txRefl",
		"txRefr",
		"txNorm"
	};

	std::wstring fullPath = L"data/shaders/";
	fullPath+= shaderName; 

	m_lastSlot = 0; 

	for( int i = 0; i < 12; i++ )
	{
		if( m_type & mapTypes[ i ] )
		{
			m_lastSlot = i; 
		}
	}

	for( AGSurface* surface : m_surfaces )
	{
		ID3D10Effect* dxEffect; 
		ID3D10Device* device = surface->getDevice();

		handleDXShaderError( D3DX10CreateEffectFromFile( 
			&fullPath[0], NULL, NULL, "fx_4_0", shadersFlags,
			NULL, device, NULL, NULL, &dxEffect, &blob, NULL ) );

		AGEffect* agEffect = new AGEffect; 
		agEffect->dxEffect = dxEffect; 

		for( int i = 0; i < 12; i++ )
		{
			if( m_type & mapTypes[ i ] )
			{
				ID3D10EffectShaderResourceVariable* resVar = dxEffect->GetVariableByName( textResourcesNames[ i ].c_str() )->AsShaderResource();
				agEffect->maps[ i ] = resVar; 
			}
		}

		agEffect->cameraPos = dxEffect->GetVariableByName( "cameraPos" )->AsVector(); 
		agEffect->worldMatrix = dxEffect->GetVariableByName( "mtxWorld" )->AsMatrix();
		agEffect->viewMatrix = dxEffect->GetVariableByName( "mtxView" )->AsMatrix();
		agEffect->projMatrix = dxEffect->GetVariableByName( "mtxProj" )->AsMatrix();
		
		m_effects[ surface ] = agEffect; 
	}

	m_curSurface = m_surfaces.begin();  
	m_curPass = 0; 
	m_passes = -1; 
}

AGShader::AGShader(AGShaderLoadingData* data)
{
	m_surfaces = std::move( data->surfaces );
	m_passes = -1;
	m_curPass = 0;
	m_type = data->type; 
	m_effects = std::move( data->effects );
	m_lastSlot = 0; 
}

AGShader::~AGShader()
{

}

void AGShader::apply(AGSurface* surface)
{
	if( m_effects.find( surface ) == m_effects.end() )
	{
		AGWarning() << "There is no effect for surface" << AGErrorSnippet; 
		return; 
	}
	AGEffect* effect = m_effects.at( surface );

	AGInputLayout* inputLayout = AGGraphics::getInstance().getInputLayout( surface->getDevice() );

	if( inputLayout )
		surface->getDevice()->IASetInputLayout( inputLayout->vertexInputLayout );

	m_curTechnique = effect->dxEffect->GetTechniqueByName( "Render" );

	AGCamera* camera = surface->getCamera(); 

	if( effect->cameraPos )
	{
		AGVec3 camPos = camera->getPos(); 
		effect->cameraPos->SetRawValue( &camPos, 0, sizeof( AGVec3 ) );
	}
	effect->viewMatrix->SetMatrix( camera->getViewMatrix() );
	effect->projMatrix->SetMatrix( camera->getProjMatrix() );

	D3D10_TECHNIQUE_DESC techDesc;
	m_curTechnique->GetDesc( &techDesc );

	m_curPass = 0; 
	m_passes = techDesc.Passes; 
}

bool AGShader::applyNextPass()
{
	if( m_curPass == m_passes || m_passes < 0 )
		return false; 

	m_curTechnique->GetPassByIndex( m_curPass )->Apply( 0 );
	
	m_curPass++; 

	return true; 
}

void AGShader::setMap(int slot, AGTexture2D* texture, AGSurface* surface)
{
	if( m_effects.find( surface ) == m_effects.end() )
	{
		AGWarning() << "There is no effect for surface" << AGErrorSnippet;
		return; 
	}
	AGEffect* effect = m_effects.at( surface );

	if( effect->maps.find( slot ) == effect->maps.end() )
	{
		AGWarning() << "There is no map in slot: " << slot << AGErrorSnippet;
		return; 
	}

	texture->apply( effect->maps[ slot ], surface );
}

void AGShader::setWorldMatrix(const AGMatrix& world)
{
	for( AGSurface* surface : m_surfaces )
	{
		AGEffect* effect = m_effects.at( surface );
		effect->worldMatrix->SetMatrix( world );
	}
}

int AGShader::addNewTextureVar(const std::string& varName)
{
	for( AGSurface* surface : m_surfaces )
	{
		AGEffect* effect = m_effects.at( surface );
		effect->maps[ m_lastSlot ] = effect->dxEffect->GetVariableByName( varName.c_str() )->AsShaderResource();
	}
	m_lastSlot++;
	return m_lastSlot-1; 
}

void AGShader::setArray(int slot, AGTexture2DArray* txArray, AGSurface* surface)
{
	if( m_effects.find( surface ) == m_effects.end() )
	{
		AGWarning() << "There is no effect for surface" << AGErrorSnippet;
		return; 
	}
	AGEffect* effect = m_effects.at( surface );

	if( effect->maps.find( slot ) == effect->maps.end() )
	{
		AGWarning() << "There is no map in slot: " << slot << AGErrorSnippet;
		return; 
	}

	txArray->apply( effect->maps[ slot ], surface );
}

int AGShader::addNewVar(const std::string& varName)
{
	int slot = 0; 
	for( AGSurface* surface : m_surfaces )
	{
		AGEffect* effect = m_effects.at( surface );
		ID3D10EffectVariable* var = effect->dxEffect->GetVariableByName( varName.c_str() );
		if( var )
		{
			slot = effect->vars.size(); 
			effect->vars.push_back( var );
		}
	}
	return slot; 
}

void AGShader::setAsFloat(int var, float value)
{
	for( AGSurface* surface : m_surfaces )
	{
		AGEffect* effect = m_effects.at( surface );
		handleDXError( effect->vars.at( var )->AsScalar()->SetFloat( value ) );
	}
}

void AGShader::setVar(int var, AGVec3 value)
{
	for( AGSurface* surface : m_surfaces )
	{
		AGEffect* effect = m_effects.at( surface );
		handleDXError( effect->vars.at( var )->AsVector()->SetFloatVector( value ) );
	}
}

