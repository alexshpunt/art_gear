#ifndef AG_ABSTRACTSYSTEM_H
#define AG_ABSTRACTSYSTEM_H

class AGAbstractSystem 
{
	public:
		virtual ~AGAbstractSystem(){}

		virtual void update() = 0; 
		virtual void shutdown() = 0; 
};

#endif 