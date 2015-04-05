#ifndef AG_CONSOLE_H
#define AG_CONSOLE_H

#include <d3dx10.h>
#include <d3d10.h>

class AGSurface;

class AGConsole 
{
	public:
		AGConsole(  ID3D10Device* device  );
		~AGConsole();

		void setTexture( ID3D10ShaderResourceView* texture ); 
		void draw( AGSurface* surface ); 
	private:
		ID3D10InputLayout* m_inputLayout; 

		ID3D10Effect* m_effect;
		ID3D10EffectTechnique* m_technique; 
		
		ID3DX10Font* m_font; 
		int m_tickCount;
		int m_dTickCount; 
		bool m_cursor; 

		ID3D10EffectShaderResourceVariable* m_var; 
		ID3D10ShaderResourceView* m_view; 

		ID3D10Buffer* m_vertexBuffer; 
}; 

#endif 