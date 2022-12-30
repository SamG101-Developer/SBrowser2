module;
#include "ext/macros.hpp"


export module apis.url.url_search_params:p;
import apis.dom_object;
import ext.mixins;

import ext.core;


DEFINE_PRIVATE_CLASS(url, url_search_params)
        : virtual dom_object_private
        , ext::map_like_linked_private<ext::string, ext::string>
{
public:
    MAKE_QIMPL(url_search_params);

public:
    ext::multi_map<ext::string, ext::string> list;
    std::observer_ptr<url> url;
};
