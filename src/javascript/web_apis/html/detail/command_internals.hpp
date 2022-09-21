#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_COMMAND_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_COMMAND_INTERNALS_HPP

#include "ext/keywords.hpp"
#include INCLUDE_INNER_TYPES(html)

namespace html::elements {class html_element;}


namespace html::detail
{
    auto should_expose_command_faucet(
            const html::detail::command_facet_t& command)
            -> ext::boolean;

    auto define_command(
            html::elements::html_element* element)
            -> command_facet_t;
};


struct html::detail::command_facet_t
{
    ext::string label;
    ext::string access_key;
    ext::boolean hidden_state;
    ext::boolean disabled_tate;
    ext::function<void()> action;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_COMMAND_INTERNALS_HPP
