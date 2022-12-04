#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FETCH_HEADERS_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FETCH_HEADERS_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "ext/map_like.ixx"

#include INCLUDE_INNER_TYPES(fetch)


DEFINE_PRIVATE_CLASS(fetch, headers)
        : virtual dom_object_private
        , ext::map_like_private<detail::header_name_t, detail::header_value_t>
{
    MAKE_QIMPL(headers);

    detail::headers_t headers_list;
    detail::header_guard_t headers_guard;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FETCH_HEADERS_PRIVATE_HPP
