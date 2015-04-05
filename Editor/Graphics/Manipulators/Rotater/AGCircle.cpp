#include "AGCircle.h"

#include "Engine/Managers/AGLogger.h"
#include "Engine/Graphics/Interfaces/AGSurface.h"
#include "Engine/Graphics/Objects/AGCamera.h"

#include <Engine/Graphics/AGGraphics.h>

AGCircle::AGCircle( CircleAxis axis)
{
	m_axis = axis; 
	m_isSelected = false; 

	D3DXVECTOR4 color( (axis == X_AXIS) * 0.798431372, (axis == Y_AXIS) * 0.6117647058, (axis == Z_AXIS) * 0.76470588233, 1.0f );
	D3DXVECTOR4 yellow( 1.0f, 1.0f, 0.0f, 1.0f );
	float k = 0.15f;
	float height = 1.0f;
	float radius = 1.0f;
	float d = 0.025f;

	AGPrimitiveVertex vertices[] = 
	{
		{ D3DXVECTOR3( k * radius * 0.999525, k * height * 0.0150551, k * radius * 3.65244e-010 ), color }, //0 
		{ D3DXVECTOR3( k * radius * 0.962182, k * height * 0.0150551, k * radius * 0.265132 ), color }, //1 
		{ D3DXVECTOR3( k * radius * 0.96379, k * height * 0.0150551, k * radius * 0.265509 ), color }, //2 
		{ D3DXVECTOR3( k * radius * 0.997866, k * height * 0.0150551, k * radius * -1.22005e-009 ), color }, //3 
		{ D3DXVECTOR3( k * radius * 0.861525, k * height * 0.0150551, k * radius * 0.503425 ), color }, //4 
		{ D3DXVECTOR3( k * radius * 0.862942, k * height * 0.0150551, k * radius * 0.504253 ), color }, //5 
		{ D3DXVECTOR3( k * radius * 0.705417, k * height * 0.0150551, k * radius * 0.705417 ), color }, //6 
		{ D3DXVECTOR3( k * radius * 0.706578, k * height * 0.0150551, k * radius * 0.706578 ), color }, //7 
		{ D3DXVECTOR3( k * radius * 0.503425, k * height * 0.0150551, k * radius * 0.861525 ), color }, //8 
		{ D3DXVECTOR3( k * radius * 0.504253, k * height * 0.0150551, k * radius * 0.862942 ), color }, //9 
		{ D3DXVECTOR3( k * radius * 0.265132, k * height * 0.0150551, k * radius * 0.962182 ), color }, //10 
		{ D3DXVECTOR3( k * radius * 0.265509, k * height * 0.0150551, k * radius * 0.963791 ), color }, //11 
		{ D3DXVECTOR3( k * radius * -2.89551e-008, k * height * 0.0150551, k * radius * 0.997866 ), color }, //12 
		{ D3DXVECTOR3( k * radius * -5.60428e-008, k * height * 0.0150551, k * radius * 0.999525 ), color }, //13 
		{ D3DXVECTOR3( k * radius * -0.265132, k * height * 0.0150551, k * radius * 0.962182 ), color }, //14 
		{ D3DXVECTOR3( k * radius * -0.265509, k * height * 0.0150551, k * radius * 0.96379 ), color }, //15 
		{ D3DXVECTOR3( k * radius * -0.503425, k * height * 0.0150551, k * radius * 0.861525 ), color }, //16 
		{ D3DXVECTOR3( k * radius * -0.504253, k * height * 0.0150551, k * radius * 0.862942 ), color }, //17 
		{ D3DXVECTOR3( k * radius * -0.705417, k * height * 0.0150551, k * radius * 0.705417 ), color }, //18 
		{ D3DXVECTOR3( k * radius * -0.706578, k * height * 0.0150551, k * radius * 0.706578 ), color }, //19 
		{ D3DXVECTOR3( k * radius * -0.861525, k * height * 0.0150551, k * radius * 0.503425 ), color }, //20 
		{ D3DXVECTOR3( k * radius * -0.862942, k * height * 0.0150551, k * radius * 0.504253 ), color }, //21 
		{ D3DXVECTOR3( k * radius * -0.962182, k * height * 0.0150551, k * radius * 0.265132 ), color }, //22 
		{ D3DXVECTOR3( k * radius * -0.963791, k * height * 0.0150551, k * radius * 0.265509 ), color }, //23 
		{ D3DXVECTOR3( k * radius * -0.997866, k * height * 0.0150551, k * radius * -7.89114e-008 ), color }, //24 
		{ D3DXVECTOR3( k * radius * -0.999525, k * height * 0.0150551, k * radius * -9.37092e-008 ), color }, //25 
		{ D3DXVECTOR3( k * radius * -0.962182, k * height * 0.0150551, k * radius * -0.265132 ), color }, //26 
		{ D3DXVECTOR3( k * radius * -0.96379, k * height * 0.0150551, k * radius * -0.265509 ), color }, //27 
		{ D3DXVECTOR3( k * radius * -0.861525, k * height * 0.0150551, k * radius * -0.503426 ), color }, //28 
		{ D3DXVECTOR3( k * radius * -0.862942, k * height * 0.0150551, k * radius * -0.504254 ), color }, //29 
		{ D3DXVECTOR3( k * radius * -0.705417, k * height * 0.0150551, k * radius * -0.705417 ), color }, //30 
		{ D3DXVECTOR3( k * radius * -0.706578, k * height * 0.0150551, k * radius * -0.706578 ), color }, //31 
		{ D3DXVECTOR3( k * radius * -0.503425, k * height * 0.0150551, k * radius * -0.861525 ), color }, //32 
		{ D3DXVECTOR3( k * radius * -0.504253, k * height * 0.0150551, k * radius * -0.862942 ), color }, //33 
		{ D3DXVECTOR3( k * radius * -0.265132, k * height * 0.0150551, k * radius * -0.962182 ), color }, //34 
		{ D3DXVECTOR3( k * radius * -0.265509, k * height * 0.0150551, k * radius * -0.963791 ), color }, //35 
		{ D3DXVECTOR3( k * radius * -7.93746e-009, k * height * 0.0150551, k * radius * -0.997866 ), color }, //36 
		{ D3DXVECTOR3( k * radius * 3.05268e-008, k * height * 0.0150551, k * radius * -0.999525 ), color }, //37 
		{ D3DXVECTOR3( k * radius * 0.265132, k * height * 0.0150551, k * radius * -0.962182 ), color }, //38 
		{ D3DXVECTOR3( k * radius * 0.265509, k * height * 0.0150551, k * radius * -0.96379 ), color }, //39 
		{ D3DXVECTOR3( k * radius * 0.503425, k * height * 0.0150551, k * radius * -0.861525 ), color }, //40 
		{ D3DXVECTOR3( k * radius * 0.504253, k * height * 0.0150551, k * radius * -0.862942 ), color }, //41 
		{ D3DXVECTOR3( k * radius * 0.705417, k * height * 0.0150551, k * radius * -0.705417 ), color }, //42 
		{ D3DXVECTOR3( k * radius * 0.706578, k * height * 0.0150551, k * radius * -0.706578 ), color }, //43 
		{ D3DXVECTOR3( k * radius * 0.861525, k * height * 0.0150551, k * radius * -0.503425 ), color }, //44 
		{ D3DXVECTOR3( k * radius * 0.862942, k * height * 0.0150551, k * radius * -0.504253 ), color }, //45 
		{ D3DXVECTOR3( k * radius * 0.962182, k * height * 0.0150551, k * radius * -0.265132 ), color }, //46 
		{ D3DXVECTOR3( k * radius * 0.963791, k * height * 0.0150551, k * radius * -0.265509 ), color }, //47 
	};

	int verticesCount = sizeof( vertices ) / sizeof( AGPrimitiveVertex );

	m_vertexBuffer = new AGBuffer< AGPrimitiveVertex >( vector< AGPrimitiveVertex >( vertices, vertices + verticesCount + 1 ), AGBufferType::Vertex );

	for( int i = 0; i < verticesCount; i++ )
	{
		m_tangents.push_back( vertices[ i ].pos ); 
	}

	color = yellow;

	AGPrimitiveVertex selectedVertices[] = 
	{
		{ D3DXVECTOR3( k * radius * 0.999525, k * height * 0.0150551, k * radius * 3.65244e-010 ), color }, //0 
		{ D3DXVECTOR3( k * radius * 0.962182, k * height * 0.0150551, k * radius * 0.265132 ), color }, //1 
		{ D3DXVECTOR3( k * radius * 0.96379, k * height * 0.0150551, k * radius * 0.265509 ), color }, //2 
		{ D3DXVECTOR3( k * radius * 0.997866, k * height * 0.0150551, k * radius * -1.22005e-009 ), color }, //3 
		{ D3DXVECTOR3( k * radius * 0.861525, k * height * 0.0150551, k * radius * 0.503425 ), color }, //4 
		{ D3DXVECTOR3( k * radius * 0.862942, k * height * 0.0150551, k * radius * 0.504253 ), color }, //5 
		{ D3DXVECTOR3( k * radius * 0.705417, k * height * 0.0150551, k * radius * 0.705417 ), color }, //6 
		{ D3DXVECTOR3( k * radius * 0.706578, k * height * 0.0150551, k * radius * 0.706578 ), color }, //7 
		{ D3DXVECTOR3( k * radius * 0.503425, k * height * 0.0150551, k * radius * 0.861525 ), color }, //8 
		{ D3DXVECTOR3( k * radius * 0.504253, k * height * 0.0150551, k * radius * 0.862942 ), color }, //9 
		{ D3DXVECTOR3( k * radius * 0.265132, k * height * 0.0150551, k * radius * 0.962182 ), color }, //10 
		{ D3DXVECTOR3( k * radius * 0.265509, k * height * 0.0150551, k * radius * 0.963791 ), color }, //11 
		{ D3DXVECTOR3( k * radius * -2.89551e-008, k * height * 0.0150551, k * radius * 0.997866 ), color }, //12 
		{ D3DXVECTOR3( k * radius * -5.60428e-008, k * height * 0.0150551, k * radius * 0.999525 ), color }, //13 
		{ D3DXVECTOR3( k * radius * -0.265132, k * height * 0.0150551, k * radius * 0.962182 ), color }, //14 
		{ D3DXVECTOR3( k * radius * -0.265509, k * height * 0.0150551, k * radius * 0.96379 ), color }, //15 
		{ D3DXVECTOR3( k * radius * -0.503425, k * height * 0.0150551, k * radius * 0.861525 ), color }, //16 
		{ D3DXVECTOR3( k * radius * -0.504253, k * height * 0.0150551, k * radius * 0.862942 ), color }, //17 
		{ D3DXVECTOR3( k * radius * -0.705417, k * height * 0.0150551, k * radius * 0.705417 ), color }, //18 
		{ D3DXVECTOR3( k * radius * -0.706578, k * height * 0.0150551, k * radius * 0.706578 ), color }, //19 
		{ D3DXVECTOR3( k * radius * -0.861525, k * height * 0.0150551, k * radius * 0.503425 ), color }, //20 
		{ D3DXVECTOR3( k * radius * -0.862942, k * height * 0.0150551, k * radius * 0.504253 ), color }, //21 
		{ D3DXVECTOR3( k * radius * -0.962182, k * height * 0.0150551, k * radius * 0.265132 ), color }, //22 
		{ D3DXVECTOR3( k * radius * -0.963791, k * height * 0.0150551, k * radius * 0.265509 ), color }, //23 
		{ D3DXVECTOR3( k * radius * -0.997866, k * height * 0.0150551, k * radius * -7.89114e-008 ), color }, //24 
		{ D3DXVECTOR3( k * radius * -0.999525, k * height * 0.0150551, k * radius * -9.37092e-008 ), color }, //25 
		{ D3DXVECTOR3( k * radius * -0.962182, k * height * 0.0150551, k * radius * -0.265132 ), color }, //26 
		{ D3DXVECTOR3( k * radius * -0.96379, k * height * 0.0150551, k * radius * -0.265509 ), color }, //27 
		{ D3DXVECTOR3( k * radius * -0.861525, k * height * 0.0150551, k * radius * -0.503426 ), color }, //28 
		{ D3DXVECTOR3( k * radius * -0.862942, k * height * 0.0150551, k * radius * -0.504254 ), color }, //29 
		{ D3DXVECTOR3( k * radius * -0.705417, k * height * 0.0150551, k * radius * -0.705417 ), color }, //30 
		{ D3DXVECTOR3( k * radius * -0.706578, k * height * 0.0150551, k * radius * -0.706578 ), color }, //31 
		{ D3DXVECTOR3( k * radius * -0.503425, k * height * 0.0150551, k * radius * -0.861525 ), color }, //32 
		{ D3DXVECTOR3( k * radius * -0.504253, k * height * 0.0150551, k * radius * -0.862942 ), color }, //33 
		{ D3DXVECTOR3( k * radius * -0.265132, k * height * 0.0150551, k * radius * -0.962182 ), color }, //34 
		{ D3DXVECTOR3( k * radius * -0.265509, k * height * 0.0150551, k * radius * -0.963791 ), color }, //35 
		{ D3DXVECTOR3( k * radius * -7.93746e-009, k * height * 0.0150551, k * radius * -0.997866 ), color }, //36 
		{ D3DXVECTOR3( k * radius * 3.05268e-008, k * height * 0.0150551, k * radius * -0.999525 ), color }, //37 
		{ D3DXVECTOR3( k * radius * 0.265132, k * height * 0.0150551, k * radius * -0.962182 ), color }, //38 
		{ D3DXVECTOR3( k * radius * 0.265509, k * height * 0.0150551, k * radius * -0.96379 ), color }, //39 
		{ D3DXVECTOR3( k * radius * 0.503425, k * height * 0.0150551, k * radius * -0.861525 ), color }, //40 
		{ D3DXVECTOR3( k * radius * 0.504253, k * height * 0.0150551, k * radius * -0.862942 ), color }, //41 
		{ D3DXVECTOR3( k * radius * 0.705417, k * height * 0.0150551, k * radius * -0.705417 ), color }, //42 
		{ D3DXVECTOR3( k * radius * 0.706578, k * height * 0.0150551, k * radius * -0.706578 ), color }, //43 
		{ D3DXVECTOR3( k * radius * 0.861525, k * height * 0.0150551, k * radius * -0.503425 ), color }, //44 
		{ D3DXVECTOR3( k * radius * 0.862942, k * height * 0.0150551, k * radius * -0.504253 ), color }, //45 
		{ D3DXVECTOR3( k * radius * 0.962182, k * height * 0.0150551, k * radius * -0.265132 ), color }, //46 
		{ D3DXVECTOR3( k * radius * 0.963791, k * height * 0.0150551, k * radius * -0.265509 ), color }, //47 
	};

	AGPrimitiveVertex boundingVertices[] = 
	{
		{ D3DXVECTOR3( k * radius * 1.01514, k * height * 0.015, k * radius * 6.6136e-010 ), color }, //0 
		{ D3DXVECTOR3( k * radius * 0.949646, k * height * 0.015, k * radius * 0.261678 ), color }, //1 
		{ D3DXVECTOR3( k * radius * 0.978843, k * height * 0.015, k * radius * 0.269655 ), color }, //2 
		{ D3DXVECTOR3( k * radius * 0.984865, k * height * 0.015, k * radius * -1.9727e-009 ), color }, //3 
		{ D3DXVECTOR3( k * radius * 0.949646, k * height * -0.015, k * radius * 0.261678 ), color }, //4 
		{ D3DXVECTOR3( k * radius * 0.984865, k * height * -0.015, k * radius * -6.6136e-010 ), color }, //5 
		{ D3DXVECTOR3( k * radius * 0.978843, k * height * -0.015, k * radius * 0.269655 ), color }, //6 
		{ D3DXVECTOR3( k * radius * 1.01514, k * height * -0.015, k * radius * 1.9727e-009 ), color }, //7 
		{ D3DXVECTOR3( k * radius * 0.8503, k * height * 0.015, k * radius * 0.496866 ), color }, //8 
		{ D3DXVECTOR3( k * radius * 0.87642, k * height * 0.015, k * radius * 0.512129 ), color }, //9 
		{ D3DXVECTOR3( k * radius * 0.8503, k * height * -0.015, k * radius * 0.496866 ), color }, //10 
		{ D3DXVECTOR3( k * radius * 0.87642, k * height * -0.015, k * radius * 0.512129 ), color }, //11 
		{ D3DXVECTOR3( k * radius * 0.696226, k * height * 0.015, k * radius * 0.696226 ), color }, //12 
		{ D3DXVECTOR3( k * radius * 0.717613, k * height * 0.015, k * radius * 0.717613 ), color }, //13 
		{ D3DXVECTOR3( k * radius * 0.696226, k * height * -0.015, k * radius * 0.696226 ), color }, //14 
		{ D3DXVECTOR3( k * radius * 0.717613, k * height * -0.015, k * radius * 0.717613 ), color }, //15 
		{ D3DXVECTOR3( k * radius * 0.496866, k * height * 0.015, k * radius * 0.8503 ), color }, //16 
		{ D3DXVECTOR3( k * radius * 0.512129, k * height * 0.015, k * radius * 0.87642 ), color }, //17 
		{ D3DXVECTOR3( k * radius * 0.496866, k * height * -0.015, k * radius * 0.8503 ), color }, //18 
		{ D3DXVECTOR3( k * radius * 0.512129, k * height * -0.015, k * radius * 0.87642 ), color }, //19 
		{ D3DXVECTOR3( k * radius * 0.261677, k * height * 0.015, k * radius * 0.949646 ), color }, //20 
		{ D3DXVECTOR3( k * radius * 0.269655, k * height * 0.015, k * radius * 0.978843 ), color }, //21 
		{ D3DXVECTOR3( k * radius * 0.261677, k * height * -0.015, k * radius * 0.949646 ), color }, //22 
		{ D3DXVECTOR3( k * radius * 0.269655, k * height * -0.015, k * radius * 0.978843 ), color }, //23 
		{ D3DXVECTOR3( k * radius * -2.89799e-008, k * height * 0.015, k * radius * 0.984865 ), color }, //24 
		{ D3DXVECTOR3( k * radius * -5.71316e-008, k * height * 0.015, k * radius * 1.01514 ), color }, //25 
		{ D3DXVECTOR3( k * radius * -3.02912e-008, k * height * -0.015, k * radius * 0.984865 ), color }, //26 
		{ D3DXVECTOR3( k * radius * -5.84429e-008, k * height * -0.015, k * radius * 1.01514 ), color }, //27 
		{ D3DXVECTOR3( k * radius * -0.261678, k * height * 0.015, k * radius * 0.949646 ), color }, //28 
		{ D3DXVECTOR3( k * radius * -0.269656, k * height * 0.015, k * radius * 0.978843 ), color }, //29 
		{ D3DXVECTOR3( k * radius * -0.261678, k * height * -0.015, k * radius * 0.949646 ), color }, //30 
		{ D3DXVECTOR3( k * radius * -0.269656, k * height * -0.015, k * radius * 0.978843 ), color }, //31 
		{ D3DXVECTOR3( k * radius * -0.496866, k * height * 0.015, k * radius * 0.8503 ), color }, //32 
		{ D3DXVECTOR3( k * radius * -0.512129, k * height * 0.015, k * radius * 0.87642 ), color }, //33 
		{ D3DXVECTOR3( k * radius * -0.496866, k * height * -0.015, k * radius * 0.8503 ), color }, //34 
		{ D3DXVECTOR3( k * radius * -0.512129, k * height * -0.015, k * radius * 0.87642 ), color }, //35 
		{ D3DXVECTOR3( k * radius * -0.696227, k * height * 0.015, k * radius * 0.696226 ), color }, //36 
		{ D3DXVECTOR3( k * radius * -0.717613, k * height * 0.015, k * radius * 0.717613 ), color }, //37 
		{ D3DXVECTOR3( k * radius * -0.696227, k * height * -0.015, k * radius * 0.696226 ), color }, //38 
		{ D3DXVECTOR3( k * radius * -0.717613, k * height * -0.015, k * radius * 0.717613 ), color }, //39 
		{ D3DXVECTOR3( k * radius * -0.8503, k * height * 0.015, k * radius * 0.496866 ), color }, //40 
		{ D3DXVECTOR3( k * radius * -0.87642, k * height * 0.015, k * radius * 0.512129 ), color }, //41 
		{ D3DXVECTOR3( k * radius * -0.8503, k * height * -0.015, k * radius * 0.496866 ), color }, //42 
		{ D3DXVECTOR3( k * radius * -0.87642, k * height * -0.015, k * radius * 0.512129 ), color }, //43 
		{ D3DXVECTOR3( k * radius * -0.949646, k * height * 0.015, k * radius * 0.261677 ), color }, //44 
		{ D3DXVECTOR3( k * radius * -0.978843, k * height * 0.015, k * radius * 0.269655 ), color }, //45 
		{ D3DXVECTOR3( k * radius * -0.949646, k * height * -0.015, k * radius * 0.261677 ), color }, //46 
		{ D3DXVECTOR3( k * radius * -0.978843, k * height * -0.015, k * radius * 0.269655 ), color }, //47 
		{ D3DXVECTOR3( k * radius * -0.984865, k * height * 0.015, k * radius * -7.86518e-008 ), color }, //48 
		{ D3DXVECTOR3( k * radius * -1.01514, k * height * 0.015, k * radius * -9.48824e-008 ), color }, //49 
		{ D3DXVECTOR3( k * radius * -0.984865, k * height * -0.015, k * radius * -7.99632e-008 ), color }, //50 
		{ D3DXVECTOR3( k * radius * -1.01514, k * height * -0.015, k * radius * -9.61937e-008 ), color }, //51 
		{ D3DXVECTOR3( k * radius * -0.949646, k * height * 0.015, k * radius * -0.261678 ), color }, //52 
		{ D3DXVECTOR3( k * radius * -0.978843, k * height * 0.015, k * radius * -0.269656 ), color }, //53 
		{ D3DXVECTOR3( k * radius * -0.949646, k * height * -0.015, k * radius * -0.261678 ), color }, //54 
		{ D3DXVECTOR3( k * radius * -0.978843, k * height * -0.015, k * radius * -0.269656 ), color }, //55 
		{ D3DXVECTOR3( k * radius * -0.8503, k * height * 0.015, k * radius * -0.496866 ), color }, //56 
		{ D3DXVECTOR3( k * radius * -0.876419, k * height * 0.015, k * radius * -0.512129 ), color }, //57 
		{ D3DXVECTOR3( k * radius * -0.8503, k * height * -0.015, k * radius * -0.496866 ), color }, //58 
		{ D3DXVECTOR3( k * radius * -0.876419, k * height * -0.015, k * radius * -0.512129 ), color }, //59 
		{ D3DXVECTOR3( k * radius * -0.696226, k * height * 0.015, k * radius * -0.696227 ), color }, //60 
		{ D3DXVECTOR3( k * radius * -0.717613, k * height * 0.015, k * radius * -0.717613 ), color }, //61 
		{ D3DXVECTOR3( k * radius * -0.696226, k * height * -0.015, k * radius * -0.696227 ), color }, //62 
		{ D3DXVECTOR3( k * radius * -0.717613, k * height * -0.015, k * radius * -0.717613 ), color }, //63 
		{ D3DXVECTOR3( k * radius * -0.496866, k * height * 0.015, k * radius * -0.8503 ), color }, //64 
		{ D3DXVECTOR3( k * radius * -0.512129, k * height * 0.015, k * radius * -0.87642 ), color }, //65 
		{ D3DXVECTOR3( k * radius * -0.496866, k * height * -0.015, k * radius * -0.8503 ), color }, //66 
		{ D3DXVECTOR3( k * radius * -0.512129, k * height * -0.015, k * radius * -0.87642 ), color }, //67 
		{ D3DXVECTOR3( k * radius * -0.261677, k * height * 0.015, k * radius * -0.949646 ), color }, //68 
		{ D3DXVECTOR3( k * radius * -0.269655, k * height * 0.015, k * radius * -0.978843 ), color }, //69 
		{ D3DXVECTOR3( k * radius * -0.261677, k * height * -0.015, k * radius * -0.949646 ), color }, //70 
		{ D3DXVECTOR3( k * radius * -0.269655, k * height * -0.015, k * radius * -0.978843 ), color }, //71 
		{ D3DXVECTOR3( k * radius * -8.25166e-009, k * height * 0.015, k * radius * -0.984865 ), color }, //72 
		{ D3DXVECTOR3( k * radius * 3.07901e-008, k * height * 0.015, k * radius * -1.01514 ), color }, //73 
		{ D3DXVECTOR3( k * radius * -6.94032e-009, k * height * -0.015, k * radius * -0.984865 ), color }, //74 
		{ D3DXVECTOR3( k * radius * 3.21014e-008, k * height * -0.015, k * radius * -1.01514 ), color }, //75 
		{ D3DXVECTOR3( k * radius * 0.261678, k * height * 0.015, k * radius * -0.949646 ), color }, //76 
		{ D3DXVECTOR3( k * radius * 0.269655, k * height * 0.015, k * radius * -0.978843 ), color }, //77 
		{ D3DXVECTOR3( k * radius * 0.261678, k * height * -0.015, k * radius * -0.949646 ), color }, //78 
		{ D3DXVECTOR3( k * radius * 0.269655, k * height * -0.015, k * radius * -0.978843 ), color }, //79 
		{ D3DXVECTOR3( k * radius * 0.496866, k * height * 0.015, k * radius * -0.8503 ), color }, //80 
		{ D3DXVECTOR3( k * radius * 0.512129, k * height * 0.015, k * radius * -0.87642 ), color }, //81 
		{ D3DXVECTOR3( k * radius * 0.496866, k * height * -0.015, k * radius * -0.8503 ), color }, //82 
		{ D3DXVECTOR3( k * radius * 0.512129, k * height * -0.015, k * radius * -0.87642 ), color }, //83 
		{ D3DXVECTOR3( k * radius * 0.696226, k * height * 0.015, k * radius * -0.696226 ), color }, //84 
		{ D3DXVECTOR3( k * radius * 0.717613, k * height * 0.015, k * radius * -0.717613 ), color }, //85 
		{ D3DXVECTOR3( k * radius * 0.696226, k * height * -0.015, k * radius * -0.696226 ), color }, //86 
		{ D3DXVECTOR3( k * radius * 0.717613, k * height * -0.015, k * radius * -0.717613 ), color }, //87 
		{ D3DXVECTOR3( k * radius * 0.8503, k * height * 0.015, k * radius * -0.496866 ), color }, //88 
		{ D3DXVECTOR3( k * radius * 0.87642, k * height * 0.015, k * radius * -0.512129 ), color }, //89 
		{ D3DXVECTOR3( k * radius * 0.8503, k * height * -0.015, k * radius * -0.496866 ), color }, //90 
		{ D3DXVECTOR3( k * radius * 0.87642, k * height * -0.015, k * radius * -0.512129 ), color }, //91 
		{ D3DXVECTOR3( k * radius * 0.949646, k * height * 0.015, k * radius * -0.261677 ), color }, //92 
		{ D3DXVECTOR3( k * radius * 0.978843, k * height * 0.015, k * radius * -0.269655 ), color }, //93 
		{ D3DXVECTOR3( k * radius * 0.949646, k * height * -0.015, k * radius * -0.261677 ), color }, //94 
		{ D3DXVECTOR3( k * radius * 0.978843, k * height * -0.015, k * radius * -0.269655 ), color }, //95 
	};

	verticesCount = sizeof( boundingVertices ) / sizeof( AGPrimitiveVertex );

	for( int i = 0 ; i < verticesCount; i++ )
	{
		m_vertices.push_back( boundingVertices[ i ] );
	}

	int selectedVerticesCount = sizeof( selectedVertices ) / sizeof( AGPrimitiveVertex );

	m_additionalVB = new AGBuffer< AGPrimitiveVertex >( 
		vector< AGPrimitiveVertex >( selectedVertices, selectedVertices + selectedVerticesCount + 1 ), AGBufferType::Vertex );

	int indices[] = 
	{
		0, 
		1, 2, 1, 0, 3, 
		2, 4, 5, 4, 2, 
		1, 5, 6, 7, 6, 
		5, 4, 7, 8, 9, 
		8, 7, 6, 9, 10, 
		11, 10, 9, 8, 11, 
		12, 13, 12, 11, 10, 
		13, 14, 15, 14, 13, 
		12, 15, 16, 17, 16, 
		15, 14, 17, 18, 19, 
		18, 17, 16, 19, 20, 
		21, 20, 19, 18, 21, 
		22, 23, 22, 21, 20, 
		23, 24, 25, 24, 23, 
		22, 25, 26, 27, 26, 
		25, 24, 27, 28, 29, 
		28, 27, 26, 29, 30, 
		31, 30, 29, 28, 31, 
		32, 33, 32, 31, 30, 
		33, 34, 35, 34, 33, 
		32, 35, 36, 37, 36, 
		35, 34, 37, 38, 39, 
		38, 37, 36, 39, 40, 
		41, 40, 39, 38, 41, 
		42, 43, 42, 41, 40, 
		43, 44, 45, 44, 43, 
		42, 45, 46, 47, 46, 
		45, 44, 47, 3, 0, 
		3, 47, 46, 
	};

	int boundIndices[] = 
	{
		0, 
		1, 2, 1, 0, 3, 
		3, 4, 1, 4, 3, 
		5, 5, 6, 4, 6, 
		5, 7, 7, 2, 6, 
		2, 7, 0, 2, 8, 
		9, 8, 2, 1, 1, 
		10, 8, 10, 1, 4, 
		4, 11, 10, 11, 4, 
		6, 6, 9, 11, 9, 
		6, 2, 9, 12, 13, 
		12, 9, 8, 8, 14, 
		12, 14, 8, 10, 10, 
		15, 14, 15, 10, 11, 
		11, 13, 15, 13, 11, 
		9, 13, 16, 17, 16, 
		13, 12, 12, 18, 16, 
		18, 12, 14, 14, 19, 
		18, 19, 14, 15, 15, 
		17, 19, 17, 15, 13, 
		17, 20, 21, 20, 17, 
		16, 16, 22, 20, 22, 
		16, 18, 18, 23, 22, 
		23, 18, 19, 19, 21, 
		23, 21, 19, 17, 21, 
		24, 25, 24, 21, 20, 
		20, 26, 24, 26, 20, 
		22, 22, 27, 26, 27, 
		22, 23, 23, 25, 27, 
		25, 23, 21, 25, 28, 
		29, 28, 25, 24, 24, 
		30, 28, 30, 24, 26, 
		26, 31, 30, 31, 26, 
		27, 27, 29, 31, 29, 
		27, 25, 29, 32, 33, 
		32, 29, 28, 28, 34, 
		32, 34, 28, 30, 30, 
		35, 34, 35, 30, 31, 
		31, 33, 35, 33, 31, 
		29, 33, 36, 37, 36, 
		33, 32, 32, 38, 36, 
		38, 32, 34, 34, 39, 
		38, 39, 34, 35, 35, 
		37, 39, 37, 35, 33, 
		37, 40, 41, 40, 37, 
		36, 36, 42, 40, 42, 
		36, 38, 38, 43, 42, 
		43, 38, 39, 39, 41, 
		43, 41, 39, 37, 41, 
		44, 45, 44, 41, 40, 
		40, 46, 44, 46, 40, 
		42, 42, 47, 46, 47, 
		42, 43, 43, 45, 47, 
		45, 43, 41, 45, 48, 
		49, 48, 45, 44, 44, 
		50, 48, 50, 44, 46, 
		46, 51, 50, 51, 46, 
		47, 47, 49, 51, 49, 
		47, 45, 49, 52, 53, 
		52, 49, 48, 48, 54, 
		52, 54, 48, 50, 50, 
		55, 54, 55, 50, 51, 
		51, 53, 55, 53, 51, 
		49, 53, 56, 57, 56, 
		53, 52, 52, 58, 56, 
		58, 52, 54, 54, 59, 
		58, 59, 54, 55, 55, 
		57, 59, 57, 55, 53, 
		57, 60, 61, 60, 57, 
		56, 56, 62, 60, 62, 
		56, 58, 58, 63, 62, 
		63, 58, 59, 59, 61, 
		63, 61, 59, 57, 61, 
		64, 65, 64, 61, 60, 
		60, 66, 64, 66, 60, 
		62, 62, 67, 66, 67, 
		62, 63, 63, 65, 67, 
		65, 63, 61, 65, 68, 
		69, 68, 65, 64, 64, 
		70, 68, 70, 64, 66, 
		66, 71, 70, 71, 66, 
		67, 67, 69, 71, 69, 
		67, 65, 69, 72, 73, 
		72, 69, 68, 68, 74, 
		72, 74, 68, 70, 70, 
		75, 74, 75, 70, 71, 
		71, 73, 75, 73, 71, 
		69, 73, 76, 77, 76, 
		73, 72, 72, 78, 76, 
		78, 72, 74, 74, 79, 
		78, 79, 74, 75, 75, 
		77, 79, 77, 75, 73, 
		77, 80, 81, 80, 77, 
		76, 76, 82, 80, 82, 
		76, 78, 78, 83, 82, 
		83, 78, 79, 79, 81, 
		83, 81, 79, 77, 81, 
		84, 85, 84, 81, 80, 
		80, 86, 84, 86, 80, 
		82, 82, 87, 86, 87, 
		82, 83, 83, 85, 87, 
		85, 83, 81, 85, 88, 
		89, 88, 85, 84, 84, 
		90, 88, 90, 84, 86, 
		86, 91, 90, 91, 86, 
		87, 87, 89, 91, 89, 
		87, 85, 89, 92, 93, 
		92, 89, 88, 88, 94, 
		92, 94, 88, 90, 90, 
		95, 94, 95, 90, 91, 
		91, 93, 95, 93, 91, 
		89, 93, 3, 0, 3, 
		93, 92, 92, 5, 3, 
		5, 92, 94, 94, 7, 
		5, 7, 94, 95, 95, 
		0, 7, 0, 95, 93, 
	};

	m_nIndices = sizeof( indices ) / sizeof( indices[ 0 ] );
	m_nBoundIndices = sizeof( boundIndices ) / sizeof( indices[ 0 ] );

	for( int i = 0; i < m_nBoundIndices; i++ )
	{
		m_indices.push_back( boundIndices[ i ] );
	}

	m_indexBuffer = new AGBuffer< int >( vector< int >( indices, indices + m_nIndices + 1 ), AGBufferType::Index ); 
}

