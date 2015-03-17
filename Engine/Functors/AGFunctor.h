#ifndef AG_FUNCTOR_H
#define AG_FUNCTOR_H

#include <string>

using namespace std;

class AGFunctor 
{
	public:
		virtual void operator()( const string& arg1, const string& arg2 ) = 0;
};

#endif 