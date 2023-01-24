module;
#include "ext/macros/namespaces.hpp"


export module ext.js:date;
#include <asap.h>


_EXT_BEGIN
    export using date = asap::datetime;
_EXT_END
