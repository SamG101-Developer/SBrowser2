module;
#include "ext/macros.hpp"


export module apis.streams.readable_stream:p;
import apis.dom_object;
import ext.mixins;

import apis.streams.types;


DEFINE_PRIVATE_CLASS(streams, readable_stream)
        : virtual dom_object_private
        , public ext::async_vector_like_private<ext::any>
{
public:
    MAKE_QIMPL(readable_stream);

public:
    std::observer_ptr<mixins::readable_stream_generic_reader> reader;
    std::observer_ptr<mixins::readable_stream_generic_controller> controller;
    ext::boolean detached;
    ext::boolean disturbed;
    detail::readable_stream_state_t state;
    ext::any stored_error;
};
