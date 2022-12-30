module;
#include "ext/macros.hpp"


export module apis.url.url:p;
import apis.dom_object;

import apis.url.types;


DEFINE_PRIVATE_CLASS(url, url) : virtual dom_object_private
{
public:
    MAKE_QIMPL(url);

public:
    std::shared_ptr<detail::url_t> url;
    std::unique_ptr<url_search_params> query_object;
};
