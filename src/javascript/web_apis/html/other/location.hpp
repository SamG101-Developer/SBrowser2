#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_OTHER_LOCATION_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_OTHER_LOCATION_HPP

#include "dom_object.hpp"
namespace html::other {class location;}
namespace html::other {class location_private;}


class html::other::location
        : public virtual dom_object
{
public constructors:
    location();
    MAKE_PIMPL(location);
    MAKE_V8_AVAILABLE;

public js_methods:
    auto assgin(ext::string&& url) -> void;
    auto replace(ext::string&& url) -> void;
    auto reload() -> void;

public js_properties:
    DEFINE_GETTER(origin, ext::string);
    DEFINE_GETTER(href, ext::string);
    DEFINE_GETTER(protocol, ext::string);
    DEFINE_GETTER(username, ext::string);
    DEFINE_GETTER(password, ext::string);
    DEFINE_GETTER(host, ext::string);
    DEFINE_GETTER(hostname, ext::string);
    DEFINE_GETTER(port, ext::string);
    DEFINE_GETTER(pathname, ext::string);
    DEFINE_GETTER(search, ext::string);
    DEFINE_GETTER(hash, ext::string);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_OTHER_LOCATION_HPP
