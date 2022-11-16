#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_URL_URL_SEARCH_PARAMS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_URL_URL_SEARCH_PARAMS_HPP

#include "dom_object.hpp"
namespace url {class url_search_params;}
namespace url {class url_search_params_private;}

#include "ext/span.hpp"
namespace url {class url;}


class url::url_search_params
        : public virtual dom_object
{
public friends:
    friend class url;

public constructors:
    url_search_params(ext::vector_span<ext::vector<ext::string>> init);
    url_search_params(ext::map_span<ext::string, ext::string> init);
    url_search_params(ext::string_view init);
    MAKE_PIMPL(url_search_params);
    MAKE_STRINGIFIER;
    MAKE_V8_AVAILABLE;

public js_methods:
    auto append(ext::string&& name, ext::string&& value) -> void;
    auto delete_(ext::string&& name) -> void;
    auto get(ext::string&& name) -> ext::string;
    auto get_all(ext::string&& name) -> ext::vector<ext::string>;
    auto has(ext::string&& name) -> ext::boolean;
    auto set(ext::string&& name, ext::string&& value) -> void;

    auto sort() -> void;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_URL_URL_SEARCH_PARAMS_HPP
