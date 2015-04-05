#ifndef AG_GIZMO_H
#define AG_GIZMO_H

#include "Engine/Graphics/Interfaces/AGPrimitive.h"

class AGGameObject; 

//ќбъект, который рисуетс€ путЄм трансл€ции из начальных координат на вектор между камерой и начальными координатами 
class AGGizmo : public AGPrimitive
{
	public:
		AGGizmo();
		virtual ~AGGizmo();

		void setDistance( float distance );
		float getDistance() const; 

		void setBeginPos( AGVec3 beginPos );
		void setBeginPos( float x, float y, float z );
		AGVec3 getBeginPos() const;

		void translateBeginPos( AGVec3 delta );
		void translateBeginPos( float x, float y, float z );

		void setSelected( bool value );
		bool isSelected() const;

		virtual AGVec3 getAxis() = 0;
		 
	protected:
		virtual void updatePos( AGCamera* camera ); 
		virtual void setupBuffers( AGSurface* surface );

		AGVec3 m_beginPos; 
		float m_distance; 

		bool m_isSelected;

		ID3D10Buffer* m_vbo; 
		ID3D10Buffer* m_ibo; 
};

#endif