#pragma once
#ifndef SBROWSER2_REQUEST_HPP
#define SBROWSER2_REQUEST_HPP

#include "mixins/body.hpp"
namespace fetch {class request;}

#include "ext/map.hpp"
#include "ext/variant.hpp"
#include USE_INNER_TYPES(fetch)
namespace dom::abort {class abort_signal;}
namespace fetch {class headers;}


class fetch::request
        : public mixins::body
{
public constructors:
    request(ext::variant<request*, ext::string> input, ext::map<ext::string, ext::any> init = {});

public js_methods:
    auto clone() -> request;

public js_properties: // TODO : constrain attributes
    ext::property<ext::string> method;
    ext::property<ext::string> url;
    ext::property<std::unique_ptr<headers>> headers_;

    ext::property<ext::string> destination;
    ext::property<ext::string> referrer;
    ext::property<ext::string> referrer_policy;
    ext::property<ext::string> mode;
    ext::property<ext::string> credentials;
    ext::property<ext::string> cache;
    ext::property<ext::string> redirect;
    ext::property<ext::string> integrity;
    ext::property<ext::boolean> keepalive;
    ext::property<ext::boolean> is_reload_navigation;
    ext::property<ext::boolean> is_history_navigation;
    ext::property<std::unique_ptr<dom::abort::abort_signal>> signal;

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;

private cpp_methods:
    auto mime_type() -> ext::string;

private cpp_properties:
    std::unique_ptr<detail::request_t> m_request;
};


#endif //SBROWSER2_REQUEST_HPP
