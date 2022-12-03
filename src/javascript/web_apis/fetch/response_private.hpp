#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FETCH_RESPONSE_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FETCH_RESPONSE_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "dom_object_private.hpp"
#include "fetch/mixins/body_private.hpp"

#include INCLUDE_INNER_TYPES(fetch);


DEFINE_PRIVATE_CLASS(fetch, response)
        : virtual dom_object_private
        , mixins::body_private
{
    MAKE_QIMPL(response);

    std::unique_ptr<detail::response_t> response;

    auto mime_type() const -> ext::string override;
    auto body() const -> detail::body_t* override;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FETCH_RESPONSE_PRIVATE_HPP
