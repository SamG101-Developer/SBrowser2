module;
#include "ext/macros/namespaces.hpp"
#include <re2/re2.h>
#include <re2/stringpiece.h>


_EXT_BEGIN
    namespace regex = re2;
    using regex_utils = RE2;
_EXT_END


export module ext.regex;
