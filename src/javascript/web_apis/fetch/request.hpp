#pragma once
#ifndef SBROWSER2_REQUEST_HPP
#define SBROWSER2_REQUEST_HPP

#include "dom_object.hpp"
#include "mixins/body.hpp"
namespace fetch {class request;}
namespace fetch {class request_private;}

#include "ext/map.hpp"
#include "ext/variant.hpp"
#include INCLUDE_INNER_TYPES(fetch)
#include INCLUDE_INNER_TYPES(referrer_policy)
namespace dom::abort {class abort_signal;}
namespace fetch {class headers;}


class fetch::request
        : virtual public dom_object
        , public mixins::body
{
public constructors:
    request(detail::request_info_t&& input, ext::map<ext::string, ext::any> init = {});
    MAKE_PIMPL(request);
    MAKE_V8_AVAILABLE(WINDOW | WORKER);

private constructors:
    request();

public js_methods:
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
    DEFINE_GETTER(signal, dom::abort::abort_signal*);
    DEFINE_GETTER(duplex, detail::request_duplex_t);
};


#endif //SBROWSER2_REQUEST_HPP
