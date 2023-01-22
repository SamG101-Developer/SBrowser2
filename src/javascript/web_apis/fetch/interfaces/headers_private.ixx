module;
#include "ext/macros.hpp"


export module apis.fetch.headers:p;
import apis.dom_object;
import ext.mixins;

import apis.fetch.types;


DEFINE_PRIVATE_CLASS(fetch, headers) final
        : virtual dom_object_private
        , ext::map_like_private<detail::header_name_t, detail::header_value_t>
{
public:
    MAKE_QIMPL(headers);

public:
    detail::headers_t headers_list;
    detail::header_guard_t headers_guard;
};
