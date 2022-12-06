#include "request_internals.hpp"




#include "ext/enums.ixx"


#include "dom/nodes/window.hpp"
#include "dom/nodes/window_private.hpp"

#include "fetch/_typedefs.hpp"
#include "fetch/detail/body_internals.hpp"
#include "fetch/headers.hpp"
#include "fetch/headers_private.hpp"
#include "fetch/request.hpp"
#include "fetch/request_private.hpp"

#include "html/_typedefs.hpp"
#include "html/detail/origin_internals.hpp"
#include "html/detail/policy_internals.hpp"

#include "url/detail/url_internals.hpp"


auto fetch::detail::is_subresource_request(const request_t& request) -> ext::boolean
{
    using enum request_destination_t;
    auto subresource_destinations = AUDIO | AUDIOWORKLET | FONT | IMAGE | MANIFEST | PAINTWORKLET | SCRIPT | STYLE | TRACK | VIDEO | XSLT | _;
    return request.destination & subresource_destinations;
}


auto fetch::detail::is_non_subresource_request(const request_t& request) -> ext::boolean
{
    using enum request_destination_t;
    auto non_subresurce_destinations = DOCUMENT | EMBED | FRAME | IFRAME | OBJECT | REPORT | SERVICEWORKER | SHAREDWORKER | WORKER;
    return request.destination & non_subresurce_destinations;
}


auto fetch::detail::is_navigation_request(const request_t& request) -> ext::boolean
{
    using enum request_destination_t;
    auto navigation_destinations = DOCUMENT | EMBED | FRAME | IFRAME | OBJECT;
    return request.destination & navigation_destinations;
}


auto fetch::detail::has_redirect_tainted_origin(const request_t& request) -> ext::boolean
{
    decltype(auto) last_url = ext::nullptr_cast<url::detail::url_t*>();
    for (decltype(auto) current_url: request.url_list) // TODO : find nicer way with ranges-v3
    {
        if (!last_url)
            last_url = current_url;
        else
        {
            return_if (!html::detail::same_origin(*url::detail::origin(*current_url), *url::detail::origin(*last_url))
                    && !html::detail::same_origin(request.origin, url::detail::origin(*last_url))) true;
            last_url = current_url;
        }
    }

    return false;
}


auto fetch::detail::serialize_request_origin(const request_t& request) -> ext::string
{
    return has_redirect_tainted_origin(request) ? u"" : html::detail::serialize_origin(request.origin);
}


auto fetch::detail::byte_serializing_request_origin(const request_t& request) -> ext::string
{
    return infra::isomporphic_encode(serialize_request_origin(request));
}


auto fetch::detail::clone_request(const request_t& request) -> std::unique_ptr<request_t>
{
    auto new_request = std::make_unique<request_t>(request);
    request->body = clone_body(*request.body);
    return new_request;
}


auto fetch::detail::add_range_header_to_request(
        request_t& request,
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
        const request_t& request)
        -> ext::boolean
{
    auto e = js::env::env::from_global_object(request.client);

    return request.mode == mode_t::NO_CORS
            || !e.cpp.settings()
            || e.cpp.settings()->policy_container->embedder_policy->value != html::detail::embedder_policy_value_t::CREDENTIALLESS
            || html::detail::same_origin(request.current_url()->d_func()->origin) && !has_redirect_tainted_origin(request);
}


auto fetch::detail::create_request_object(
        std::unique_ptr<request_t>&& inner_request,
        fetch::detail::header_guard_t header_guard)
        -> std::unique_ptr<request>
{
    auto request_object = std::make_unique<request>();
    request_object->d_func()->request = std::move(inner_request);
    request_object->d_func()->headers = std::make_unique<headers>(inner_request->header_list);
    request_object->d_func()->signal = std::make_unique<dom::abort::abort_signal>();
    return request_object;
}
