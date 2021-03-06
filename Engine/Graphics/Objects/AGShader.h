#ifndef AG_SHADER_H
#define AG_SHADER_H

#include <string>
#include <list>
#include <map>

#include <d3dx10.h>
#include <d3d10.h>

#include "Engine/Graphics/Interfaces/AGSurface.h"
#include "Engine/Graphics/Objects/Textures/AGTexture2D.h"
#include "Engine/Graphics/Objects/Textures/AGTexture2DArray.h"

enum AGShaderMap{ 
	Amb = 0x001, 
	Dif = 0x002,
	SpecColor = 0x004,
	SpecLvl = 0x008,
	Gloss = 0x010,
	SelfIllum = 0x020, 
	Opacity = 0x040,
	FilterColor = 0x080,
	Bump = 0x100, 
	Reflaction = 0x200,
	Refraction = 0x400,
	Normals = 0x800
	};

enum AGShaderMapSlots{ 
	AmbSlot = 0, 
	DifSlot = 1,
	SpecColorSlot = 2,
	SpecLvlSlot = 3,
	GlossSlot = 4,
	SelfIllumSlot = 5, 
	OpacitySlot = 6,
	FilterColorSlot = 7,
	BumpSlot = 8, 
	ReflactionSlot = 9,
	RefractionSlot = 10,
	NormalsSlot = 11
};

struct AGEffect
{
	ID3D10Effect* dxEffect; 

	std::map< int, ID3D10EffectShaderResourceVariable* > maps; 
	std::vector< ID3D10EffectVariable* > vars; 

	ID3D10EffectVectorVariable* cameraPos;

	ID3D10EffectMatrixVariable* worldMatrix;
	ID3D10EffectMatrixVariable* viewMatrix;
	ID3D10EffectMatrixVariable* projMatrix;
};

struct AGShaderLoadingData 
{
	std::list< AGSurface* > surfaces; 
	std::map< AGSurface*, AGEffect* > effects; 
	std::map< AGSurface*, ID3D10InputLayout* > inputLayouts; 
	int type;
};

class AGShader 
{
	public:
		AGShader( AGShaderLoadingData* data );
		AGShader( const std::wstring& shaderName ); 
		virtual ~AGShader(); 

		void apply( AGSurface* surface );
		bool applyNextPass(); 

		void setMap( int slot, AGTexture2D* texture, AGSurface* surface ); 
		void setArray( int slot, AGTexture2DArray* txArray, AGSurface* surface );

		void setWorldMatrix( const AGMatrix& world );
		int addNewTextureVar( const std::string& varName );
		int addNewVar( const std::string& varName );
		void setAsFloat( int var, float value );
		void setVar( int var, AGVec3 value );
	private:
		std::list< AGSurface* > m_surfaces; 
		std::map< AGSurface*, AGEffect* > m_effects; 
		std::map< AGSurface*, ID3D10InputLayout* > m_inputLayouts; 

		std::list< AGSurface* >::iterator m_curSurface; 
		ID3D10EffectTechnique* m_curTechnique; 
		int m_curPass; 
		int m_passes; 

		int m_lastSlot;
		int m_type;
};

#endif 