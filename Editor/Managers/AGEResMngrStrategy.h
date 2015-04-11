#ifndef AGE_RESOURCEMANAGER_H
#define AGE_RESOURCEMANAGER_H

#include <fstream>
#include <mutex>

#include <QApplication>

#include "Engine/Managers/AGResourceManager.h"

#include "Engine/Graphics/Objects/AGShader.h"
#include "Engine/Graphics/Objects/AGMesh.h"
#include "Engine/Graphics/Objects/Textures/AGTexture2D.h"
#include "Engine/Graphics/Objects/AGMaterial.h"

class AGEResMngrStrategy : public AGResourceManagerStrategy
{
	public:
		AGEResMngrStrategy( QApplication& app );
		~AGEResMngrStrategy();
		
		void initShaders() override; 
		AGShader* getShader( const std::wstring& shaderName );

		AGMesh* getMesh( const std::string& fileName ) override;
		AGTexture2D* getTexture( const std::wstring& fileName ) override;

	private:
		AGShader* loadShader( const std::wstring& shaderName );
		AGTexture2D* loadTexture( const std::wstring& fileName );
		AGMesh* loadMesh( const std::string& fileName );
		AGSubMeshLoadingData* loadSubMesh( std::ifstream& in );
		AGMaterial* loadMaterial( std::ifstream& in );

		QApplication& m_app; 

		std::mutex m; 
};

#endif 