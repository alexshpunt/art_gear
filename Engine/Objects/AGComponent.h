#ifndef AG_COMPONENT_H
#define AG_COMPONENT_H

#include <string>

using namespace std;

class AGObject; 
class AGScene; 

class AGComponent 
{
	public:
		AGComponent( AGObject* object );
		virtual ~AGComponent(); 
		
		virtual void onSceneInit() = 0;
		virtual void onSceneUpdate() = 0;
		virtual void onSceneFixedUpdate() = 0;

		AGObject* getObject() const; 
		const string& getName() const; 

	protected:
		AGObject* m_object; 
		string m_name; 
};

#endif 