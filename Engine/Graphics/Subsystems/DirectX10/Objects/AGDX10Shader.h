#ifndef AG_DX10SHADER_H
#define AG_DX10SHADER_H

#include <d3dx10.h>
#include <d3d10.h>

#include <string>

using namespace std;

class AGDX10Material; 
class AGDX10Camera; 

struct AGDX10TextureResource 
{
	ID3D10EffectShaderResourceVariable* var; 
	ID3D10ShaderResourceView* view; 
};

class AGDX10Shader 
{
	public:
		AGDX10Shader();
		~AGDX10Shader();

		void initialize( const AGDX10Material* material, ID3D10Device* device  ); 
		void apply( AGDX10Camera* camera ); 
	private:
		ID3D10InputLayout* m_inputLayout; 

		ID3D10Effect* m_effect;
		ID3D10EffectTechnique* m_technique; 

		ID3D10EffectMatrixVariable* m_worldVar; 
		ID3D10EffectMatrixVariable* m_viewVar;
		ID3D10EffectMatrixVariable* m_projectionVar;

		D3DXMATRIX m_world;
		D3DXMATRIX m_view;
		D3DXMATRIX m_proj; 
};

#endif 