#include "AGDX10Scene.h"

#include <QDebug>

#include "AGDX10Camera.h"
#include "AGDX10Mesh.h"

AGDX10Scene::AGDX10Scene()
{
}

AGDX10Scene::~AGDX10Scene()
{

}

void AGDX10Scene::addMesh(AGDX10Mesh* mesh)
{
	m_meshes.push_back( mesh );
}

void AGDX10Scene::removeMesh(AGDX10Mesh* mesh)
{

}

vector< AGDX10Mesh* > AGDX10Scene::getMeshes() const
{
	return m_meshes; 
}

void AGDX10Scene::addCamera(AGDX10Camera* camera)
{
	m_cameras.push_back( camera );
	m_camerasByLayer[ camera->getLayer() ] = camera; 
}

void AGDX10Scene::removeCamera(AGDX10Camera* camera)
{

}

vector< AGDX10Camera* > AGDX10Scene::getCameras() const
{
	return m_cameras; 
}


void AGDX10Scene::draw(ID3D10Device* device)
{
	for( AGDX10Camera* camera : m_cameras )
	{
		camera->update();
		for( AGDX10Mesh* mesh : m_meshes )
		{
			mesh->draw( device, camera );
		}
	}
}

AGDX10Camera* AGDX10Scene::getTopCamera() const
{
	int layer = m_cameras[ 0 ]->getLayer();
	AGDX10Camera* topCamera = m_cameras[ 0 ];

	for( AGDX10Camera* camera : m_cameras )
	{
		if( camera->getLayer() > layer )
		{
			topCamera = camera;
			layer = camera->getLayer();
		}
	} 
	return topCamera; 
}







