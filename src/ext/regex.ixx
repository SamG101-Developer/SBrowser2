export module ext.regex;

#include "ext/keywords.hpp"
#include <re2/re2.h>
#include <re2/stringpiece.h>


_EXT_BEGIN
    export namespace regex = re2;
    export using regex_utils = RE2;
_EXT_END
