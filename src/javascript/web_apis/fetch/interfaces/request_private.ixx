module;
#include "ext/macros.hpp"


export module apis.fetch.request:p;
import apis.dom_object;
import apis.fetch.mixins.body;

import apis.fetch.types;
import apis.dom.types;


DEFINE_PRIVATE_CLASS(fetch, request)
        : virtual dom_object_private
        , public fetch::mixins::body_private
{
public:
    MAKE_QIMPL(request);

public:
    std::unique_ptr<detail::request_t> request;
    std::unique_ptr<dom::abort_signal> signal;

public:
    auto mime_type() const -> ext::string override;
    auto body() const -> detail::body_t* override;
};
