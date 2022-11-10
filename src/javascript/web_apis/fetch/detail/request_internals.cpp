#include "request_internals.hpp"

#include "html/_typedefs.hpp"
#include "javascript/environment/realms.hpp"

#include "ext/casting.hpp"
#include "ext/enums.hpp"

#include "dom/nodes/window.hpp"
#include "dom/nodes/window_private.hpp"

#include "fetch/_typedefs.hpp"
#include "fetch/detail/body_internals.hpp"

#include "html/detail/policy_internals.hpp"
#include "url/detail/url_internals.hpp"


auto fetch::detail::is_subresource_request(const fetch::detail::request_t& request) -> ext::boolean
{
    return request.destination & (destination_t::AUDIO | destination_t::AUDIOWORKLET | destination_t::FONT
            | destination_t::IMAGE | destination_t::MANIFEST | destination_t::PAINTWORKLET | destination_t::SCRIPT
            | destination_t::STYLE | destination_t::TRACK | destination_t::VIDEO | destination_t::XSLT
            | destination_t::_);
}


auto fetch::detail::is_non_subresource_request(const fetch::detail::request_t& request) -> ext::boolean
{
    return request.destination & (destination_t::DOCUMENT | destination_t::EMBED | destination_t::FRAME
            | destination_t::IFRAME | destination_t::OBJECT | destination_t::REPORT | destination_t::SERVICEWORKER
            | destination_t::SHAREDWORKER | destination_t::WORKER);
}


auto fetch::detail::is_navigation_request(const fetch::detail::request_t& request) -> ext::boolean
{
    return request.destination & (destination_t::DOCUMENT | destination_t::EMBED | destination_t::FRAME
            | destination_t::IFRAME | destination_t::OBJECT);
}


auto fetch::detail::has_redirect_tainted_origin(const fetch::detail::request_t& request) -> ext::boolean
{
    decltype(auto) last_url = ext::nullptr_cast<url::detail::url_t*>();
    for (decltype(auto) current_url: request.url_list) // TODO : find nicer way with ranges-v3
    {
        if (!last_url)
            last_url = current_url;
        else
        {
            return_if (!url::detail::same_origin(url::detail::origin(*current_url), url::detail::origin(*last_url))
                    && !url::detail::same_origin(request.origin, url::detail::origin(*last_url))) true;
            last_url = current_url;
        }
    }

    return false;
}


auto fetch::detail::serialize_request_origin(const fetch::detail::request_t& request) -> ext::string
{
    return has_redirect_tainted_origin(request) ? u"" : html::detail::serialize_origin(request.origin);
}


auto fetch::detail::byte_serializing_request_origin(const fetch::detail::request_t& request) -> ext::string
{
    return infra::isomporphic_encode(serialize_request_origin(request));
}


auto fetch::detail::clone_request(const fetch::detail::request_t& request) -> request_t
{
    auto new_request = request_t
            {
        .method = request.method,
        .url = request.url,
        .local_urls_only_flag = request.local_urls_only_flag,
        .unsafe_request_flag = request.unsafe_request_flag,
        .header_list = request.header_list,
        .body = clone_body(*request.body),
        .client = request.client,
        .reserved_client = request.reserved_client,
        .window = request.window,
        .replaces_client = request.replaces_client,
        .keep_alive = request.keep_alive,
        .initiator_type = request.initiator_type,
        .service_workers_mode = request.service_workers_mode,
        .initiator = request.initiator,
        .destination = request.destination,
        .priority = request.priority,
        .origin = request.origin,
        .policy_container = request.policy_container,
        .referrer = request.referrer,
        .referrer_policy = request.referrer_policy,
        .mode = request.mode,
        .credentials_mode = request.credentials_mode,
        .cache_mode = request.cache_mode,
        .redirect_mode = request.redirect_mode,
        .use_cors_preflight_flag = request.use_cors_preflight_flag,
        .use_url_credentials_flag = request.use_url_credentials_flag,
        .integrity_metadata = request.integrity_metadata,
        .cryptographic_nonce_metadata = request.cryptographic_nonce_metadata,
        .parser_metadata = request.parser_metadata,
        .reload_navigation_flag = request.reload_navigation_flag,
        .history_navigation_flag = request.history_navigation_flag,
        .user_activation = request.user_activation,
        .render_blocking = request.render_blocking,
        .url_list = request.url_list,
        .redirect_count = request.redirect_count,
        .response_tainting = request.response_tainting,
        .prevent_no_cache_cache_control_header_modification_flag = request.prevent_no_cache_cache_control_header_modification_flag,
        .done_flag = request.done_flag,
        .timing_allow_failed_flag = request.timing_allow_failed_flag
            };
}


auto fetch::detail::add_range_header_to_request(
        fetch::detail::request_t& request,
        ext::number<int> first,
        ext::number<int> last)
        -> void
{
    ASSERT(last == -1 || first < last);
    using namespace ext::literals;

    auto range_value = u"bytes="_s16;
    range_value += infra::detail::isomorphic_encode(ext::to_string(first));
    range_value += char8_t(0x2d);
    range_value += (last != -1) ? infra::detail::isomorphic_encode(ext::to_string(first)) : u"";
    request.header_list.emplace_back(ext::make_pair(u"Range"_s16, std::move(range_value)));
}


auto fetch::detail::check_if_cross_origin_embedder_policy_allows_credentials(
        const fetch::detail::request_t& request)
        -> ext::boolean
{
    auto e = js::env::env::from_global_object(request.client);

    return request.mode == mode_t::NO_CORS
            || !e.cpp.settings()
            || e.cpp.settings()->policy_container->embedder_policy->value != html::detail::embedder_policy_value_t::CREDENTIALLESS
            || html::detail::same_origin(request.current_url()->d_func()->origin) && !has_redirect_tainted_origin(request);
}
