#include "AGELight.h"

#include "Engine/Graphics/Objects/AGLight.h"

#include "Engine/Graphics/Objects/Shapes/AGBoxShape.h"
#include "Engine/Graphics/Objects/Shapes/AGConeShape.h"
#include "Engine/Graphics/Objects/Shapes/AGLine.h"
#include "Engine/Graphics/Objects/Shapes/AGCylinderShape.h"
#include "Engine/Graphics/Objects/Shapes/AGSphereShape.h"

#include "AGEDaylightShape.h"

#include "Engine/Graphics/Objects/AGBillboard.h"

#include "Engine/Graphics/AGGraphics.h"
#include "Engine/Managers/AGResourceManager.h"

class AGELightPrivate
{
	public:	
		AGELightPrivate()
		{
			light = nullptr;
			
			posBox = nullptr; 
			dirBox = nullptr;
			
			hotspotCone = nullptr;
			posCone = nullptr;

			pointHotspot = nullptr;
			pointFalloff = nullptr;

			dirCylinder = nullptr;
			daylightShape = nullptr;
			sunlightGizmo = nullptr;
			pointGizmo = nullptr;
			line = nullptr; 

			isSelected = false; 
		}
		~AGELightPrivate()
		{
			delete light;

			delete posBox; 
			delete dirBox;
			
			delete hotspotCone;
			delete posCone;
			
			delete pointHotspot;
			delete pointFalloff; 

			delete dirCylinder;
			delete daylightShape;
			delete sunlightGizmo;
			delete pointGizmo; 
			delete line;
		}

		AGLight* light; 

		AGBoxShape* posBox; 
		AGBoxShape* dirBox;

		AGConeShape* falloffCone;
		AGConeShape* hotspotCone; 
		AGConeShape* posCone; 

		AGSphereShape* pointHotspot; 
		AGSphereShape* pointFalloff; 

		AGCylinderShape* dirCylinder; 
		AGEDaylightShape* daylightShape; 

		AGBillboard* sunlightGizmo; 
		AGBillboard* pointGizmo; 

		AGLine* line;	

		AGVec3 dir; 

		bool isSelected; 
};

AGELight::AGELight()
{
	m_p = new AGELightPrivate; 
	m_p->posCone = new AGConeShape( 0.05f, 0.1f );
	m_p->hotspotCone = new AGConeShape( 0.5f, 1.0f, AGColor( 0.8f, 0.72f, 0.18f, 1.0f ) );
	m_p->falloffCone = new AGConeShape( 0.52f, 1.0f, AGColor( 0.52f, 0.48f, 0.18f, 1.0f ) );

	m_p->dir = AGVec3( 0.0f, 1.0f, 0.0f );

	m_p->hotspotCone->setLookAt( m_p->dir );
	m_p->falloffCone->setLookAt( m_p->dir );

	m_p->sunlightGizmo = new AGBillboard;
	m_p->sunlightGizmo->setTexture( AGResourceManager::getInstance().getTexture( L"gizmos/dir.png" ) ); 
	m_p->pointGizmo = new AGBillboard;
	m_p->pointGizmo->setTexture( AGResourceManager::getInstance().getTexture( L"gizmos/omni.png" ) );

	m_p->dirBox = new AGBoxShape( 0.1f ); 
	m_p->dirBox->setWorldPos( m_p->dir );

	m_p->posBox = new AGBoxShape( 0.1f ); 

	m_p->pointHotspot = new AGSphereShape( 0.5f, AGColor( 0.8f, 0.72f, 0.18f ) ); 
	m_p->pointFalloff = new AGSphereShape( 0.6, AGColor( 0.52f, 0.48f, 0.18f ) );

	m_p->dirCylinder = new AGCylinderShape( 0.5f, 1.0f, AGColor( 0.8f, 0.72f, 0.18f ) );
	m_p->daylightShape = new AGEDaylightShape( 0.2f, 0.5f, AGColor( 0.8f, 0.72f, 0.18f ) );
	m_p->daylightShape->setLookAt( m_p->dir ) ;

	m_p->posCone->setWorldPos( 0.0, 0.0f, 0.0f ); 

	m_p->line = new AGLine( m_p->posCone->getWorldPos(), m_p->posCone->getWorldPos() + m_p->dir, D3DXVECTOR4( 0.0f, 0.0f, 1.0f, 1.0f ) );

	m_p->light = new AGLight;
	AGGraphics::getInstance().addLight( m_p->light );
	AGGraphics::getInstance().addClickableObject( this ); 
}

AGELight::~AGELight()
{
	AGGraphics::getInstance().removeLight( m_p->light );
	delete m_p; 
}

void AGELight::draw(AGSurface* surface)
{
	AGLight::LightType lightType = m_p->light->getLightType(); 

	if( lightType == AGLight::Point )
	{
		m_p->pointGizmo->draw( surface );
	}
	else if( lightType == AGLight::Spot || lightType == AGLight::Daylight || lightType == AGLight::Directional  )
	{
		m_p->posBox->draw( surface );
	}
	else if( lightType == AGLight::Spot )
	{
		m_p->posCone->draw( surface );
	}

	if( !m_p->isSelected )
		return; 

	if( lightType == AGLight::Directional )
	{
		m_p->dirCylinder->draw( surface );
		m_p->dirBox->draw( surface );
		m_p->line->draw( surface );
	}
	else if( lightType == AGLight::Spot )
	{
		m_p->dirBox->draw( surface );
		m_p->hotspotCone->draw( surface );
		m_p->falloffCone->draw( surface );
		m_p->line->draw( surface );
	}
	else if( lightType == AGLight::Daylight )
	{
		m_p->daylightShape->draw( surface );
		m_p->dirBox->draw( surface );
		m_p->line->draw( surface );
	}
	else if( lightType == AGLight::Point )
	{
		m_p->pointHotspot->draw( surface );
		m_p->pointFalloff->draw( surface );
	}
}

float AGELight::intersect(AGVec3 rayOrigin, AGVec3 rayDir)
{
	return m_p->posBox->intersect( rayOrigin, rayDir );
}

bool AGELight::mouseMoveEvent(AGSurface* surface)
{
	return false; 
}

bool AGELight::mouseClickEvent(AGMouseButton button, AGSurface* surface)
{
	if( button != LMB )
		return false; 
	calculateRays( surface, m_p->posBox->getResultMatrix() );

	float dist = m_p->posBox->intersect( m_rayOrigin, m_rayDir );
	m_p->isSelected = dist > 0.0f; 

	return m_p->isSelected;
}

AGLight* AGELight::getLight() const
{
	return m_p->light; 
}

