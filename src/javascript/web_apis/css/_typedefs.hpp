#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS__TYPEDEFS_HPP

#include "ext/concepts.hpp"

#include INCLUDE_INNER_TYPES(css/css_web_animations)


namespace css::detail
{
    enum class percent_t {NA};
    enum class computed_value_t {SPECIFIED_KEYWORDS};
    enum class canonical_order_t {PER_GRAMMAR};

    struct abstract_property_t;
}


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS__TYPEDEFS_HPP
