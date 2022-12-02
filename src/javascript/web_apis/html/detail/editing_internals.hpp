#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_EDITING_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_EDITING_INTERNALS_HPP

#include "ext/boolean.ixx"
namespace dom::nodes {class node;}


namespace html::detail
{
    auto is_editing_host(
            const dom::nodes::node* node)
            -> ext::boolean;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_EDITING_INTERNALS_HPP
