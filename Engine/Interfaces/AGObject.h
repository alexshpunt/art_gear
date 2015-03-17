#ifndef AG_OBJECT
#define AG_OBJECT

#include <string>
#include <list>

class AGObject 
{
	public:
		AGObject();
		~AGObject();

		void registerListener( AGObject* listener );
		void unregisterListener( AGObject* listener ); 

		void setName( std::string name );
		std::string getName(); 

		virtual void notify(); 
	protected:
		void sendNotifications(); 

		std::string m_name; 
	private: 
		std::list< AGObject* > m_listeners; 
};

#endif 