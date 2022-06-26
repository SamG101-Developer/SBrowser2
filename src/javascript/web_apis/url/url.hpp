#ifndef SBROWSER2_URL_HPP
#define SBROWSER2_URL_HPP

#include <web_apis/dom_object.hpp>
namespace url {class url_object;}


class url::url_object : public virtual web_apis::dom_object
{
public cpp_operators:
    auto operator=(ext::string_view url) -> url_object&;
};


#endif //SBROWSER2_URL_HPP
