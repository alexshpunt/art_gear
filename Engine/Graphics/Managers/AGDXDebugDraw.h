#ifndef AGDX_DEBUGDRAW_H
#define AGDX_DEBUGDRAW_H

#include <d3dx10.h>
#include <d3d10.h>

#include "Graphics/Interfaces/AGSurface.h"
#include "Engine/Patterns/Singleton.h"

class AGDXDebugDraw 
{
	DECLARE_SINGLETON_INIT( AGDXDebugDraw )
	public:
		void initialize( ID3D10Device* device );
		void drawLine( AGDXSurface* surface, D3DXVECTOR3 start, D3DXVECTOR3 end, D3DXVECTOR4 color );
	private:
		void init(); 
		bool m_isInitialized;

		ID3D10InputLayout* m_inputLayout; 

		ID3D10Effect* m_effect;
		ID3D10EffectTechnique* m_technique; 

		ID3D10EffectMatrixVariable* m_worldVar; 
		ID3D10EffectMatrixVariable* m_viewVar;
		ID3D10EffectMatrixVariable* m_projectionVar;

		ID3D10Buffer* m_vertexBuffer; 
		ID3D10Buffer* m_indexBuffer; 

		ID3D10DepthStencilState* m_depthState; 
};

#endif 