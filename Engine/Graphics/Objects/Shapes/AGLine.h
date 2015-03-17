#ifndef AG_LINE_H
#define AG_LINE_H

#include "Graphics/Interfaces/AGPrimitive.h"

class AGLine : public AGPrimitive
{
	public:
		AGLine( D3DXVECTOR3 startPoint, D3DXVECTOR3 endPoint, D3DXVECTOR4 color = D3DXVECTOR4( 1.0f, 1.0f, 1.0f, 1.0f ) ); 
		~AGLine();

		void setLine( D3DXVECTOR3 startPoint, D3DXVECTOR3 endPoint, D3DXVECTOR4 color = D3DXVECTOR4( 1.0f, 1.0f, 1.0f, 1.0f ) );

		void draw( AGSurface* surface );
};

#endif 