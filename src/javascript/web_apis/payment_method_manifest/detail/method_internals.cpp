#include "method_internals.hpp"

#include INCLUDE_INNER_TYPES(payment_method_id)
#include "url/detail/url_internals.hpp"

#include "payment_method_id/detail/identifier_internals.hpp"

#include <range/v3/view/filter.hpp>
#include <range/v3/view/transform.hpp>


auto payment::detail::ingest_payment_method_manifests(
        ext::vector_span<payment_method_identifier_t> identifiers,
        v8::Local<v8::Object> client)
        -> void
{
    auto manifests_map = fetch_payment_method_manifests(identifiers, client);
    while (manifests_map.pending()) continue;
    return_if (!manifests_map.rejected());

    for (const auto& [identifier_url, response_info]: *(manifests_map.value()))
    {
        auto [response_url, manifest] = response_info;
        auto parsed = validate_and_parse(manifest, *response_url);

        for (decltype(auto) web_app_manifest_url: parsed.default_applications)
        {
            auto web_app_manifest_string = fetch_web_app_manifest_for_default_payment_app(web_app_manifest_url, *identifier_url, client);
            return_if (!web_app_manifest_string.value().has_value());
            auto web_app_manifest = manifest::start_processing_web_app_manifest(std::move(*web_app_manifest_string.value()));
            // TODO
        }

        // TODO
    }
}


auto payment::detail::fetch_payment_method_manifests(
        ext::vector_span<payment_method_identifier_t> identifiers,
        v8::Local<v8::Object> client)
        -> ext::promise<manifest_map_t>
{
    auto identifier_urls = identifiers
            | ranges::views::transform(&url::detail::basic_url_parser)
            | ranges::views::filter(&ext::expected<url::detail::url_t>::has_value)
            | ranges::views::transform(&ext::expected<url::detail::url_t>::operator*)
            | ranges::views::filter(&detail::validate_url_based_payment_method_identifier);

    for (decltype(auto) identifier_url: identifier_urls)
    {
        auto manfifest_url_string = ext::string{};
        // TODO
    }
}


auto payment::detail::validate_and_parse(
        ext::string_view bytes,
        const url::detail::url_t& url)
        -> parsed_payment_method_manifest_t
{
    // TODO
}
