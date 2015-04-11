#ifndef AG_DX10MATERIAL_H
#define AG_DX10MATERIAL_H

#include <vector>
#include <list>
#include <map>
#include <string>
#include <fstream>
#include <d3dx10.h>
#include <d3d10.h>

#include "Engine/Interfaces/AGResource.h"

using namespace std; 

class AGCamera;
class AGShader; 
class AGSurface; 

struct AGTextureResource 
{
	ID3D10EffectShaderResourceVariable* var; 
	ID3D10ShaderResourceView* view; 
};

struct AGShaderResources 
{
	vector< ID3D10ShaderResourceView* > resources; 
};

class AGMaterialLoadingData
{
	public:
		wstring textures[12]; 

		list< AGSurface* > surfaces; 

		AGResPtr resources[ 12 ];

		AGShader* shader; 

		int type; 
};

class AGMaterial 
{
	public:
		AGMaterial( AGMaterialLoadingData* data );
		AGMaterial();
		~AGMaterial();

		const wstring& getTexture( int index ) const; 

		void loadFrom( ifstream& in );
		AGShader* getShader() const; 

		void apply();

	private:
		wstring m_textures[12]; 

		list< AGSurface* > m_surfaces; 

		AGResPtr m_resources[ 12 ];

		AGShader* m_shader; 

		int m_type; 
};

#endif 