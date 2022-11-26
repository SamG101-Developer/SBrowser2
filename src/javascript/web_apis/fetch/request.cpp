#include "request.hpp"
#include "mixins/body.hpp"
#include "request_private.hpp"

#include "ext/casting.hpp"
#include "ext/variant.hpp"

#include "dom/_typedefs.hpp"
#include "dom/abort/abort_signal.hpp"
#include "dom/abort/abort_signal_private.hpp"
#include "dom/detail/aborting_internals.hpp"
#include "dom/detail/exception_internals.hpp"

#include "html/detail/origin_internals.hpp"

#include "fetch/_typedefs.hpp"
#include "fetch/headers.hpp"
#include "fetch/headers_private.hpp"
#include "fetch/detail/body_internals.hpp"
#include "fetch/detail/header_internals.hpp"
#include "fetch/detail/request_internals.hpp"

#include "referrer_policy/_typedefs.hpp"
#include "url/detail/url_internals.hpp"


fetch::request::request(detail::request_info_t&& input, detail::request_init_t&& init)
{
    INIT_PIMPL(request);
    ACCESS_PIMPL(request);

    using enum v8_primitive_error_t;
    auto e = js::env::env::relevant(this);

    auto fallback_mode = detail::request_mode_t::_;
    auto signal = std::make_unique<dom::abort::abort_signal>();
    auto inner_request = std::make_unique<fetch::detail::request_t>();
    decltype(auto) base_url = *e.cpp.settings()->api_base_url;
    decltype(auto) origin   = *e.cpp.settings()->origin;

    if (ext::holds_alternative<ext::string>(input))
    {
        auto parsed_url = url::detail::url_parser(ext::unsafe_get<1>(input), *base_url);

        dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
                [&parsed_url] {return !parsed_url.has_value();},
                u8"Invalid URL - Parsing failed", e);

        dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
                [&parsed_url] {return url::detail::url_includes_credentials(**parsed_url);},
                u8"Invalid URL - URL must not include credentials", e);

        inner_request->url = std::move(*parsed_url);
        fallback_mode = detail::request_mode_t::CORS;
    }

    else
    {
        ASSERT(ext::holds_alternative<std::unique_ptr<request>>(input));
        inner_request = std::move(ext::get<0>(input)->d_func()->request);
        signal = std::move(ext::get<0>(input)->d_func()->signal);
    }

    auto window = detail::window_t{detail::deferred_window_t::CLIENT};
    if (ext::holds_alternative<v8::Local<v8::Object>>(inner_request->window))
    {
        decltype(auto) request_window = ext::get<2>(inner_request->window);
        decltype(auto) window_origin  = *js::env::env::from_global_object(request_window).cpp.settings()->origin;
        window = html::detail::same_origin(window_origin, origin) ? request_window : window;
    }

    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [&init] {return init.contains(u"window") && !ext::holds_alternative<ext::variant_monostate_t>(init[u"window"].to<detail::window_t>());},
            u8"Init cannot contain an empty 'window' entry", e);

    window = init.contains(u"window") ? detail::deferred_window_t::NO_WINDOW : window;

    d->request = std::make_unique<detail::request_t>();
    d->request->url = inner_request->url;
    d->request->method = inner_request->method;
    d->request->header_list = inner_request->header_list; // Copies
    d->request->unsafe_request_flag = true;
    d->request->client = e.js.settings();
    d->request->window = std::move(window);
    d->request->priority = inner_request->priority;
    d->request->origin = inner_request->origin;
    d->request->referrer = inner_request->referrer; // TODO : ownership (variant contains raw pointer)
    d->request->referrer_policy = inner_request->referrer_policy;
    d->request->mode = inner_request->mode;
    d->request->credentials_mode = inner_request->credentials_mode;
    d->request->cache_mode = inner_request->cache_mode;
    d->request->redirect_mode = inner_request->redirect_mode;
    d->request->integrity_metadata = inner_request->integrity_metadata; // Copies
    d->request->keep_alive = inner_request->keep_alive;
    d->request->reload_navigation_flag = inner_request->reload_navigation_flag;
    d->request->history_navigation_flag = inner_request->history_navigation_flag;
    d->request->url_list = inner_request->url_list; // Copies / clones
    d->request->initiator_type = detail::request_initiator_t::FETCH;

    if (!init.empty())
    {
        inner_request->mode = inner_request->mode == detail::request_mode_t::NAVIGATE
                ? detail::request_mode_t::SAME_ORIGIN
                : inner_request->mode;

        inner_request->reload_navigation_flag = false;
        inner_request->history_navigation_flag = false;
        inner_request->origin = u"client";
        inner_request->referrer = detail::referrer_t::CLIENT;
        inner_request->referrer_policy = referrer_policy::detail::referrer_policy_t::_;
        inner_request->url.reset(&inner_request->current_url()); // TODO
        inner_request->url_list = {inner_request->url.get()};
    }

    // TODO
}


