module;
#include "ext/macros/namespaces.hpp"
#include <re2/re2.h>
#include <re2/stringpiece.h>


export module ext.core:regex;


_EXT_BEGIN
    template <ext::string_like T> auto regex_matches(T&& pattern, T&& matches)
_EXT_END
