#ifndef AGE_RESOURCEPREVIEW_H
#define AGE_RESOURCEPREVIEW_H

#include <QWidget>

#include "Engine/Graphics/Interfaces/AGSurface.h"

#include "Engine/Graphics/Objects/AGMesh.h"

class AGEResourcePreview : public QWidget, public AGSurface
{
	public:
		AGEResourcePreview();
		~AGEResourcePreview();

		QPaintEngine* paintEngine() const; 

		void setMesh( AGMesh* mesh ); 
		void update(); 
	protected:
		void resizeEvent( QResizeEvent* event );

	private:
		AGMesh* m_mesh; 
};

#endif 