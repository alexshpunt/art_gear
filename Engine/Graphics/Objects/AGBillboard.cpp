#include "AGBillboard.h"

#include <vector>

#include "Engine/Graphics/AGGraphics.h"

#include "Engine/Graphics/Objects/AGBuffer.h"
#include "Engine/Graphics/Objects/AGShader.h"
#include "Engine/Graphics/Objects/AGCamera.h"

#include "Engine/Graphics/Objects/Textures/AGTexture2D.h"

#include "Engine/Managers/AGResourceManager.h"

#include "Engine/Utils/AGConversion.h"

class AGBillboardPrivate 
{
	public:
		~AGBillboardPrivate()
		{
			delete vbo;
		}

		AGBuffer< AGBillboardVertex >* vbo; 
		ID3D10InputLayout* inputLayout; 
		AGShader* shader; 
		AGResPtr resPtr;
		AGTexture2D* texture;  

		D3DXVECTOR3 pos;
		D3DXVECTOR2 size; 

};

AGBillboard::AGBillboard()
{
		m_p = new AGBillboardPrivate; 

		m_p->pos = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
		m_p->size = D3DXVECTOR2( 0.5f, 0.5f ); 
	
		m_p->vbo = nullptr; 
		setup(); 

		m_p->shader = AGResourceManager::getInstance().getShader( L"billboard" );
		m_p->texture = AGResourceManager::getInstance().getTexture( L"gizmos/dir.png" );
		m_p->resPtr = m_p->texture; 
		
}

AGBillboard::~AGBillboard()
{
	delete m_p; 
}

void AGBillboard::setPos(const AGVec3& pos)
{
	m_p->pos = AGConversion::toD3DXVec3D( pos ); 
}

const AGVec3& AGBillboard::getPos() const
{
	return AGConversion::toAGVec3D( m_p->pos );
}

void AGBillboard::setSize(const AGSize& size)
{
	m_p->size = D3DXVECTOR2( size.getWidth(), size.getHeight() );
}

const AGSize& AGBillboard::getSize() const
{
	return AGSize( m_p->size.x, m_p->size.y );
}

void AGBillboard::draw(AGSurface* surface)
{
	AGCamera* camera = surface->getCamera();
	ID3D10Device* device = surface->getDevice();

	if( !m_p->shader )
		return; 

	m_p->shader->applySurface( surface );

	if( !m_p->texture->isValid() )
		return; 

	m_p->shader->setMap( AGShaderMapSlots::DifSlot, m_p->texture, surface );

	if( !m_p->vbo )
		return; 

	m_p->vbo->apply( surface );

	while( m_p->shader->applyNextPass() )
	{
		device->Draw( 4, 0 );
	}
}

void AGBillboard::setup()
{
	if( m_p->vbo )
		delete m_p; 

	AGBillboardVertex vertex;
	vertex.pos = m_p->pos;
	vertex.size = m_p->size; 
	
	m_p->vbo = new AGBuffer< AGBillboardVertex >( vector< AGBillboardVertex >( &vertex, &vertex + 1 ), AGBufferType::Vertex );
}

void AGBillboard::setTexture(AGTexture2D* texture)
{
	m_p->texture = texture; 
	m_p->resPtr = m_p->texture;
}

