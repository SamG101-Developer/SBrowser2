#ifndef SBROWSER2_URL_HPP
#define SBROWSER2_URL_HPP

#include "dom_object.hpp"
namespace url {class url_object;}


class url::url_object
        : public virtual dom_object
{
public constructors:
    url_object(ext::string_view url_string = "");

public js_methods:
    /* FILE_API */
    static auto create_object_url(blob& blob_object) -> ext::string;
    static auto revoke_object_url(ext::string_view url);

public js_properties:
    ext::property<ext::string> scheme;
    ext::property<ext::string> username;
    ext::property<ext::string> password;
    ext::property<ext::string> host;
    ext::property<ext::string> port;

public cpp_operators:
    auto operator=(ext::string_view url) -> url_object&;
    operator bool() const {return !m_url.empty();}
    auto operator!() const -> ext::boolean {return m_url.empty();}
    auto operator==(const url::url_object& other) const -> ext::boolean;

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;
    auto is_opaque() const -> ext::boolean; // TODO : move to `detail` helper

private cpp_properties:
    ext::string m_url;
};


#endif //SBROWSER2_URL_HPP