auto fetch::request::clone() -> std::unique_ptr<request>
{
    ACCESS_PIMPL(const request);
    using enum v8_primitive_error_t;
    auto e = js::env::env::relevant(this);

    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [this] {return detail::is_unusable(this);},
            u8"This Request (-> Body) must be usable", e);

    auto cloned_request = detail::clone_request(*d->request);
    auto cloned_request_object = detail::create_request_object(std::move(cloned_request), d->headers->d_func()->headers_guard);
    dom::detail::follow_signal(cloned_request_object->d_func()->signal.get(), d->signal.get());
    return cloned_request_object;
}


auto fetch::request::get_method() const -> detail::method_t
{
    ACCESS_PIMPL(const request);
    return d->request->method;
}


auto fetch::request::get_url() const -> ext::string
{
    ACCESS_PIMPL(const request);
    return url::detail::url_serializer(*d->request->url);
}


auto fetch::request::get_headers() const -> headers*
{
    ACCESS_PIMPL(const request);
    return d->headers.get();
}


auto fetch::request::get_destination() const -> detail::request_destination_t
{
    ACCESS_PIMPL(const request);
    return d->request->destination;
}


auto fetch::request::get_referrer() const -> ext::string
{
    ACCESS_PIMPL(const request);
    return_if (ext::get_and_equals(d->request->referrer, detail::referrer_t::NO_REFERRER)) u"";
    return_if (ext::get_and_equals(d->request->referrer, detail::referrer_t::CLIENT)) u"abort:client";
    return url::detail::url_serializer(*ext::unsafe_get<1>(d->request->referrer));
}


auto fetch::request::get_referrer_policy() const -> referrer_policy::detail::referrer_policy_t
{
    ACCESS_PIMPL(const request);
    return d->request->referrer_policy;
}


auto fetch::request::get_mode() const -> detail::request_mode_t
{
    ACCESS_PIMPL(const request);
    return d->request->mode;
}


auto fetch::request::get_credentials() const -> detail::request_credentials_t
{
    ACCESS_PIMPL(const request);
    return d->request->credentials_mode;
}


auto fetch::request::get_cache() const -> detail::request_cache_t
{
    ACCESS_PIMPL(const request);
    return d->request->cache_mode;
}


auto fetch::request::get_redirect() const -> detail::request_redirect_t
{
    ACCESS_PIMPL(const request);
    return d->request->redirect_mode;
}


auto fetch::request::get_integrity() const -> ext::string_view
{
    ACCESS_PIMPL(const request);
    return d->request->integrity_metadata;
}


auto fetch::request::get_keepalive() const -> ext::boolean
{
    ACCESS_PIMPL(const request);
    return d->request->keep_alive;
}


auto fetch::request::get_is_reload_navigation() const -> ext::boolean
{
    ACCESS_PIMPL(const request);
    return d->request->reload_navigation_flag;
}


auto fetch::request::get_is_history_navigation() const -> ext::boolean
{
    ACCESS_PIMPL(const request);
    return d->request->history_navigation_flag;
}


auto fetch::request::get_signal() const -> dom::abort::abort_signal*
{
    ACCESS_PIMPL(const request);
    return d->signal.get();
}


auto fetch::request::get_duplex() const -> detail::request_duplex_t
{
    ACCESS_PIMPL(const request);
    return detail::request_duplex_t::HALF;
}


auto fetch::request::_to_v8(js::env::module_t E, v8::Isolate* isolate) -> ext::tuple<bool, v8pp::class_<self_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<dom_object>()
        .inherit<mixins::body>()
        .ctor<detail::request_info_t&&, detail::request_init_t&&>()
        .function("clone", &request::clone)
        .property("method", &request::get_method)
        .property("URL", &request::get_url)
        .property("headers", &request::get_headers)
        .property("destination", &request::get_destination)
        .property("referrer", &request::get_referrer)
        .property("referrerPolicy", &request::get_referrer_policy)
        .property("mode", &request::get_mode)
        .property("credentials", &request::get_credentials)
        .property("cache", &request::get_cache)
        .property("redirect", &request::get_redirect)
        .property("integrity", &request::get_integrity)
        .property("keepalive", &request::get_keepalive)
        .property("isReloadNavigation", &request::get_is_reload_navigation)
        .property("isHistoryNavigation", &request::get_is_history_navigation)
        .property("signal", &request::get_signal)
        .property("duplex", &request::get_duplex)
        .auto_wrap_objects();

    V8_INTEROP_SUCCESSFUL_CONVERSION;
}
