#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_METHOD_MANIFEST_DETAIL_METHOD_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_METHOD_MANIFEST_DETAIL_METHOD_INTERNALS_HPP


#include "ext/span.hpp"
#include <v8-forward.h>
#include INCLUDE_INNER_TYPES(payment_method_id)
#include INCLUDE_INNER_TYPES(payment_method_manifest)
#include INCLUDE_INNER_TYPES(url)

namespace payment::detail
{
    auto ingest_payment_method_manifests(
            ext::vector_span<payment_method_identifier_t> identifiers,
            v8::Local<v8::Object> client)
            -> void;

    auto fetch_payment_method_manifests(
            ext::vector_span<payment_method_identifier_t> identifiers,
            v8::Local<v8::Object> client)
            -> ext::promise<manifest_map_t>;

    auto validate_and_parse(
            ext::string_view bytes,
            const url::detail::url_t& url)
            -> parsed_payment_method_manifest_t;

    auto fetch_web_app_manifest_for_default_payment_app(
            const url::detail::url_t& url,
            const url::detail::url_t& referrer,
            v8::Local<v8::Object> client)
            -> ext::promise<ext::expected<ext::string>>;
}


struct payment::detail::parsed_payment_method_manifest_t
{
    ext::vector<url::detail::url_t> default_applications;
    ext::vector<html::detail::origin_t> supported_origins;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_METHOD_MANIFEST_DETAIL_METHOD_INTERNALS_HPP
