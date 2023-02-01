#pragma once
#ifndef SBROWSER2_DIRECTIVE_INTERNALS_HPP
#define SBROWSER2_DIRECTIVE_INTERNALS_HPP



#include "ext/vector.hpp"
#include INCLUDE_INNER_TYPES(fetch)
#include INCLUDE_INNER_TYPES(html)
#include INCLUDE_INNER_TYPES(webappsec)
#include INCLUDE_INNER_TYPES(webappsec_csp)
namespace dom::nodes {class document;}
namespace dom::nodes {class element;}


namespace webappsec::detail
{


    auto effective_directive_for_request(
            const fetch::detail::request_t& request)
            -> ext::string;

    auto get_effective_directive_inline_checks(
            ext::string_view type)
            -> ext::string;
    
    auto get_fetch_directive_fallback_list(
            ext::string_view directive_name)
            -> ext::vector<ext::string>;
    
    auto should_fetch_directive_execute(
            ext::string_view effective_directive_name,
            ext::string_view directive_name,
            const policy_t& csp)
            -> ext::boolean;
}


#endif //SBROWSER2_DIRECTIVE_INTERNALS_HPP
