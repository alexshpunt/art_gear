#ifndef AG_RENDERER_H
#define AG_RENDERER_H

#include <d3dx10.h>
#include <d3d10.h>
#include <string>

#include "Objects/AGComponent.h"
#include "Graphics/Interfaces/AGPureInterfaces.h"
#include "Engine/Graphics/Objects/Shapes/AGBoxShape.h"
#include "Engine/Interfaces/AGResource.h"
#include "Engine/Interfaces/AGMovable.h"

using namespace std;

class AGGraphics; 
class AGSurface; 
class AGMesh;
class AGGameObject; 

class AGRenderer : public AGComponent, public AGMovable
{
	public:
		AGRenderer( AGGameObject* object );
		~AGRenderer();

		void notify(  AGGameObject::Change change ); 

		void onSceneInit();
		void onSceneUpdate();
		void onSceneFixedUpdate();

		void setSelected( bool value );
		bool isSelected() const;

		void setMesh( AGMesh* mesh );
		AGMesh* getMesh() const; 

		void loadMeshFrom( const string& fileName ); 
		float intersect( const AGVec3& rayOrigin, const AGVec3& rayDir );

		void draw( AGSurface* surface ); 

	private:
		void handleChanges( Changes changes );

		bool m_isSelected; 
		AGResPtr m_mesh; 
		//AGMesh* m_mesh;
		AGBoxShape* m_boundingBox; 
};

#endif 