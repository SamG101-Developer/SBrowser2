module;
#include "ext/macros.hpp"


export module apis.fetch.mixins.body:p;
import apis.dom_object;

import apis.fetch.types;


DEFINE_PRIVATE_CLASS(fetch::mixins, body)
        : virtual dom_object_private
{
public:
    MAKE_QIMPL(body);

public:
    std::unique_ptr<headers> headers;

    // TODO : Provide default implementations?
    virtual auto mime_type() const -> ext::string = 0;
    virtual auto body() const -> detail::body_t* = 0;
};
