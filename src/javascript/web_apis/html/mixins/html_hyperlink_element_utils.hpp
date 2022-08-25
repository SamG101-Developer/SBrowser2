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
    ext::property<ext::string, false> origin;
    ext::property<ext::string, true> href;
    ext::property<ext::string, true> protocol;
    ext::property<ext::string, true> username;
    ext::property<ext::string, true> password;
    ext::property<ext::string, true> host;
    ext::property<ext::string, true> hostname;
    ext::property<ext::string, true> port;
    ext::property<ext::string, true> pathname;
    ext::property<ext::string, true> search;
    ext::property<ext::string, true> hash;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;
    auto to_json() const -> ext::string override {return href();};

private cpp_properties:
    url::url_object m_url;

private cpp_accessors:
    auto get_origin() const -> ext::string;
    auto get_href() const -> ext::string;
    auto get_protocol() const -> ext::string;
    auto get_username() const -> ext::string;
    auto get_password() const -> ext::string;
    auto get_host() const -> ext::string;
    auto get_hostname() const -> ext::string;
    auto get_port() const -> ext::string;
    auto get_pathname() const -> ext::string;
    auto get_search() const -> ext::string;
    auto get_hash() const -> ext::string;

    auto set_href(ext::string_view val) -> void;
    auto set_protocol(ext::string_view val) -> void;
    auto set_username(ext::string_view val) -> void;
    auto set_password(ext::string_view val) -> void;
    auto set_host(ext::string_view val) -> void;
    auto set_hostname(ext::string_view val) -> void;
    auto set_port(ext::string_view val) -> void;
    auto set_pathname(ext::string_view val) -> void;
    auto set_search(ext::string_view val) -> void;
    auto set_hash(ext::string_view val) -> void;

    auto del_href() -> void;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_MIXINS_HTML_HYPERLINK_ELEMENT_UTILS_HPP
