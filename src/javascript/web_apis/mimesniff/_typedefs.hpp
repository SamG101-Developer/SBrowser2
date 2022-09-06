#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MIMESNIFF__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MIMESNIFF__TYPEDEFS_HPP

#include "ext/boolean.hpp"
#include "ext/map.hpp"
#include "ext/string.hpp"

namespace mimesniff::detail
{
    struct mime_type_t;
    struct resource_t;
    using resource_header_t = char*;
    using byte_pattern_t = char*;
    using pattern_mask_t = char*;
}


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MIMESNIFF__TYPEDEFS_HPP
