module;
#include "ext/macros.hpp"


export module apis.fetch.request;
import apis.dom_object;
import apis.fetch.mixins.body;

import apis.fetch.types;
import apis.dom.types;
import apis.referrer_policy.types;


DEFINE_PUBLIC_CLASS(fetch, request) final
        : virtual public dom_object
        , public mixins::body
{
public constructors:
    request(detail::request_info_t&& input, detail::request_init_t&& init = {});
    MAKE_PIMPL(request);
    MAKE_V8_AVAILABLE(WINDOW | WORKER);

private js_methods:
    auto clone() -> std::unique_ptr<request>;

private js_properties:
    DEFINE_GETTER(method, detail::method_t);
    DEFINE_GETTER(url, ext::string);
    DEFINE_GETTER(headers, headers*);

    DEFINE_GETTER(destination, detail::request_destination_t);
    DEFINE_GETTER(referrer, ext::string);
    DEFINE_GETTER(referrer_policy, referrer_policy::detail::referrer_policy_t);
    DEFINE_GETTER(mode, detail::request_mode_t);
    DEFINE_GETTER(credentials, detail::request_credentials_t);
    DEFINE_GETTER(cache, detail::request_cache_t);
    DEFINE_GETTER(redirect, detail::request_redirect_t);
    DEFINE_GETTER(integrity, ext::string_view);
    DEFINE_GETTER(keepalive, ext::boolean);
    DEFINE_GETTER(is_reload_navigation, ext::boolean);
    DEFINE_GETTER(is_history_navigation, ext::boolean);
    DEFINE_GETTER(signal, dom::abort_signal*);
    DEFINE_GETTER(duplex, detail::request_duplex_t);
};
