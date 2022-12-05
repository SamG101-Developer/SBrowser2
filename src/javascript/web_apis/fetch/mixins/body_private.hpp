#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FETCH_MIXINS_BODY_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FETCH_MIXINS_BODY_PRIVATE_HPP

#include "ext/pimpl.ixx"


#include INCLUDE_INNER_TYPES(fetch)




DEFINE_PRIVATE_CLASS(fetch::mixins, body)
        : virtual dom_object_private
{
    MAKE_QIMPL(body);

    std::unique_ptr<headers> headers;

    // TODO : Provide default implementations?
    virtual auto mime_type() const -> ext::string = 0;
    virtual auto body() const -> detail::body_t* = 0;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FETCH_MIXINS_BODY_PRIVATE_HPP
