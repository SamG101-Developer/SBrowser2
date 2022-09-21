#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_SANDBOXING_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_SANDBOXING_INTERNALS_HPP

#include "ext/number.hpp"
#include "ext/string.hpp"
#include INCLUDE_INNER_TYPES(html)
namespace dom::nodes {class element;}


namespace html::detail
{
    auto parse_sandboxing_directive(
            ext::string_view input,
            ext::number<std::underlying_type_t<detail::sandboxing_flag_set_t>>& output)
            -> ext::number<std::underlying_type_t<detail::sandboxing_flag_set_t>>&;

    auto determine_creation_sandboxing_flags(
            const detail::browsing_context_t& browsing_context,
            dom::nodes::element* embedder)
            -> sandboxing_flag_set_t;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_SANDBOXING_INTERNALS_HPP
