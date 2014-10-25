#ifndef AG_TIMEMANAGER_H
#define AG_TIMEMANAGER_H

#include "Patterns/Singleton.h"

class AGTimeManager
{
	DECLARE_SINGLETON_INIT( AGTimeManager )
	public:
		void setDeltaTime( double dt );
		double getDeltaTime() const; 

	private:
		void init();
		 
		double m_dt;
};

#endif 