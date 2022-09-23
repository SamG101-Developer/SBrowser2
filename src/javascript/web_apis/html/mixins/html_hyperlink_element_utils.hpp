#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_MIXINS_HTML_HYPERLINK_ELEMENT_UTILS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_MIXINS_HTML_HYPERLINK_ELEMENT_UTILS_HPP

#include "dom_object.hpp"
namespace html::mixins {class html_hyperlink_element_utils;}

#include INCLUDE_INNER_TYPES(url)

class html::mixins::html_hyperlink_element_utils
        : public virtual dom_object
{
public constructors:
    html_hyperlink_element_utils();

private js_properties:
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

private js_properties:
    DEFINE_CUSTOM_GETTER(origin);
    DEFINE_CUSTOM_GETTER(href);
    DEFINE_CUSTOM_GETTER(protocol);
    DEFINE_CUSTOM_GETTER(username);
    DEFINE_CUSTOM_GETTER(password);
    DEFINE_CUSTOM_GETTER(host);
    DEFINE_CUSTOM_GETTER(hostname);
    DEFINE_CUSTOM_GETTER(port);
    DEFINE_CUSTOM_GETTER(pathname);
    DEFINE_CUSTOM_GETTER(search);
    DEFINE_CUSTOM_GETTER(hash);

    DEFINE_CUSTOM_SETTER(href);
    DEFINE_CUSTOM_SETTER(protocol);
    DEFINE_CUSTOM_SETTER(username);
    DEFINE_CUSTOM_SETTER(password);
    DEFINE_CUSTOM_SETTER(host);
    DEFINE_CUSTOM_SETTER(hostname);
    DEFINE_CUSTOM_SETTER(port);
    DEFINE_CUSTOM_SETTER(pathname);
    DEFINE_CUSTOM_SETTER(search);
    DEFINE_CUSTOM_SETTER(hash);

    DEFINE_CUSTOM_DELETER(href);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_MIXINS_HTML_HYPERLINK_ELEMENT_UTILS_HPP
