#ifndef AG_BILLBOARD_H
#define AG_BILLBOARD_H

#include "Engine/Graphics/Interfaces/AGSurface.h"
#include "Engine/Graphics/Interfaces/AGPureInterfaces.h"

#include "Engine/Math/AGMath.h"

class AGBillboardPrivate; 
class AGTexture2D;

class AGBillboard : public AGDrawable
{
	public:
		AGBillboard();
		~AGBillboard();

		void setPos( const AGVec3& pos );
		const AGVec3& getPos() const; 

		void setSize( const AGSize& size );
		const AGSize& getSize() const; 

		void draw( AGSurface* surface );

		void setTexture( AGTexture2D* texture );

	private:
		void setup(); 

		AGBillboardPrivate* m_p; 
};

#endif 