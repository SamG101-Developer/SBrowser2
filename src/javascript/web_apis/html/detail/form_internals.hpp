#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_FORM_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_FORM_INTERNALS_HPP

#include "ext/string.hpp"
#include "ext/vector.hpp"

namespace dom::nodes {class node;}


namespace html::detail
{
    auto supported_property_names()
            -> ext::vector<ext::string>;

    auto determine_value_of_named_property(
            ext::string_view name)
            -> dom::nodes::node*;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_FORM_INTERNALS_HPP
