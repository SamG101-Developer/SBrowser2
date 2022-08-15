#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MIMESNIFF__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MIMESNIFF__TYPEDEFS_HPP

#include "ext/map.hpp"
#include "ext/string.hpp"

namespace mimesniff::detail
{
    struct mime_type_t;
}


struct mimesniff::detail::mime_type_t
{
    ext::string type;
    ext::string sub_type;
    ext::map<ext::string, ext::string> parameters;
};

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MIMESNIFF__TYPEDEFS_HPP
