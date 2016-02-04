//----------------------------------------------------------------------------
#ifndef KW_SHAREDLIB_H
#define KW_SHAREDLIB_H
//----------------------------------------------------------------------------
#include <string>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <assert.h>
#include "fmt.h"
//----------------------------------------------------------------------------
using std::string;
//----------------------------------------------------------------------------
#define likely(x)       __builtin_expect((x),1)
#define unlikely(x)     __builtin_expect((x),0)
#define NSEC2MSEC(nsec) (nsec / 1000000)
#define MSEC2NSEC(msec) (msec * 1000000)
//----------------------------------------------------------------------------
#endif // SHAREDLIB_H
