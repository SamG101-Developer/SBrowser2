#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_MIXED_CONTENT_DETAIL_ALGORITHM_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_MIXED_CONTENT_DETAIL_ALGORITHM_INTERNALS_HPP

#include "ext/boolean.hpp"
#include INCLUDE_INNER_TYPES(fetch)
#include INCLUDE_INNER_TYPES(url)
namespace js::env {class env;}
namespace dom::nodes {class document;}


namespace webappsec::detail
{
    auto is_mixed_content(
            const fetch::detail::request_t& request)
            -> ext::boolean;

    auto is_mixed_content(
            const fetch::detail::response_t& response)
            -> ext::boolean;

    auto is_unauthenticated_response(
            const fetch::detail::response_t& response)
            -> ext::boolean;

    auto os_embedding_document(
            dom::nodes::document* document)
            -> ext::boolean;

    template <typename T>
    auto is_mixed_download(
            T&&)
            -> ext::boolean; // TODO

    auto is_priori_authenticated_url(
            const url::detail::url_t& url)
            -> ext::boolean;

    auto upgrade_mixed_content_request_to_potentially_trustworthy_url_if_appropriate(
            const fetch::detail::request_t& request)
            -> void;

    auto does_settings_prhibit_mixed_security_contexts(
            v8::Local<v8::Object> settings)
            -> ext::boolean;

    auto should_request_be_blocked_as_mixed_content(
            const fetch::detail::request_t& request)
            -> ext::boolean;

    auto should_response_to_request_be_blocked_as_mixed_content(
            const fetch::detail::request_t& request,
            const fetch::detail::response_t& response)
            -> ext::boolean;
}


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_MIXED_CONTENT_DETAIL_ALGORITHM_INTERNALS_HPP
