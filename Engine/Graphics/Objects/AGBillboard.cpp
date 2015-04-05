#include "AGBillboard.h"

#include <assert.h>
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

		AGVec3 pos;
		AGSize size; 
};

AGBillboard::AGBillboard()
{
		m_p = new AGBillboardPrivate; 

		m_p->pos = AGVec3( 0.0f, 0.0f, 0.0f );
		m_p->size = AGSize( 0.5f, 0.5f ); 
	
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
	m_p->pos = pos; 
}

const AGVec3& AGBillboard::getPos() const
{
	return m_p->pos;
}

void AGBillboard::setSize(const AGSize& size)
{
	m_p->size = size;
}

const AGSize& AGBillboard::getSize() const
{
	return getSize();
}

void AGBillboard::draw(AGSurface* surface)
{
	AGCamera* camera = surface->getCamera();
	ID3D10Device* device = surface->getDevice();

	assert( camera );
	assert( device );
	assert( m_p->shader );

	m_p->shader->apply( surface );

	assert( m_p->texture->isValid() );

	m_p->shader->setMap( AGShaderMapSlots::DifSlot, m_p->texture, surface );

	assert( m_p->vbo );

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
	vertex.size = D3DXVECTOR2( m_p->size.getWidth(), m_p->size.getHeight() ); 
	
	m_p->vbo = new AGBuffer< AGBillboardVertex >( vector< AGBillboardVertex >( &vertex, &vertex + 1 ), AGBufferType::Vertex );
}

void AGBillboard::setTexture(AGTexture2D* texture)
{
	m_p->texture = texture; 
	m_p->resPtr = m_p->texture;
}

