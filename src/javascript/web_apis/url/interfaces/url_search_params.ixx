module;
#include "ext/macros/annotations.hpp"
#include "ext/macros/macros.hpp"
#include "ext/macros/other.hpp"
#include "javascript/macros/expose.hpp"


export module apis.url.url_search_params;
import apis.dom_object;
import ext.mixins;

import ext.core;
import js.env.module_type;


DEFINE_PUBLIC_CLASS(url, url_search_params) final
        : virtual public dom_object
        , ext::map_like_linked<ext::string, ext::string>
{
public friends:
    friend class url;

public constructors:
    url_search_params(ext::vector<ext::pair<ext::string, ext::string>>&& init);
    url_search_params(ext::map<ext::string, ext::string>&& init);
    url_search_params(ext::string_view init = u"");
    MAKE_PIMPL(url_search_params);
    MAKE_STRINGIFIER;
    MAKE_V8_AVAILABLE(ALL);

public js_methods:
    auto append(ext::string&& name, ext::string&& value) -> void;
    auto delete_(ext::string&& name) -> void;
    auto get(ext::string&& name) -> ext::string;
    auto get_all(ext::string&& name) -> ext::vector<ext::string>;
    auto has(ext::string&& name) -> ext::boolean;
    auto set(ext::string&& name, ext::string&& value) -> void;

    auto sort() -> void;
};
