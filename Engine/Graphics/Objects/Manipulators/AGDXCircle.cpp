#include "AGDXCircle.h"

#include "Managers/AGLogger.h"
#include "Graphics/Interfaces/AGSurface.h"
#include "Graphics/Objects/AGDXCamera.h"

AGDXCircle::AGDXCircle(ID3D10Device* device, CircleAxis axis) : AGDXGizmo( device )
{
	m_axis = axis; 
	m_isSelected = false; 

	D3DXVECTOR4 color( (axis == X_AXIS) * 0.798431372, (axis == Y_AXIS) * 0.6117647058, (axis == Z_AXIS) * 0.76470588233, 1.0f );
	D3DXVECTOR4 yellow( 1.0f, 1.0f, 0.0f, 1.0f );
	float k = 0.1f;
	float height = 1.0f;
	float radius = 1.0f;
	float d = 0.025f;

	AGColorVertex vertices[] = 
	{
		{ D3DXVECTOR3( k * radius * 0.915583, k * height * 0.05, k * radius * 0.252489 ), color },       //0 
		{ D3DXVECTOR3( k * radius * 1.05045, k * height * 0.05, k * radius * 0.000118735 ), color },     //1 
		{ D3DXVECTOR3( k * radius * 0.949549, k * height * 0.05, k * radius * 0.000118726 ), color },    //2 
		{ D3DXVECTOR3( k * radius * 1.01291, k * height * 0.05, k * radius * 0.279082 ), color },        //3 
		{ D3DXVECTOR3( k * radius * 0.915583, k * height * -0.05, k * radius * 0.252489 ), color },      //4 
		{ D3DXVECTOR3( k * radius * 0.949549, k * height * -0.05, k * radius * 0.00011873 ), color },    //5 
		{ D3DXVECTOR3( k * radius * 1.01291, k * height * -0.05, k * radius * 0.279082 ), color },       //6 
		{ D3DXVECTOR3( k * radius * 1.05045, k * height * -0.05, k * radius * 0.000118739 ), color },    //7 
		{ D3DXVECTOR3( k * radius * 0.819827, k * height * 0.05, k * radius * 0.479179 ), color },       //8 
		{ D3DXVECTOR3( k * radius * 0.906893, k * height * 0.05, k * radius * 0.530054 ), color },       //9 
		{ D3DXVECTOR3( k * radius * 0.819827, k * height * -0.05, k * radius * 0.479179 ), color },      //10 
		{ D3DXVECTOR3( k * radius * 0.906893, k * height * -0.05, k * radius * 0.530054 ), color },      //11 
		{ D3DXVECTOR3( k * radius * 0.671275, k * height * 0.05, k * radius * 0.671394 ), color },       //12 
		{ D3DXVECTOR3( k * radius * 0.742564, k * height * 0.05, k * radius * 0.742683 ), color },       //13 
		{ D3DXVECTOR3( k * radius * 0.671275, k * height * -0.05, k * radius * 0.671394 ), color },      //14 
		{ D3DXVECTOR3( k * radius * 0.742564, k * height * -0.05, k * radius * 0.742683 ), color },      //15 
		{ D3DXVECTOR3( k * radius * 0.47906, k * height * 0.05, k * radius * 0.819946 ), color },        //16 
		{ D3DXVECTOR3( k * radius * 0.529935, k * height * 0.05, k * radius * 0.907011 ), color },       //17 
		{ D3DXVECTOR3( k * radius * 0.47906, k * height * -0.05, k * radius * 0.819946 ), color },       //18 
		{ D3DXVECTOR3( k * radius * 0.529935, k * height * -0.05, k * radius * 0.907011 ), color },      //19 
		{ D3DXVECTOR3( k * radius * 0.25237, k * height * 0.05, k * radius * 0.915702 ), color },        //20 
		{ D3DXVECTOR3( k * radius * 0.278963, k * height * 0.05, k * radius * 1.01302 ), color },        //21 
		{ D3DXVECTOR3( k * radius * 0.25237, k * height * -0.05, k * radius * 0.915702 ), color },       //22 
		{ D3DXVECTOR3( k * radius * 0.278963, k * height * -0.05, k * radius * 1.01302 ), color },       //23 
		{ D3DXVECTOR3( k * radius * 5.39365e-009, k * height * 0.05, k * radius * 0.949668 ), color },   //24 
		{ D3DXVECTOR3( k * radius * -8.84453e-008, k * height * 0.05, k * radius * 1.05057 ), color },   //25 
		{ D3DXVECTOR3( k * radius * 1.02251e-009, k * height * -0.05, k * radius * 0.949668 ), color },  //26 
		{ D3DXVECTOR3( k * radius * -9.28164e-008, k * height * -0.05, k * radius * 1.05057 ), color },  //27 
		{ D3DXVECTOR3( k * radius * -0.25237, k * height * 0.05, k * radius * 0.915702 ), color },       //28 
		{ D3DXVECTOR3( k * radius * -0.278963, k * height * 0.05, k * radius * 1.01302 ), color },       //29 
		{ D3DXVECTOR3( k * radius * -0.25237, k * height * -0.05, k * radius * 0.915702 ), color },      //30 
		{ D3DXVECTOR3( k * radius * -0.278963, k * height * -0.05, k * radius * 1.01302 ), color },      //31 
		{ D3DXVECTOR3( k * radius * -0.47906, k * height * 0.05, k * radius * 0.819946 ), color },       //32 
		{ D3DXVECTOR3( k * radius * -0.529935, k * height * 0.05, k * radius * 0.907011 ), color },      //33 
		{ D3DXVECTOR3( k * radius * -0.47906, k * height * -0.05, k * radius * 0.819946 ), color },      //34 
		{ D3DXVECTOR3( k * radius * -0.529935, k * height * -0.05, k * radius * 0.907011 ), color },     //35 
		{ D3DXVECTOR3( k * radius * -0.671275, k * height * 0.05, k * radius * 0.671394 ), color },      //36 
		{ D3DXVECTOR3( k * radius * -0.742564, k * height * 0.05, k * radius * 0.742683 ), color },      //37 
		{ D3DXVECTOR3( k * radius * -0.671275, k * height * -0.05, k * radius * 0.671394 ), color },     //38 
		{ D3DXVECTOR3( k * radius * -0.742564, k * height * -0.05, k * radius * 0.742683 ), color },     //39 
		{ D3DXVECTOR3( k * radius * -0.819827, k * height * 0.05, k * radius * 0.479179 ), color },      //40 
		{ D3DXVECTOR3( k * radius * -0.906893, k * height * 0.05, k * radius * 0.530054 ), color },      //41 
		{ D3DXVECTOR3( k * radius * -0.819827, k * height * -0.05, k * radius * 0.479179 ), color },     //42 
		{ D3DXVECTOR3( k * radius * -0.906893, k * height * -0.05, k * radius * 0.530054 ), color },     //43 
		{ D3DXVECTOR3( k * radius * -0.915583, k * height * 0.05, k * radius * 0.252489 ), color },      //44 
		{ D3DXVECTOR3( k * radius * -1.01291, k * height * 0.05, k * radius * 0.279082 ), color },       //45 
		{ D3DXVECTOR3( k * radius * -0.915583, k * height * -0.05, k * radius * 0.252489 ), color },     //46 
		{ D3DXVECTOR3( k * radius * -1.01291, k * height * -0.05, k * radius * 0.279081 ), color },      //47 
		{ D3DXVECTOR3( k * radius * -0.949549, k * height * 0.05, k * radius * 0.000118674 ), color },   //48 
		{ D3DXVECTOR3( k * radius * -1.05045, k * height * 0.05, k * radius * 0.00011862 ), color },     //49 
		{ D3DXVECTOR3( k * radius * -0.949549, k * height * -0.05, k * radius * 0.00011867 ), color },   //50 
		{ D3DXVECTOR3( k * radius * -1.05045, k * height * -0.05, k * radius * 0.000118616 ), color },   //51 
		{ D3DXVECTOR3( k * radius * -0.915583, k * height * 0.05, k * radius * -0.252251 ), color },     //52 
		{ D3DXVECTOR3( k * radius * -1.01291, k * height * 0.05, k * radius * -0.278844 ), color },      //53 
		{ D3DXVECTOR3( k * radius * -0.915583, k * height * -0.05, k * radius * -0.252251 ), color },    //54 
		{ D3DXVECTOR3( k * radius * -1.01291, k * height * -0.05, k * radius * -0.278844 ), color },     //55 
		{ D3DXVECTOR3( k * radius * -0.819827, k * height * 0.05, k * radius * -0.478941 ), color },     //56 
		{ D3DXVECTOR3( k * radius * -0.906892, k * height * 0.05, k * radius * -0.529816 ), color },     //57 
		{ D3DXVECTOR3( k * radius * -0.819827, k * height * -0.05, k * radius * -0.478941 ), color },    //58 
		{ D3DXVECTOR3( k * radius * -0.906892, k * height * -0.05, k * radius * -0.529816 ), color },    //59 
		{ D3DXVECTOR3( k * radius * -0.671275, k * height * 0.05, k * radius * -0.671157 ), color },     //60 
		{ D3DXVECTOR3( k * radius * -0.742564, k * height * 0.05, k * radius * -0.742446 ), color },     //61 
		{ D3DXVECTOR3( k * radius * -0.671275, k * height * -0.05, k * radius * -0.671157 ), color },    //62 
		{ D3DXVECTOR3( k * radius * -0.742564, k * height * -0.05, k * radius * -0.742446 ), color },    //63 
		{ D3DXVECTOR3( k * radius * -0.47906, k * height * 0.05, k * radius * -0.819708 ), color },      //64 
		{ D3DXVECTOR3( k * radius * -0.529935, k * height * 0.05, k * radius * -0.906774 ), color },     //65 
		{ D3DXVECTOR3( k * radius * -0.47906, k * height * -0.05, k * radius * -0.819708 ), color },     //66 
		{ D3DXVECTOR3( k * radius * -0.529935, k * height * -0.05, k * radius * -0.906774 ), color },    //67 
		{ D3DXVECTOR3( k * radius * -0.25237, k * height * 0.05, k * radius * -0.915465 ), color },      //68 
		{ D3DXVECTOR3( k * radius * -0.278963, k * height * 0.05, k * radius * -1.01279 ), color },      //69 
		{ D3DXVECTOR3( k * radius * -0.25237, k * height * -0.05, k * radius * -0.915465 ), color },     //70 
		{ D3DXVECTOR3( k * radius * -0.278963, k * height * -0.05, k * radius * -1.01279 ), color },     //71 
		{ D3DXVECTOR3( k * radius * -5.53303e-008, k * height * 0.05, k * radius * -0.94943 ), color },  //72 
		{ D3DXVECTOR3( k * radius * 7.48089e-008, k * height * 0.05, k * radius * -1.05033 ), color },   //73 
		{ D3DXVECTOR3( k * radius * -5.09591e-008, k * height * -0.05, k * radius * -0.94943 ), color }, //74 
		{ D3DXVECTOR3( k * radius * 7.918e-008, k * height * -0.05, k * radius * -1.05033 ), color },    //75 
		{ D3DXVECTOR3( k * radius * 0.25237, k * height * 0.05, k * radius * -0.915464 ), color },       //76 
		{ D3DXVECTOR3( k * radius * 0.278963, k * height * 0.05, k * radius * -1.01279 ), color },       //77 
		{ D3DXVECTOR3( k * radius * 0.25237, k * height * -0.05, k * radius * -0.915464 ), color },      //78 
		{ D3DXVECTOR3( k * radius * 0.278963, k * height * -0.05, k * radius * -1.01279 ), color },      //79 
		{ D3DXVECTOR3( k * radius * 0.47906, k * height * 0.05, k * radius * -0.819708 ), color },       //80 
		{ D3DXVECTOR3( k * radius * 0.529935, k * height * 0.05, k * radius * -0.906774 ), color },      //81 
		{ D3DXVECTOR3( k * radius * 0.47906, k * height * -0.05, k * radius * -0.819708 ), color },      //82 
		{ D3DXVECTOR3( k * radius * 0.529935, k * height * -0.05, k * radius * -0.906774 ), color },     //83 
		{ D3DXVECTOR3( k * radius * 0.671275, k * height * 0.05, k * radius * -0.671157 ), color },      //84 
		{ D3DXVECTOR3( k * radius * 0.742564, k * height * 0.05, k * radius * -0.742445 ), color },      //85 
		{ D3DXVECTOR3( k * radius * 0.671275, k * height * -0.05, k * radius * -0.671157 ), color },     //86 
		{ D3DXVECTOR3( k * radius * 0.742564, k * height * -0.05, k * radius * -0.742445 ), color },     //87 
		{ D3DXVECTOR3( k * radius * 0.819827, k * height * 0.05, k * radius * -0.478941 ), color },      //88 
		{ D3DXVECTOR3( k * radius * 0.906893, k * height * 0.05, k * radius * -0.529816 ), color },      //89 
		{ D3DXVECTOR3( k * radius * 0.819827, k * height * -0.05, k * radius * -0.478941 ), color },     //90 
		{ D3DXVECTOR3( k * radius * 0.906893, k * height * -0.05, k * radius * -0.529816 ), color },     //91 
		{ D3DXVECTOR3( k * radius * 0.915583, k * height * 0.05, k * radius * -0.252251 ), color },      //92 
		{ D3DXVECTOR3( k * radius * 1.01291, k * height * 0.05, k * radius * -0.278844 ), color },       //93 
		{ D3DXVECTOR3( k * radius * 0.915583, k * height * -0.05, k * radius * -0.252251 ), color },     //94 
		{ D3DXVECTOR3( k * radius * 1.01291, k * height * -0.05, k * radius * -0.278844 ), color },      //95 
	};

	int verticesCount = sizeof( vertices ) / sizeof( AGColorVertex );

	D3D10_BUFFER_DESC buffDesc; 

	buffDesc.Usage = D3D10_USAGE_DEFAULT; 
	buffDesc.ByteWidth = sizeof( vertices ); 
	buffDesc.CPUAccessFlags = 0;
	buffDesc.MiscFlags = 0;
	buffDesc.BindFlags = D3D10_BIND_VERTEX_BUFFER; 

	D3D10_SUBRESOURCE_DATA subresData; 
	subresData.pSysMem = vertices;

	color = yellow;

	HRESULT hr = device->CreateBuffer( &buffDesc, &subresData, &m_vertexBuffer );

	AGColorVertex selectedVertices[] = 
	{
		{ D3DXVECTOR3( k * radius * 0.915583, k * height * 0.05, k * radius * 0.252489 ), color },       //0 
		{ D3DXVECTOR3( k * radius * 1.05045, k * height * 0.05, k * radius * 0.000118735 ), color },     //1 
		{ D3DXVECTOR3( k * radius * 0.949549, k * height * 0.05, k * radius * 0.000118726 ), color },    //2 
		{ D3DXVECTOR3( k * radius * 1.01291, k * height * 0.05, k * radius * 0.279082 ), color },        //3 
		{ D3DXVECTOR3( k * radius * 0.915583, k * height * -0.05, k * radius * 0.252489 ), color },      //4 
		{ D3DXVECTOR3( k * radius * 0.949549, k * height * -0.05, k * radius * 0.00011873 ), color },    //5 
		{ D3DXVECTOR3( k * radius * 1.01291, k * height * -0.05, k * radius * 0.279082 ), color },       //6 
		{ D3DXVECTOR3( k * radius * 1.05045, k * height * -0.05, k * radius * 0.000118739 ), color },    //7 
		{ D3DXVECTOR3( k * radius * 0.819827, k * height * 0.05, k * radius * 0.479179 ), color },       //8 
		{ D3DXVECTOR3( k * radius * 0.906893, k * height * 0.05, k * radius * 0.530054 ), color },       //9 
		{ D3DXVECTOR3( k * radius * 0.819827, k * height * -0.05, k * radius * 0.479179 ), color },      //10 
		{ D3DXVECTOR3( k * radius * 0.906893, k * height * -0.05, k * radius * 0.530054 ), color },      //11 
		{ D3DXVECTOR3( k * radius * 0.671275, k * height * 0.05, k * radius * 0.671394 ), color },       //12 
		{ D3DXVECTOR3( k * radius * 0.742564, k * height * 0.05, k * radius * 0.742683 ), color },       //13 
		{ D3DXVECTOR3( k * radius * 0.671275, k * height * -0.05, k * radius * 0.671394 ), color },      //14 
		{ D3DXVECTOR3( k * radius * 0.742564, k * height * -0.05, k * radius * 0.742683 ), color },      //15 
		{ D3DXVECTOR3( k * radius * 0.47906, k * height * 0.05, k * radius * 0.819946 ), color },        //16 
		{ D3DXVECTOR3( k * radius * 0.529935, k * height * 0.05, k * radius * 0.907011 ), color },       //17 
		{ D3DXVECTOR3( k * radius * 0.47906, k * height * -0.05, k * radius * 0.819946 ), color },       //18 
		{ D3DXVECTOR3( k * radius * 0.529935, k * height * -0.05, k * radius * 0.907011 ), color },      //19 
		{ D3DXVECTOR3( k * radius * 0.25237, k * height * 0.05, k * radius * 0.915702 ), color },        //20 
		{ D3DXVECTOR3( k * radius * 0.278963, k * height * 0.05, k * radius * 1.01302 ), color },        //21 
		{ D3DXVECTOR3( k * radius * 0.25237, k * height * -0.05, k * radius * 0.915702 ), color },       //22 
		{ D3DXVECTOR3( k * radius * 0.278963, k * height * -0.05, k * radius * 1.01302 ), color },       //23 
		{ D3DXVECTOR3( k * radius * 5.39365e-009, k * height * 0.05, k * radius * 0.949668 ), color },   //24 
		{ D3DXVECTOR3( k * radius * -8.84453e-008, k * height * 0.05, k * radius * 1.05057 ), color },   //25 
		{ D3DXVECTOR3( k * radius * 1.02251e-009, k * height * -0.05, k * radius * 0.949668 ), color },  //26 
		{ D3DXVECTOR3( k * radius * -9.28164e-008, k * height * -0.05, k * radius * 1.05057 ), color },  //27 
		{ D3DXVECTOR3( k * radius * -0.25237, k * height * 0.05, k * radius * 0.915702 ), color },       //28 
		{ D3DXVECTOR3( k * radius * -0.278963, k * height * 0.05, k * radius * 1.01302 ), color },       //29 
		{ D3DXVECTOR3( k * radius * -0.25237, k * height * -0.05, k * radius * 0.915702 ), color },      //30 
		{ D3DXVECTOR3( k * radius * -0.278963, k * height * -0.05, k * radius * 1.01302 ), color },      //31 
		{ D3DXVECTOR3( k * radius * -0.47906, k * height * 0.05, k * radius * 0.819946 ), color },       //32 
		{ D3DXVECTOR3( k * radius * -0.529935, k * height * 0.05, k * radius * 0.907011 ), color },      //33 
		{ D3DXVECTOR3( k * radius * -0.47906, k * height * -0.05, k * radius * 0.819946 ), color },      //34 
		{ D3DXVECTOR3( k * radius * -0.529935, k * height * -0.05, k * radius * 0.907011 ), color },     //35 
		{ D3DXVECTOR3( k * radius * -0.671275, k * height * 0.05, k * radius * 0.671394 ), color },      //36 
		{ D3DXVECTOR3( k * radius * -0.742564, k * height * 0.05, k * radius * 0.742683 ), color },      //37 
		{ D3DXVECTOR3( k * radius * -0.671275, k * height * -0.05, k * radius * 0.671394 ), color },     //38 
		{ D3DXVECTOR3( k * radius * -0.742564, k * height * -0.05, k * radius * 0.742683 ), color },     //39 
		{ D3DXVECTOR3( k * radius * -0.819827, k * height * 0.05, k * radius * 0.479179 ), color },      //40 
		{ D3DXVECTOR3( k * radius * -0.906893, k * height * 0.05, k * radius * 0.530054 ), color },      //41 
		{ D3DXVECTOR3( k * radius * -0.819827, k * height * -0.05, k * radius * 0.479179 ), color },     //42 
		{ D3DXVECTOR3( k * radius * -0.906893, k * height * -0.05, k * radius * 0.530054 ), color },     //43 
		{ D3DXVECTOR3( k * radius * -0.915583, k * height * 0.05, k * radius * 0.252489 ), color },      //44 
		{ D3DXVECTOR3( k * radius * -1.01291, k * height * 0.05, k * radius * 0.279082 ), color },       //45 
		{ D3DXVECTOR3( k * radius * -0.915583, k * height * -0.05, k * radius * 0.252489 ), color },     //46 
		{ D3DXVECTOR3( k * radius * -1.01291, k * height * -0.05, k * radius * 0.279081 ), color },      //47 
		{ D3DXVECTOR3( k * radius * -0.949549, k * height * 0.05, k * radius * 0.000118674 ), color },   //48 
		{ D3DXVECTOR3( k * radius * -1.05045, k * height * 0.05, k * radius * 0.00011862 ), color },     //49 
		{ D3DXVECTOR3( k * radius * -0.949549, k * height * -0.05, k * radius * 0.00011867 ), color },   //50 
		{ D3DXVECTOR3( k * radius * -1.05045, k * height * -0.05, k * radius * 0.000118616 ), color },   //51 
		{ D3DXVECTOR3( k * radius * -0.915583, k * height * 0.05, k * radius * -0.252251 ), color },     //52 
		{ D3DXVECTOR3( k * radius * -1.01291, k * height * 0.05, k * radius * -0.278844 ), color },      //53 
		{ D3DXVECTOR3( k * radius * -0.915583, k * height * -0.05, k * radius * -0.252251 ), color },    //54 
		{ D3DXVECTOR3( k * radius * -1.01291, k * height * -0.05, k * radius * -0.278844 ), color },     //55 
		{ D3DXVECTOR3( k * radius * -0.819827, k * height * 0.05, k * radius * -0.478941 ), color },     //56 
		{ D3DXVECTOR3( k * radius * -0.906892, k * height * 0.05, k * radius * -0.529816 ), color },     //57 
		{ D3DXVECTOR3( k * radius * -0.819827, k * height * -0.05, k * radius * -0.478941 ), color },    //58 
		{ D3DXVECTOR3( k * radius * -0.906892, k * height * -0.05, k * radius * -0.529816 ), color },    //59 
		{ D3DXVECTOR3( k * radius * -0.671275, k * height * 0.05, k * radius * -0.671157 ), color },     //60 
		{ D3DXVECTOR3( k * radius * -0.742564, k * height * 0.05, k * radius * -0.742446 ), color },     //61 
		{ D3DXVECTOR3( k * radius * -0.671275, k * height * -0.05, k * radius * -0.671157 ), color },    //62 
		{ D3DXVECTOR3( k * radius * -0.742564, k * height * -0.05, k * radius * -0.742446 ), color },    //63 
		{ D3DXVECTOR3( k * radius * -0.47906, k * height * 0.05, k * radius * -0.819708 ), color },      //64 
		{ D3DXVECTOR3( k * radius * -0.529935, k * height * 0.05, k * radius * -0.906774 ), color },     //65 
		{ D3DXVECTOR3( k * radius * -0.47906, k * height * -0.05, k * radius * -0.819708 ), color },     //66 
		{ D3DXVECTOR3( k * radius * -0.529935, k * height * -0.05, k * radius * -0.906774 ), color },    //67 
		{ D3DXVECTOR3( k * radius * -0.25237, k * height * 0.05, k * radius * -0.915465 ), color },      //68 
		{ D3DXVECTOR3( k * radius * -0.278963, k * height * 0.05, k * radius * -1.01279 ), color },      //69 
		{ D3DXVECTOR3( k * radius * -0.25237, k * height * -0.05, k * radius * -0.915465 ), color },     //70 
		{ D3DXVECTOR3( k * radius * -0.278963, k * height * -0.05, k * radius * -1.01279 ), color },     //71 
		{ D3DXVECTOR3( k * radius * -5.53303e-008, k * height * 0.05, k * radius * -0.94943 ), color },  //72 
		{ D3DXVECTOR3( k * radius * 7.48089e-008, k * height * 0.05, k * radius * -1.05033 ), color },   //73 
		{ D3DXVECTOR3( k * radius * -5.09591e-008, k * height * -0.05, k * radius * -0.94943 ), color }, //74 
		{ D3DXVECTOR3( k * radius * 7.918e-008, k * height * -0.05, k * radius * -1.05033 ), color },    //75 
		{ D3DXVECTOR3( k * radius * 0.25237, k * height * 0.05, k * radius * -0.915464 ), color },       //76 
		{ D3DXVECTOR3( k * radius * 0.278963, k * height * 0.05, k * radius * -1.01279 ), color },       //77 
		{ D3DXVECTOR3( k * radius * 0.25237, k * height * -0.05, k * radius * -0.915464 ), color },      //78 
		{ D3DXVECTOR3( k * radius * 0.278963, k * height * -0.05, k * radius * -1.01279 ), color },      //79 
		{ D3DXVECTOR3( k * radius * 0.47906, k * height * 0.05, k * radius * -0.819708 ), color },       //80 
		{ D3DXVECTOR3( k * radius * 0.529935, k * height * 0.05, k * radius * -0.906774 ), color },      //81 
		{ D3DXVECTOR3( k * radius * 0.47906, k * height * -0.05, k * radius * -0.819708 ), color },      //82 
		{ D3DXVECTOR3( k * radius * 0.529935, k * height * -0.05, k * radius * -0.906774 ), color },     //83 
		{ D3DXVECTOR3( k * radius * 0.671275, k * height * 0.05, k * radius * -0.671157 ), color },      //84 
		{ D3DXVECTOR3( k * radius * 0.742564, k * height * 0.05, k * radius * -0.742445 ), color },      //85 
		{ D3DXVECTOR3( k * radius * 0.671275, k * height * -0.05, k * radius * -0.671157 ), color },     //86 
		{ D3DXVECTOR3( k * radius * 0.742564, k * height * -0.05, k * radius * -0.742445 ), color },     //87 
		{ D3DXVECTOR3( k * radius * 0.819827, k * height * 0.05, k * radius * -0.478941 ), color },      //88 
		{ D3DXVECTOR3( k * radius * 0.906893, k * height * 0.05, k * radius * -0.529816 ), color },      //89 
		{ D3DXVECTOR3( k * radius * 0.819827, k * height * -0.05, k * radius * -0.478941 ), color },     //90 
		{ D3DXVECTOR3( k * radius * 0.906893, k * height * -0.05, k * radius * -0.529816 ), color },     //91 
		{ D3DXVECTOR3( k * radius * 0.915583, k * height * 0.05, k * radius * -0.252251 ), color },      //92 
		{ D3DXVECTOR3( k * radius * 1.01291, k * height * 0.05, k * radius * -0.278844 ), color },       //93 
		{ D3DXVECTOR3( k * radius * 0.915583, k * height * -0.05, k * radius * -0.252251 ), color },     //94 
		{ D3DXVECTOR3( k * radius * 1.01291, k * height * -0.05, k * radius * -0.278844 ), color },      //95 
	};

	AGColorVertex boundingVertices[] = 
	{
		{ D3DXVECTOR3( k * radius * 0.915583, k * height * 0.05, k * radius * 0.252489 ), color },       //0 
		{ D3DXVECTOR3( k * radius * 1.05045, k * height * 0.05, k * radius * 0.000118735 ), color },     //1 
		{ D3DXVECTOR3( k * radius * 0.949549, k * height * 0.05, k * radius * 0.000118726 ), color },    //2 
		{ D3DXVECTOR3( k * radius * 1.01291, k * height * 0.05, k * radius * 0.279082 ), color },        //3 
		{ D3DXVECTOR3( k * radius * 0.915583, k * height * -0.05, k * radius * 0.252489 ), color },      //4 
		{ D3DXVECTOR3( k * radius * 0.949549, k * height * -0.05, k * radius * 0.00011873 ), color },    //5 
		{ D3DXVECTOR3( k * radius * 1.01291, k * height * -0.05, k * radius * 0.279082 ), color },       //6 
		{ D3DXVECTOR3( k * radius * 1.05045, k * height * -0.05, k * radius * 0.000118739 ), color },    //7 
		{ D3DXVECTOR3( k * radius * 0.819827, k * height * 0.05, k * radius * 0.479179 ), color },       //8 
		{ D3DXVECTOR3( k * radius * 0.906893, k * height * 0.05, k * radius * 0.530054 ), color },       //9 
		{ D3DXVECTOR3( k * radius * 0.819827, k * height * -0.05, k * radius * 0.479179 ), color },      //10 
		{ D3DXVECTOR3( k * radius * 0.906893, k * height * -0.05, k * radius * 0.530054 ), color },      //11 
		{ D3DXVECTOR3( k * radius * 0.671275, k * height * 0.05, k * radius * 0.671394 ), color },       //12 
		{ D3DXVECTOR3( k * radius * 0.742564, k * height * 0.05, k * radius * 0.742683 ), color },       //13 
		{ D3DXVECTOR3( k * radius * 0.671275, k * height * -0.05, k * radius * 0.671394 ), color },      //14 
		{ D3DXVECTOR3( k * radius * 0.742564, k * height * -0.05, k * radius * 0.742683 ), color },      //15 
		{ D3DXVECTOR3( k * radius * 0.47906, k * height * 0.05, k * radius * 0.819946 ), color },        //16 
		{ D3DXVECTOR3( k * radius * 0.529935, k * height * 0.05, k * radius * 0.907011 ), color },       //17 
		{ D3DXVECTOR3( k * radius * 0.47906, k * height * -0.05, k * radius * 0.819946 ), color },       //18 
		{ D3DXVECTOR3( k * radius * 0.529935, k * height * -0.05, k * radius * 0.907011 ), color },      //19 
		{ D3DXVECTOR3( k * radius * 0.25237, k * height * 0.05, k * radius * 0.915702 ), color },        //20 
		{ D3DXVECTOR3( k * radius * 0.278963, k * height * 0.05, k * radius * 1.01302 ), color },        //21 
		{ D3DXVECTOR3( k * radius * 0.25237, k * height * -0.05, k * radius * 0.915702 ), color },       //22 
		{ D3DXVECTOR3( k * radius * 0.278963, k * height * -0.05, k * radius * 1.01302 ), color },       //23 
		{ D3DXVECTOR3( k * radius * 5.39365e-009, k * height * 0.05, k * radius * 0.949668 ), color },   //24 
		{ D3DXVECTOR3( k * radius * -8.84453e-008, k * height * 0.05, k * radius * 1.05057 ), color },   //25 
		{ D3DXVECTOR3( k * radius * 1.02251e-009, k * height * -0.05, k * radius * 0.949668 ), color },  //26 
		{ D3DXVECTOR3( k * radius * -9.28164e-008, k * height * -0.05, k * radius * 1.05057 ), color },  //27 
		{ D3DXVECTOR3( k * radius * -0.25237, k * height * 0.05, k * radius * 0.915702 ), color },       //28 
		{ D3DXVECTOR3( k * radius * -0.278963, k * height * 0.05, k * radius * 1.01302 ), color },       //29 
		{ D3DXVECTOR3( k * radius * -0.25237, k * height * -0.05, k * radius * 0.915702 ), color },      //30 
		{ D3DXVECTOR3( k * radius * -0.278963, k * height * -0.05, k * radius * 1.01302 ), color },      //31 
		{ D3DXVECTOR3( k * radius * -0.47906, k * height * 0.05, k * radius * 0.819946 ), color },       //32 
		{ D3DXVECTOR3( k * radius * -0.529935, k * height * 0.05, k * radius * 0.907011 ), color },      //33 
		{ D3DXVECTOR3( k * radius * -0.47906, k * height * -0.05, k * radius * 0.819946 ), color },      //34 
		{ D3DXVECTOR3( k * radius * -0.529935, k * height * -0.05, k * radius * 0.907011 ), color },     //35 
		{ D3DXVECTOR3( k * radius * -0.671275, k * height * 0.05, k * radius * 0.671394 ), color },      //36 
		{ D3DXVECTOR3( k * radius * -0.742564, k * height * 0.05, k * radius * 0.742683 ), color },      //37 
		{ D3DXVECTOR3( k * radius * -0.671275, k * height * -0.05, k * radius * 0.671394 ), color },     //38 
		{ D3DXVECTOR3( k * radius * -0.742564, k * height * -0.05, k * radius * 0.742683 ), color },     //39 
		{ D3DXVECTOR3( k * radius * -0.819827, k * height * 0.05, k * radius * 0.479179 ), color },      //40 
		{ D3DXVECTOR3( k * radius * -0.906893, k * height * 0.05, k * radius * 0.530054 ), color },      //41 
		{ D3DXVECTOR3( k * radius * -0.819827, k * height * -0.05, k * radius * 0.479179 ), color },     //42 
		{ D3DXVECTOR3( k * radius * -0.906893, k * height * -0.05, k * radius * 0.530054 ), color },     //43 
		{ D3DXVECTOR3( k * radius * -0.915583, k * height * 0.05, k * radius * 0.252489 ), color },      //44 
		{ D3DXVECTOR3( k * radius * -1.01291, k * height * 0.05, k * radius * 0.279082 ), color },       //45 
		{ D3DXVECTOR3( k * radius * -0.915583, k * height * -0.05, k * radius * 0.252489 ), color },     //46 
		{ D3DXVECTOR3( k * radius * -1.01291, k * height * -0.05, k * radius * 0.279081 ), color },      //47 
		{ D3DXVECTOR3( k * radius * -0.949549, k * height * 0.05, k * radius * 0.000118674 ), color },   //48 
		{ D3DXVECTOR3( k * radius * -1.05045, k * height * 0.05, k * radius * 0.00011862 ), color },     //49 
		{ D3DXVECTOR3( k * radius * -0.949549, k * height * -0.05, k * radius * 0.00011867 ), color },   //50 
		{ D3DXVECTOR3( k * radius * -1.05045, k * height * -0.05, k * radius * 0.000118616 ), color },   //51 
		{ D3DXVECTOR3( k * radius * -0.915583, k * height * 0.05, k * radius * -0.252251 ), color },     //52 
		{ D3DXVECTOR3( k * radius * -1.01291, k * height * 0.05, k * radius * -0.278844 ), color },      //53 
		{ D3DXVECTOR3( k * radius * -0.915583, k * height * -0.05, k * radius * -0.252251 ), color },    //54 
		{ D3DXVECTOR3( k * radius * -1.01291, k * height * -0.05, k * radius * -0.278844 ), color },     //55 
		{ D3DXVECTOR3( k * radius * -0.819827, k * height * 0.05, k * radius * -0.478941 ), color },     //56 
		{ D3DXVECTOR3( k * radius * -0.906892, k * height * 0.05, k * radius * -0.529816 ), color },     //57 
		{ D3DXVECTOR3( k * radius * -0.819827, k * height * -0.05, k * radius * -0.478941 ), color },    //58 
		{ D3DXVECTOR3( k * radius * -0.906892, k * height * -0.05, k * radius * -0.529816 ), color },    //59 
		{ D3DXVECTOR3( k * radius * -0.671275, k * height * 0.05, k * radius * -0.671157 ), color },     //60 
		{ D3DXVECTOR3( k * radius * -0.742564, k * height * 0.05, k * radius * -0.742446 ), color },     //61 
		{ D3DXVECTOR3( k * radius * -0.671275, k * height * -0.05, k * radius * -0.671157 ), color },    //62 
		{ D3DXVECTOR3( k * radius * -0.742564, k * height * -0.05, k * radius * -0.742446 ), color },    //63 
		{ D3DXVECTOR3( k * radius * -0.47906, k * height * 0.05, k * radius * -0.819708 ), color },      //64 
		{ D3DXVECTOR3( k * radius * -0.529935, k * height * 0.05, k * radius * -0.906774 ), color },     //65 
		{ D3DXVECTOR3( k * radius * -0.47906, k * height * -0.05, k * radius * -0.819708 ), color },     //66 
		{ D3DXVECTOR3( k * radius * -0.529935, k * height * -0.05, k * radius * -0.906774 ), color },    //67 
		{ D3DXVECTOR3( k * radius * -0.25237, k * height * 0.05, k * radius * -0.915465 ), color },      //68 
		{ D3DXVECTOR3( k * radius * -0.278963, k * height * 0.05, k * radius * -1.01279 ), color },      //69 
		{ D3DXVECTOR3( k * radius * -0.25237, k * height * -0.05, k * radius * -0.915465 ), color },     //70 
		{ D3DXVECTOR3( k * radius * -0.278963, k * height * -0.05, k * radius * -1.01279 ), color },     //71 
		{ D3DXVECTOR3( k * radius * -5.53303e-008, k * height * 0.05, k * radius * -0.94943 ), color },  //72 
		{ D3DXVECTOR3( k * radius * 7.48089e-008, k * height * 0.05, k * radius * -1.05033 ), color },   //73 
		{ D3DXVECTOR3( k * radius * -5.09591e-008, k * height * -0.05, k * radius * -0.94943 ), color }, //74 
		{ D3DXVECTOR3( k * radius * 7.918e-008, k * height * -0.05, k * radius * -1.05033 ), color },    //75 
		{ D3DXVECTOR3( k * radius * 0.25237, k * height * 0.05, k * radius * -0.915464 ), color },       //76 
		{ D3DXVECTOR3( k * radius * 0.278963, k * height * 0.05, k * radius * -1.01279 ), color },       //77 
		{ D3DXVECTOR3( k * radius * 0.25237, k * height * -0.05, k * radius * -0.915464 ), color },      //78 
		{ D3DXVECTOR3( k * radius * 0.278963, k * height * -0.05, k * radius * -1.01279 ), color },      //79 
		{ D3DXVECTOR3( k * radius * 0.47906, k * height * 0.05, k * radius * -0.819708 ), color },       //80 
		{ D3DXVECTOR3( k * radius * 0.529935, k * height * 0.05, k * radius * -0.906774 ), color },      //81 
		{ D3DXVECTOR3( k * radius * 0.47906, k * height * -0.05, k * radius * -0.819708 ), color },      //82 
		{ D3DXVECTOR3( k * radius * 0.529935, k * height * -0.05, k * radius * -0.906774 ), color },     //83 
		{ D3DXVECTOR3( k * radius * 0.671275, k * height * 0.05, k * radius * -0.671157 ), color },      //84 
		{ D3DXVECTOR3( k * radius * 0.742564, k * height * 0.05, k * radius * -0.742445 ), color },      //85 
		{ D3DXVECTOR3( k * radius * 0.671275, k * height * -0.05, k * radius * -0.671157 ), color },     //86 
		{ D3DXVECTOR3( k * radius * 0.742564, k * height * -0.05, k * radius * -0.742445 ), color },     //87 
		{ D3DXVECTOR3( k * radius * 0.819827, k * height * 0.05, k * radius * -0.478941 ), color },      //88 
		{ D3DXVECTOR3( k * radius * 0.906893, k * height * 0.05, k * radius * -0.529816 ), color },      //89 
		{ D3DXVECTOR3( k * radius * 0.819827, k * height * -0.05, k * radius * -0.478941 ), color },     //90 
		{ D3DXVECTOR3( k * radius * 0.906893, k * height * -0.05, k * radius * -0.529816 ), color },     //91 
		{ D3DXVECTOR3( k * radius * 0.915583, k * height * 0.05, k * radius * -0.252251 ), color },      //92 
		{ D3DXVECTOR3( k * radius * 1.01291, k * height * 0.05, k * radius * -0.278844 ), color },       //93 
		{ D3DXVECTOR3( k * radius * 0.915583, k * height * -0.05, k * radius * -0.252251 ), color },     //94 
		{ D3DXVECTOR3( k * radius * 1.01291, k * height * -0.05, k * radius * -0.278844 ), color },      //95 
	};

	for( int i = 0 ; i < verticesCount; i++ )
	{
		m_vertices.push_back( selectedVertices[ i ] );
	}

	subresData.pSysMem = selectedVertices; 

	device->CreateBuffer( &buffDesc, &subresData, &m_additionalVB );

	if( FAILED( hr ) )
	{
		AGError() << "Couldn't create vertex buffer";
		return; 
	}

	int indices[] = 
	{
		0, 
		1, 2, 1, 0, 3, 
		4, 2, 5, 2, 4, 
		0, 6, 5, 7, 5, 
		6, 4, 3, 7, 1, 
		7, 3, 6, 8, 3, 
		0, 3, 8, 9, 10, 
		0, 4, 0, 10, 8, 
		11, 4, 6, 4, 11, 
		10, 9, 6, 3, 6, 
		9, 11, 12, 9, 8, 
		9, 12, 13, 14, 8, 
		10, 8, 14, 12, 15, 
		10, 11, 10, 15, 14, 
		13, 11, 9, 11, 13, 
		15, 16, 13, 12, 13, 
		16, 17, 18, 12, 14, 
		12, 18, 16, 19, 14, 
		15, 14, 19, 18, 17, 
		15, 13, 15, 17, 19, 
		20, 17, 16, 17, 20, 
		21, 22, 16, 18, 16, 
		22, 20, 23, 18, 19, 
		18, 23, 22, 21, 19, 
		17, 19, 21, 23, 24, 
		21, 20, 21, 24, 25, 
		26, 20, 22, 20, 26, 
		24, 27, 22, 23, 22, 
		27, 26, 25, 23, 21, 
		23, 25, 27, 28, 25, 
		24, 25, 28, 29, 30, 
		24, 26, 24, 30, 28, 
		31, 26, 27, 26, 31, 
		30, 29, 27, 25, 27, 
		29, 31, 32, 29, 28, 
		29, 32, 33, 34, 28, 
		30, 28, 34, 32, 35, 
		30, 31, 30, 35, 34, 
		33, 31, 29, 31, 33, 
		35, 36, 33, 32, 33, 
		36, 37, 38, 32, 34, 
		32, 38, 36, 39, 34, 
		35, 34, 39, 38, 37, 
		35, 33, 35, 37, 39, 
		40, 37, 36, 37, 40, 
		41, 42, 36, 38, 36, 
		42, 40, 43, 38, 39, 
		38, 43, 42, 41, 39, 
		37, 39, 41, 43, 44, 
		41, 40, 41, 44, 45, 
		46, 40, 42, 40, 46, 
		44, 47, 42, 43, 42, 
		47, 46, 45, 43, 41, 
		43, 45, 47, 48, 45, 
		44, 45, 48, 49, 50, 
		44, 46, 44, 50, 48, 
		51, 46, 47, 46, 51, 
		50, 49, 47, 45, 47, 
		49, 51, 52, 49, 48, 
		49, 52, 53, 54, 48, 
		50, 48, 54, 52, 55, 
		50, 51, 50, 55, 54, 
		53, 51, 49, 51, 53, 
		55, 56, 53, 52, 53, 
		56, 57, 58, 52, 54, 
		52, 58, 56, 59, 54, 
		55, 54, 59, 58, 57, 
		55, 53, 55, 57, 59, 
		60, 57, 56, 57, 60, 
		61, 62, 56, 58, 56, 
		62, 60, 63, 58, 59, 
		58, 63, 62, 61, 59, 
		57, 59, 61, 63, 64, 
		61, 60, 61, 64, 65, 
		66, 60, 62, 60, 66, 
		64, 67, 62, 63, 62, 
		67, 66, 65, 63, 61, 
		63, 65, 67, 68, 65, 
		64, 65, 68, 69, 70, 
		64, 66, 64, 70, 68, 
		71, 66, 67, 66, 71, 
		70, 69, 67, 65, 67, 
		69, 71, 72, 69, 68, 
		69, 72, 73, 74, 68, 
		70, 68, 74, 72, 75, 
		70, 71, 70, 75, 74, 
		73, 71, 69, 71, 73, 
		75, 76, 73, 72, 73, 
		76, 77, 78, 72, 74, 
		72, 78, 76, 79, 74, 
		75, 74, 79, 78, 77, 
		75, 73, 75, 77, 79, 
		80, 77, 76, 77, 80, 
		81, 82, 76, 78, 76, 
		82, 80, 83, 78, 79, 
		78, 83, 82, 81, 79, 
		77, 79, 81, 83, 84, 
		81, 80, 81, 84, 85, 
		86, 80, 82, 80, 86, 
		84, 87, 82, 83, 82, 
		87, 86, 85, 83, 81, 
		83, 85, 87, 88, 85, 
		84, 85, 88, 89, 90, 
		84, 86, 84, 90, 88, 
		91, 86, 87, 86, 91, 
		90, 89, 87, 85, 87, 
		89, 91, 92, 89, 88, 
		89, 92, 93, 94, 88, 
		90, 88, 94, 92, 95, 
		90, 91, 90, 95, 94, 
		93, 91, 89, 91, 93, 
		95, 2, 93, 92, 93, 
		2, 1, 5, 92, 94, 
		92, 5, 2, 7, 94, 
		95, 94, 7, 5, 1, 
		95, 93, 95, 1, 7, 
	};

	buffDesc.ByteWidth = sizeof( indices );
	buffDesc.BindFlags = D3D10_BIND_INDEX_BUFFER; 
	subresData.pSysMem = indices;

	m_nIndices = sizeof( indices ) / sizeof( indices[ 0 ] );

	for( int i = 0; i < m_nIndices; i++ )
	{
		m_indices.push_back( indices[ i ] );
	}

	hr = device->CreateBuffer( &buffDesc, &subresData, &m_indexBuffer );

	if( FAILED( hr ) )
	{
		AGError() << "Couldn't create index buffer"; 
		return; 
	}

	D3D10_DEPTH_STENCIL_DESC dsDesc; 

	dsDesc.DepthEnable = false; 
	dsDesc.DepthFunc = D3D10_COMPARISON_GREATER; 
	dsDesc.DepthWriteMask = D3D10_DEPTH_WRITE_MASK_ALL; 

	dsDesc.StencilEnable = true;
	dsDesc.StencilReadMask = 0xFF;
	dsDesc.StencilWriteMask = 0xFF;

	// Stencil operations if pixel is front-facing
	dsDesc.FrontFace.StencilFailOp = D3D10_STENCIL_OP_KEEP;
	dsDesc.FrontFace.StencilDepthFailOp = D3D10_STENCIL_OP_INCR;
	dsDesc.FrontFace.StencilPassOp = D3D10_STENCIL_OP_KEEP;
	dsDesc.FrontFace.StencilFunc = D3D10_COMPARISON_ALWAYS;

	// Stencil operations if pixel is back-facing
	dsDesc.BackFace.StencilFailOp = D3D10_STENCIL_OP_KEEP;
	dsDesc.BackFace.StencilDepthFailOp = D3D10_STENCIL_OP_DECR;
	dsDesc.BackFace.StencilPassOp = D3D10_STENCIL_OP_KEEP;
	dsDesc.BackFace.StencilFunc = D3D10_COMPARISON_ALWAYS;

	device->CreateDepthStencilState( &dsDesc, &m_depthState );
}