AGCircle::~AGCircle()
{

}

void AGCircle::draw( AGSurface* surface )
{
	AGCamera* camera = surface->getCamera(); 
	ID3D10Device* device = surface->getDevice(); 

	D3DXVECTOR3 camEye = camera->getEye(); 
	D3DXVECTOR3 dir = camEye - m_beginPos; 
	D3DXVec3Normalize( &dir, &dir );
	dir = camEye - dir * 1.0f; 
	D3DXVECTOR3 pos = dir; 

	setLocalPos( pos.x, pos.y, pos.z );

	D3DXMATRIX worldTextMat = getLocalMatrix();

	if( m_axis == X_AXIS )
	{
		setLocalAngle( 0.0f, 0.0f, D3DXToRadian( -90.0f ) );	
	}
	else if( m_axis == Z_AXIS )
	{
		setLocalAngle( D3DXToRadian( 90.0f ), 0.0f, 0.0f );	
	} 

	AGEStateManager::CoordSystem system = AGEStateManager::getInstance().getCoordSystem(); 

	m_shader->setWorldMatrix( system == AGEStateManager::World ? getLocalMatrix() : getResultMatrix() );

	AGInputLayout* inputLayout = AGGraphics::getInstance().getInputLayout( device );

	if( !inputLayout )
	{
		AGError() << "Cant get input layout for device " << AGCurFileFunctionLineSnippet; 
		return; 
	}

	device->IASetInputLayout( inputLayout->colorVertexInputLayout );

	ID3D10Buffer* ibo = m_indexBuffer->applyTo( device );
	
	if( !ibo )
	{
		AGError() << "Cant apply index buffer to device " << AGCurFileFunctionLineSnippet; 
		return; 
	}

	device->IASetIndexBuffer( ibo, DXGI_FORMAT_R32_UINT, 0 );

	UINT stride = sizeof( AGPrimitiveVertex );
	UINT offset = 0; 
	
	ID3D10Buffer* vbo;

	if( m_isSelected )
	{
		vbo = m_additionalVB->applyTo( device ); 
	}
	else 
	{
		vbo = m_vertexBuffer->applyTo( device );
	}
	
	if( !vbo )
	{
		AGError() << "Cant apply vertex buffer to device " << AGCurFileFunctionLineSnippet; 
		return; 
	}

	device->IASetVertexBuffers( 0, 1, &vbo, &stride, &offset );

	m_shader->applySurface( surface );

	while( m_shader->applyNextPass() )
	{
		device->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_LINELIST );
		device->DrawIndexed( m_nIndices, 0, 0 );
	}

}

