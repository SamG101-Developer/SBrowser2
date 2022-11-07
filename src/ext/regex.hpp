#ifndef SBROWSER2_SRC_EXT_REGEX_HPP
#define SBROWSER2_SRC_EXT_REGEX_HPP

#include "ext/keywords.hpp"
#include <re2/re2.h>
#include <re2/stringpiece.h>


_EXT_BEGIN
    namespace regex = re2;
    using regex_utils = RE2;
_EXT_END


#endif //SBROWSER2_SRC_EXT_REGEX_HPP