AGDXCircle::~AGDXCircle()
{

}

void AGDXCircle::draw(AGDXSurface* surface)
{
	D3D10_TECHNIQUE_DESC desc; 
	m_technique->GetDesc( &desc );

	AGDXCamera* camera = surface->getCamera(); 
	ID3D10Device* device = surface->getDevice(); 

	D3DXVECTOR3 camEye = camera->getEye(); 
	D3DXVECTOR3 dir = camEye - m_worldPos; 
	D3DXVec3Normalize( &dir, &dir );
	dir = camEye - dir * 1.0f; 
	D3DXVECTOR3 pos = dir; 

	setPos( pos.x, pos.y, pos.z );

	D3DXMATRIX worldTextMat = getWorld();

	if( m_axis == X_AXIS )
	{
		setAngle( 0.0f, 0.0f, D3DXToRadian( -90.0f ) );	
	}
	else if( m_axis == Z_AXIS )
	{
		setAngle( D3DXToRadian( 90.0f ), 0.0f, 0.0f );	
	} 

	D3DXMATRIX viewMat = camera->getViewMatrix();
	D3DXMATRIX projMat = camera->getProjMatrix();

	m_worldVar->SetMatrix( getWorld() );
	m_viewVar->SetMatrix( viewMat );
	m_projectionVar->SetMatrix( projMat );

	device->IASetInputLayout( m_inputLayout );
	device->IASetIndexBuffer( m_indexBuffer, DXGI_FORMAT_R32_UINT, 0 );
	UINT stride = sizeof( AGColorVertex );
	UINT offset = 0; 
	
	if( m_isSelected )
	{
		device->IASetVertexBuffers( 0, 1, &m_additionalVB, &stride, &offset );
	}
	else 
	{
		device->IASetVertexBuffers( 0, 1, &m_vertexBuffer, &stride, &offset );
	}
	device->OMSetDepthStencilState( m_depthState, 1 );

	for( int i = 0; i < desc.Passes; i++ )
	{
		m_technique->GetPassByIndex( i )->Apply( 0 );
		device->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
		device->DrawIndexed( m_nIndices, 0, 0 );
	}

	//m_boundingBox->setWorld( getWorld() );
}

