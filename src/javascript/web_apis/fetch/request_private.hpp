#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FETCH_REQUEST_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FETCH_REQUEST_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "dom_object_private.hpp"
#include "fetch/mixins/body_private.hpp"

#include INCLUDE_INNER_TYPES(fetch)
namespace dom::abort {class abort_signal;}
namespace fetch {class headers;}


DEFINE_PRIVATE_CLASS(fetch, request)
        : virtual dom_object_private
        , public fetch::mixins::body_private
{
    MAKE_QIMPL(request);

    std::unique_ptr<detail::request_t> request;
    std::unique_ptr<headers> headers;
    std::unique_ptr<dom::abort::abort_signal> signal;

    auto mime_type() -> ext::string;
    auto body() -> detail::body_t*;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FETCH_REQUEST_PRIVATE_HPP
