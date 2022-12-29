module;
#include "ext/macros/annotations.hpp"
#include "ext/macros/other.hpp"
#include "ext/macros/macros.hpp"
#include "ext/macros/property.hpp"
#include "javascript/macros/expose.hpp"


export module apis.url.url;
import apis.dom_object;

import apis.file_api.types;
import apis.url.types;
import ext.core;
import js.env.module_type;


DEFINE_PUBLIC_CLASS(url, url) final
        : virtual public dom_object
{
public constructors:
    url(ext::string_view url_string = u"", ext::string_view base = u"");
    MAKE_PIMPL(url);
    MAKE_STRINGIFIER;
    MAKE_V8_AVAILABLE(ALL);

    operator bool() const;
    auto operator!() const -> ext::boolean;

public js_methods:
    /* [FILE-API] */
    static auto create_object_url(file_api::blob* blob) -> ext::string;
    static auto revoke_object_url(ext::string_view url);
    
private js_properties:
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
    DEFINE_GETTER(origin, ext::string);
    DEFINE_GETTER(search_params, url_search_params*);

    DEFINE_SETTER(href, ext::string);
    DEFINE_SETTER(protocol, ext::string);
    DEFINE_SETTER(username, ext::string);
    DEFINE_SETTER(password, ext::string);
    DEFINE_SETTER(host, ext::string);
    DEFINE_SETTER(hostname, ext::string);
    DEFINE_SETTER(port, ext::string);
    DEFINE_SETTER(pathname, ext::string);
    DEFINE_SETTER(search, ext::string);
    DEFINE_SETTER(hash, ext::string);
};