float AGDXCircle::intersect(D3DXVECTOR3 rayOrigin, D3DXVECTOR3 rayDir)
{
	float retDist = -1.0f;
	int nIndices = m_indices.size() - 2;  
	for( int i = 0; i < nIndices; i++ )
	{
		D3DXVECTOR3 vertex1 = m_vertices[ m_indices[ i ] ].pos;
		D3DXVECTOR3 vertex2 = m_vertices[ m_indices[ i + 1 ] ].pos;
		D3DXVECTOR3 vertex3 = m_vertices[ m_indices[ i + 2 ] ].pos;

		float dist, u, v; 

		bool res = D3DXIntersectTri( &vertex1, &vertex2, &vertex3, &rayOrigin, &rayDir, &u, &v, &dist );
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
		}
	}

	return retDist; 
}

AGDXIntersectedTriangle AGDXCircle::getIntersectedTriangle(D3DXVECTOR3 rayOrigin, D3DXVECTOR3 rayDir)
{
	AGDXIntersectedTriangle triangle; 
	triangle.dist = -1.0f; 
	int nIndices = m_indices.size() - 2;  
	for( int i = 0; i < nIndices; i++ )
	{
		D3DXVECTOR3 vertex1 = m_vertices[ m_indices[ i ] ].pos;
		D3DXVECTOR3 vertex2 = m_vertices[ m_indices[ i + 1 ] ].pos;
		D3DXVECTOR3 vertex3 = m_vertices[ m_indices[ i + 2 ] ].pos;

		float dist, u, v; 

		bool res = D3DXIntersectTri( &vertex1, &vertex2, &vertex3, &rayOrigin, &rayDir, &u, &v, &dist );
		if( res )
		{
			if( triangle.dist < 0 )
			{
				triangle.dist = dist; 
			}
			else 
			{
				triangle.dist = min( triangle.dist, dist );	
			}
		}
	}

	return triangle; 
}

D3DXVECTOR3 AGDXCircle::getAxis()
{
	return D3DXVECTOR3( m_axis == X_AXIS, m_axis == Y_AXIS, m_axis == Z_AXIS );
	//return D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
}


