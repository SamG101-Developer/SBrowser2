#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSSOM__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSSOM__TYPEDEFS_HPP

#include "ext/any.hpp"
#include "ext/map.hpp"
#include "ext/string.hpp"


namespace css::detail
{
    struct css_rule_t;
    struct css_style_sheet_t;
    struct css_declaration_t;
    struct css_declaration_block_t;

    using css_style_sheet_init_t = ext::map<ext::string, ext::any>;
}


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSSOM__TYPEDEFS_HPP