float AGCircle::intersect(D3DXVECTOR3 rayOrigin, D3DXVECTOR3 rayDir)
{
	float retDist = -1.0f;
	int nIndices = m_indices.size() - 2;  

	D3DXVECTOR3 vertex1;
	D3DXVECTOR3 vertex2;
	D3DXVECTOR3 vertex3;

	for( int i = 0; i < nIndices; i++ )
	{
		D3DXVECTOR3 v1 = m_vertices[ m_indices[ i ] ].pos;
		D3DXVECTOR3 v2 = m_vertices[ m_indices[ i + 1 ] ].pos;
		D3DXVECTOR3 v3 = m_vertices[ m_indices[ i + 2 ] ].pos;

		float dist, u, v; 

		bool res = D3DXIntersectTri( &v1, &v2, &v3, &rayOrigin, &rayDir, &u, &v, &dist );
		if( res )
		{
			if( retDist < 0 )
			{
				retDist = dist; 
			}
			else 
			{
				retDist = min( retDist, dist );	
			}
			vertex1 = v1;
			vertex2 = v2;
			vertex3 = v3;
		}
	}

	if( retDist > 0.0f )
	{
		D3DXVECTOR3 midleVec = ( vertex1 + vertex2 + vertex3 ) / 3.0f;
		D3DXVECTOR3 closestVec = m_tangents[ 0 ] - midleVec; 
		float closestDist = D3DXVec3LengthSq( &closestVec );
		m_tangent = m_tangents[ 0 ];

		for( int i = 0; i < m_tangents.size(); i++ )
		{
			D3DXVECTOR3 vec = m_tangents[ i ] - midleVec; 
			float dist = D3DXVec3LengthSq( &vec );

			if( dist < closestDist )
			{
				closestVec = vec;
				m_tangent = m_tangents[ i ];
				closestDist = dist; 
			}
		}
	}

	return retDist; 
}

D3DXVECTOR3 AGCircle::getAxis()
{
	return D3DXVECTOR3( m_axis == X_AXIS, m_axis == Y_AXIS, m_axis == Z_AXIS );
}

D3DXVECTOR3 AGCircle::getTangent()
{
	return m_tangent;
}


