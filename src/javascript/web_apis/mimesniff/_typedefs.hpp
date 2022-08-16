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


struct mimesniff::detail::mime_type_t
{
    ext::string type;
    ext::string sub_type;
    ext::map<ext::string, ext::string> parameters;

    auto operator==(const mime_type_t&) const -> bool = default;
};


struct mimesniff::detail::resource_t
{
    mime_type_t supplied_mime_type;
    mime_type_t computed_mime_type;
    ext::boolean check_for_apache_bug_flag;
    ext::boolean no_sniff_flag;
};

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MIMESNIFF__TYPEDEFS_HPP
