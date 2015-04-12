#ifndef AG_SURFACE_H
#define AG_SURFACE_H

#include <d3d10.h>
#include <d3dx10.h>

#include "Math/AGMath.h"

class AGCamera; 

class AGSurface 
{
	public:
		enum AGSurfaceMode{ Wireframe, Simple, Shaded, EdgedFaces };
		enum AGSurfaceCameraMode{ Perspective, Orthographics, Top, Bottom, Left, Right, Back, Front };

		AGSurface();
		virtual ~AGSurface();

		void resizeSurface( float width, float height ); 

		void setMaximizedMode( bool value ); 
		bool isMaximizedMode() const; 

		void setSurfaceMode( AGSurfaceMode surfaceMode );
		AGSurfaceMode getSurfaceMode() const; 

		void setCameraMode( AGSurfaceCameraMode cameraMode );
		AGSurfaceCameraMode getCameraMode() const; 

		void setRenderTargets(); 
		void clearRenderTargets();
		void present(); 
		void swapChainPresent(); 

		void setCamera( AGCamera* camera ); 
		AGCamera* getCamera() const; 

		ID3D10Device* getDevice() const;

		const AGSize& getSize() const;
		float getWidth() const;
		float getHeight() const; 

		unsigned getId() const; 

		void draw( unsigned int nVertices, unsigned int offset );
		void drawIndexed( unsigned int indexCount, unsigned int startIndexLocation, unsigned int baseVertexLocation ); 

		bool isMainSurface() const;
	protected:
		void setup( float width, float height, HWND hwnd, bool mainSurface = true );

		void createRenderTargets( int width, int height );
		void releaseRenderTargets(); 

		bool m_isMainSurface; 

		ID3D10Device* m_device; 
		IDXGISwapChain* m_swapChain; 

		ID3D10RenderTargetView* m_diffuseRTV;
		ID3D10RenderTargetView* m_normalRTV;
		ID3D10RenderTargetView* m_posRTV; 
		ID3D10RenderTargetView* m_glossRTV; 
		ID3D10RenderTargetView* m_specRTV; 

		ID3D10ShaderResourceView* m_diffuseResource; 
		ID3D10ShaderResourceView* m_normalResource; 
		ID3D10ShaderResourceView* m_posResource; 
		ID3D10ShaderResourceView* m_glossResource; 
		ID3D10ShaderResourceView* m_specResource; 

		ID3D10EffectShaderResourceVariable* m_diffuseVar;
		ID3D10EffectShaderResourceVariable* m_normalVar;
		ID3D10EffectShaderResourceVariable* m_posVar;
		ID3D10EffectShaderResourceVariable* m_glossVar;
		ID3D10EffectShaderResourceVariable* m_specVar;

		ID3D10EffectVariable* m_camPosVar; 
		ID3D10EffectVariable* m_lightVar; 

		ID3D10Effect* m_effect;
		ID3D10EffectTechnique* m_technique; 

		ID3D10InputLayout* m_vertexLayout;
		ID3D10Buffer* m_vertexBuffer; 

		ID3D10RenderTargetView* m_renderTargetView; 
		ID3D10DepthStencilView* m_depthStencilView; 
		ID3D10Texture2D* m_depthBuffer;
		AGCamera* m_camera; 
		HWND m_hwnd;
		AGSize m_size; 

		AGSurfaceMode m_surfaceMode; 
		AGSurfaceCameraMode m_surfaceCameraMode; 

		bool m_isMaximized; 

		unsigned int m_id; 
};

#endif 