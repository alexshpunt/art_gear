#ifndef AG_DX10MATERIAL_H
#define AG_DX10MATERIAL_H

#include <string>
#include <fstream>
#include <d3dx10.h>
#include <d3d10.h>

using namespace std; 

class AGDX10Camera;

struct AGDX10TextureResource 
{
	ID3D10EffectShaderResourceVariable* var; 
	ID3D10ShaderResourceView* view; 
};

class AGDX10Material 
{
	public:
		AGDX10Material();
		~AGDX10Material();

		const wstring& getTexture( int index ) const; 

		void loadFrom( ifstream& in, ID3D10Device* device );

		void setWorldMatrix( D3DXMATRIX world );
		void setViewMatrix( D3DXMATRIX view );
		void setProjMatrix( D3DXMATRIX proj );

		void apply( ID3D10Device* device );

	private:
		wstring m_textures[12]; 
		
		ID3D10InputLayout* m_inputLayout; 

		ID3D10Effect* m_effect;
		ID3D10EffectTechnique* m_technique; 

		ID3D10EffectMatrixVariable* m_worldVar; 
		ID3D10EffectMatrixVariable* m_viewVar;
		ID3D10EffectMatrixVariable* m_projectionVar;
};

#endif 