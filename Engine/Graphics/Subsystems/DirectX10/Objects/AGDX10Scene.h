#ifndef AGDX10_SCENE_H
#define AGDX10_SCENE_H

#include <d3dx10.h>
#include <d3d10.h>
#include <vector>
#include <map>

using namespace std;

class AGDX10Mesh;
class AGDX10Camera; 
class AGDX10Light; 

class AGDX10Scene 
{
	public:
		AGDX10Scene();
		~AGDX10Scene();

		void addMesh( AGDX10Mesh* mesh );
		void removeMesh( AGDX10Mesh* mesh );
		vector< AGDX10Mesh* > getMeshes() const; 

		void addCamera( AGDX10Camera* camera );
		void removeCamera( AGDX10Camera* camera );
		AGDX10Camera* getTopCamera() const; 
		vector< AGDX10Camera* > getCameras() const; 
		
		void draw( ID3D10Device* device );

	private:
		vector< AGDX10Mesh* > m_meshes;
		vector< AGDX10Camera* > m_cameras; 
		map< int, AGDX10Camera* > m_camerasByLayer; 

		
};

#endif 