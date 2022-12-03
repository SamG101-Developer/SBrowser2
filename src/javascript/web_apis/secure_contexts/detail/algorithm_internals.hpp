#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SECURE_CONTEXTS_DETAIL_ALGORITHM_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SECURE_CONTEXTS_DETAIL_ALGORITHM_INTERNALS_HPP

#include "ext/keywords.ixx"
#include INCLUDE_INNER_TYPES(html)
#include INCLUDE_INNER_TYPES(secure_contexts)
#include INCLUDE_INNER_TYPES(url)


namespace secure_contexts::detail
{
    auto is_origin_potentially_trustworthy(
            const html::detail::origin_t& origin)
            -> trust_type_t;

    auto is_url_potentially_trustworthy(
            const url::detail::url_t& url)
            -> trust_type_t;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SECURE_CONTEXTS_DETAIL_ALGORITHM_INTERNALS_HPP
