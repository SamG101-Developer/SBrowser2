#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_URL_URL_SEARCH_PARAMS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_URL_URL_SEARCH_PARAMS_HPP

#include "dom_object.hpp"
namespace url {class url_search_params;}

#include "ext/map.hpp"
namespace url {class url;}


class url::url_search_params
        : public virtual dom_object
{
public constructors:
    DOM_CTORS(url_search_params);
    url_search_params() = default;
    url_search_params(const ext::vector<ext::vector<ext::string>>& init);
    url_search_params(const ext::map<ext::string, ext::string>& init);
    url_search_params(ext::string_view init);

public js_methods:
    auto append(ext::string&& name, ext::string&& value) -> void;
    auto delete_(ext::string&& name) -> void;
    auto get(ext::string&& name) -> ext::string;
    auto get_all(ext::string&& name) -> ext::vector<ext::string>;
    auto has(ext::string&& name) -> ext::boolean;
    auto set(ext::string&& name, ext::string&& value) -> void;

    auto sort() -> void;

public cpp_methods:
    auto to_json() const -> ext::string override;

private cpp_properties:
    std::unique_ptr<ext::map<ext::string, ext::string>> m_list;
    std::unique_ptr<url::url> m_url;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_URL_URL_SEARCH_PARAMS_HPP
