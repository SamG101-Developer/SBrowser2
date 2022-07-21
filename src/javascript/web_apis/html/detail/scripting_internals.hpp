#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_SCRIPTING_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_SCRIPTING_INTERNALS_HPP

#include "ext/boolean.hpp"
namespace dom::nodes {class node;}

namespace html::detail::scripting_internals
{
    auto is_scripting_enabled(
            dom::nodes::node* node)
            -> ext::boolean;

    auto is_scripting_disabled(
            dom::nodes::node* node)
            -> ext::boolean;
}


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_SCRIPTING_INTERNALS_HPP
