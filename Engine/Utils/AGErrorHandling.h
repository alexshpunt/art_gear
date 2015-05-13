#ifndef AG_ERRORHANDLING_H
#define AG_ERRORHANDLING_H

#include <assert.h>

#define softAssert( exrp ) if( !expr ){ return; }
#define softAssert( expr, ret ) if( !expr ){ return ret; }

#endif 