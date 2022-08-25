#ifndef SBROWSER2_URL_HPP
#define SBROWSER2_URL_HPP

#include "dom_object.hpp"
namespace url {class url;}

#include USE_INNER_TYPES(url)
namespace file_api {class blob;}
namespace url {class url_search_params;}


class url::url
        : public virtual dom_object
{
public constructors:
    url(ext::string_view url_string = "");

public js_methods:
    /* FILE_API */
    static auto create_object_url(file_api::blob* blob) -> ext::string;
    static auto revoke_object_url(ext::string_view url);

public js_properties:
    ext::property<ext::string> href;
    ext::property<ext::string> origin;
    ext::property<ext::string> protocol;
    ext::property<ext::string> username;
    ext::property<ext::string> password;
    ext::property<ext::string> host;
    ext::property<ext::string> hostname;
    ext::property<ext::string> port;
    ext::property<ext::string> pathname;
    ext::property<ext::string> search;
    ext::property<ext::string> hash;
    ext::property<std::unique_ptr<url_search_params>> search_params;

public cpp_operators:
    operator bool() const {return !href().empty();}
    auto operator!() const -> ext::boolean {return href().empty();}

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;
    auto to_json() const -> ext::string override;

private cpp_properties:
    std::unique_ptr<detail::url_t> m_url;
    std::unique_ptr<url_search_params> m_query_object;
};


#endif //SBROWSER2_URL_HPP
