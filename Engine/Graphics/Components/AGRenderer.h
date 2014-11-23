#ifndef AG_RENDERER_H
#define AG_RENDERER_H

#include <d3dx10.h>
#include <d3d10.h>
#include <string>

#include "Objects/AGComponent.h"
#include "Graphics/Objects/AGDXBoundingBox.h"

using namespace std;

class AGGraphics; 
class AGSurface; 
class AGDXMesh;
class AGObject; 
class AGDXAxises; 

class AGRenderer : public AGComponent
{
	public:
		AGRenderer( AGObject* object );
		~AGRenderer();

		void onSceneInit();
		void onSceneUpdate();
		void onSceneFixedUpdate();

		void setSelected( bool value );
		bool isSelected() const;

		void setMesh( AGDXMesh* mesh );
		AGDXMesh* getMesh() const; 

		void loadMeshFrom( const string& fileName, ID3D10Device* device );

		float intersect( D3DXVECTOR3 rayOrigin, D3DXVECTOR3 rayDir );

		void draw( AGDXSurface* surface ); 

	private:
		bool m_isSelected; 
		AGDXMesh* m_mesh;
		AGDXBoundingBox* m_boundingBox; 
		AGDXAxises* m_axises;
};

#endif 