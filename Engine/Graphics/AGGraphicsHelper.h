#ifndef AG_GRAPHICSHELPER_H
#define AG_GRAPHICSHELPER_H

#include <d3dx10.h>
#include <d3d10.h>
#include <dxgi.h>
#include <DxErr.h>

#include <string>

#include "Engine/Managers/AGLogger.h"

//std::wstring expr = #( __EXPR__ );\

/*std::wstring errDesc = DXGetErrorDescription( hr ); \
	std::wstring errString = DXGetErrorString( hr ); \
	std::wstring sep = L" ";\ */

#define handleDXError( __EXPR__ )\
{\
	HRESULT hr = ( __EXPR__ );\
	if( FAILED( hr ) )\
	{ \
		std::wstring errDesc = DXGetErrorDescription( hr );\
		std::wstring errString = DXGetErrorString( hr );\
		std::wstring sep = L" ";\
		std::string expr = #__EXPR__;\
		AGError() << AGErrorSnippet << errDesc + sep + errString + sep << expr; abort();\
	}\
}

#define handleDXShaderError( __EXPR__ )\
{\
	ID3D10Blob* blob;\
	HRESULT hr = ( __EXPR__ );\
	if( FAILED( hr ) )\
	{\
		std::wstring errDesc = DXGetErrorDescription( hr );\
		std::wstring errString = DXGetErrorString( hr );\
		std::wstring sep = L" ";\
		std::string expr = #__EXPR__;\
		std::string shaderLog = (char*)blob->GetBufferPointer(); \
		AGError() << AGErrorSnippet << errDesc + sep + errString + sep << expr << sep << shaderLog; abort(); \
	}\
}

#endif 