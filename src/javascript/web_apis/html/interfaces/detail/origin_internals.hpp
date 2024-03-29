#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_ORIGIN_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_ORIGIN_INTERNALS_HPP


#include "ext/expected.ixx"

#include INCLUDE_INNER_TYPES(html)
#include INCLUDE_INNER_TYPES(url)


namespace html::detail
{
    auto effective_domain(
            const origin_t& origin)
            -> ext::expected<url::detail::url_t>;

    auto serialize_origin(
            const origin_t& origin)
            -> ext::string;

    auto same_origin(
            const origin_t& origin_a,
            const origin_t& origin_b)
            -> ext::boolean;

    auto same_origin_domain(
            const origin_t& origin_a,
            const origin_t& origin_b)
            -> ext::boolean;

    auto same_site(
            const origin_t& origin_a,
            const origin_t& origin_b)
            -> ext::boolean;

    auto obtain_site(
            const origin_t& origin)
            -> site_t;

    auto serialize_site(
            const site_t& site)
            -> ext::string;

    auto is_registerable_domain_suffix_or_equal_to(
            ext::string_view host_suffix_string,
            ext::string_view original_host)
            -> ext::boolean;
    
    auto is_opaque_origin(
            const origin_t& origin)
            -> ext::boolean;
}




#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_ORIGIN_INTERNALS_HPP
