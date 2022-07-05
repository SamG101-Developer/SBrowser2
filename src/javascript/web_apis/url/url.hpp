#ifndef SBROWSER2_URL_HPP
#define SBROWSER2_URL_HPP

#include <web_apis/dom_object.hpp>
namespace url {class url_object;}


class url::url_object : public virtual web_apis::dom_object
{
public constructors:
    url_object(ext::string_view url_string);

public cpp_operators:
    auto operator=(ext::string_view url) -> url_object&;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;
};


#endif //SBROWSER2_URL_HPP
