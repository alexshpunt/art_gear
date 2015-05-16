#ifndef AG_T_H
#define AG_T_H

#include "Engine/Graphics/Interfaces/AGPureInterfaces.h"
#include "Engine/Graphics/AGInputLayouts.h"

#include "Engine/Graphics/Objects/AGBuffer.h"

class AGT : public AGDrawable
{
	public:
		AGT();
		~AGT();

	private:
		AGBuffer< int >* m_ibo;
};

#endif 