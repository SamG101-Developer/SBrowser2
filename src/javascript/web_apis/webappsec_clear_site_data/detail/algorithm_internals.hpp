#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CLEAR_SITE_DATA_DETAIL_ALGORITHM_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CLEAR_SITE_DATA_DETAIL_ALGORITHM_INTERNALS_HPP

#include "ext/vector.hpp"
#include "ext/span.hpp"
#include INCLUDE_INNER_TYPES(html)
#include INCLUDE_INNER_TYPES(fetch)


namespace webappsec::detail
{
    auto parse_response_clear_site_data_header(
            const fetch::detail::response_t& response)
            -> fetch::detail::header_values_t;

    auto clear_site_data_for_response(
            const fetch::detail::response_t& response)
            -> void;

    auto prepare_to_clear_origins_data(
            const html::detail::origin_t& origin,
            ext::vector_span<ext::string> types)
            -> ext::vector<html::detail::browsing_context_t*>;

    auto reload_browsing_contexts(
            ext::vector_span<html::detail::browsing_context_t*> context)
            -> void;

    auto clear_cache_for_origin(
            const html::detail::origin_t& origin)
            -> void;

    auto clear_cookies_for_origin(
            const html::detail::origin_t& origin)
            -> void;

    auto clear_dom_accessible_storage_for_origin(
            const html::detail::origin_t& origin)
            -> void;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CLEAR_SITE_DATA_DETAIL_ALGORITHM_INTERNALS_HPP
