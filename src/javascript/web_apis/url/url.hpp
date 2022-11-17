#ifndef SBROWSER2_URL_HPP
#define SBROWSER2_URL_HPP

#include "dom_object.hpp"
namespace url {class url;}
namespace url {class url_private;}

#include INCLUDE_INNER_TYPES(url)
namespace file_api {class blob;}
namespace url {class url_search_params;}


class url::url
        : virtual public dom_object
{
public constructors:
    url(ext::string_view url_string = u"", ext::string_view base = u"");
    MAKE_PIMPL(url);
    MAKE_STRINGIFIER;
    MAKE_V8_AVAILABLE;

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


#endif //SBROWSER2_URL_HPP
