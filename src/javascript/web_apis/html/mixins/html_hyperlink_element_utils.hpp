#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_MIXINS_HTML_HYPERLINK_ELEMENT_UTILS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_MIXINS_HTML_HYPERLINK_ELEMENT_UTILS_HPP

#include "dom_object.hpp"
namespace html::mixins {class html_hyperlink_element_utils;}

#include USE_INNER_TYPES(url)

class html::mixins::html_hyperlink_element_utils
        : public virtual dom_object
{
public constructors:
    html_hyperlink_element_utils();

public js_properties:
    ext::property<ext::string> origin;
    ext::property<ext::string> href;
    ext::property<ext::string> protocol;
    ext::property<ext::string> username;
    ext::property<ext::string> password;
    ext::property<ext::string> host;
    ext::property<ext::string> hostname;
    ext::property<ext::string> port;
    ext::property<ext::string> pathname;
    ext::property<ext::string> search;
    ext::property<ext::string> hash;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;
    auto to_json() const -> ext::string override {return href();};

private cpp_properties:
    url::detail::url_t m_url;

private cpp_accessors:
    DEFINE_GETTER(origin);
    DEFINE_GETTER(href);
    DEFINE_GETTER(protocol);
    DEFINE_GETTER(username);
    DEFINE_GETTER(password);
    DEFINE_GETTER(host);
    DEFINE_GETTER(hostname);
    DEFINE_GETTER(port);
    DEFINE_GETTER(pathname);
    DEFINE_GETTER(search);
    DEFINE_GETTER(hash);

    DEFINE_SETTER(href);
    DEFINE_SETTER(protocol);
    DEFINE_SETTER(username);
    DEFINE_SETTER(password);
    DEFINE_SETTER(host);
    DEFINE_SETTER(hostname);
    DEFINE_SETTER(port);
    DEFINE_SETTER(pathname);
    DEFINE_SETTER(search);
    DEFINE_SETTER(hash);

    DEFINE_DELETER(href);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_MIXINS_HTML_HYPERLINK_ELEMENT_UTILS_HPP
