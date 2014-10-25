#ifndef AGE_WINDOW_H
#define AGE_WINDOW_H

#include <d3d10.h>
#include <d3dx10.h>
#include <QWidget>

#include "Engine/Graphics/AGWindow.h"

class AGDX10Mesh;
class AGDX10Scene; 

class AGEWindow : public QWidget 
{
	Q_OBJECT
	public:
		AGEWindow();
		~AGEWindow();

		void setScene( AGDX10Scene* scene );

		QPaintEngine* paintEngine() const; 
		ID3D10Device* getDevice() const; 
	protected:
		void paintEvent( QPaintEvent* event );
		void resizeEvent( QResizeEvent* event );
		bool nativeEvent( const QByteArray &eventType, void *message, long *result );
		void mouseClickEvent( QString btn );  
	private:
		ID3D10Device* m_device; 
		IDXGISwapChain* m_swapChain; 
		ID3D10RenderTargetView* m_renderTargetView; 
		ID3D10DepthStencilView* m_depthStencilView; 
		ID3D10InputLayout* m_vertexLayout; 
		ID3D10Buffer* m_buffer; 
		ID3D10Texture2D* m_depthBuffer; 

		AGDX10Mesh* m_mesh; 

		AGDX10Scene* m_scene; 
};

#endif 