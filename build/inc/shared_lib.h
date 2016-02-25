//----------------------------------------------------------------------------
#ifndef KW_SHAREDLIB_H
#define KW_SHAREDLIB_H
//----------------------------------------------------------------------------
#include <string>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <assert.h>
#include <tr1/functional>
#include <tr1/memory>
#include "fmt.h"
//----------------------------------------------------------------------------
using std::string;
//----------------------------------------------------------------------------
#define likely(x)       __builtin_expect((x),1)
#define unlikely(x)     __builtin_expect((x),0)
#define NSEC2MSEC(nsec) (nsec / 1000000)
#define MILLISEC2NSEC(msec) (msec * 000000)

namespace kw{
    using std::tr1::function;
    using std::tr1::shared_ptr;
    using std::tr1::weak_ptr;
}
//----------------------------------------------------------------------------
#endif // SHAREDLIB_H
