module;
#include "ext/macros/pimpl.hpp"


export module apis.url.url_private;
import apis.dom_object_private;

import apis.url.types;


DEFINE_PRIVATE_CLASS(url, url) : virtual dom_object_private
{
public:
    MAKE_QIMPL(url);

public:
    std::shared_ptr<detail::url_t> url;
    std::unique_ptr<url_search_params> query_object;
};
