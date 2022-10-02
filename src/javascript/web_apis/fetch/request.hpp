#pragma once
#ifndef SBROWSER2_REQUEST_HPP
#define SBROWSER2_REQUEST_HPP

#include "mixins/body.hpp"
namespace fetch {class request;}

#include "ext/map.hpp"
#include "ext/variant.hpp"
#include INCLUDE_INNER_TYPES(fetch)
namespace dom::abort {class abort_signal;}
namespace fetch {class headers;}


class fetch::request
        : public mixins::body
{
public constructors:
    request(ext::variant<request*, ext::string> input, ext::map<ext::string, ext::any> init = {});
    ~request() override = default;

public js_methods:
    auto clone() -> request;

private js_properties: // TODO : constrain attributes
    DEFINE_GETTER(method, ext::string);
    DEFINE_GETTER(url, ext::string);
    DEFINE_GETTER(headers, detail::headers_t); // TODO : view

    DEFINE_GETTER(destination, ext::string);
    DEFINE_GETTER(referrer, ext::string);
    DEFINE_GETTER(referrer_policy, ext::string);
    DEFINE_GETTER(mode, ext::string);
    DEFINE_GETTER(credentials, ext::string);
    DEFINE_GETTER(cache, ext::string);
    DEFINE_GETTER(redirect, ext::string);
    DEFINE_GETTER(integrity, ext::string);
    DEFINE_GETTER(keepalive, ext::boolean);
    DEFINE_GETTER(is_reload_navigation, ext::boolean);
    DEFINE_GETTER(is_history_navigation, ext::boolean);
    DEFINE_GETTER(signal, dom::abort::abort_signal*);
//
//private cpp_methods:
//    auto mime_type() -> ext::string;
//
//private cpp_properties:
//    std::unique_ptr<detail::request_t> m_request;
};


#endif //SBROWSER2_REQUEST_HPP
