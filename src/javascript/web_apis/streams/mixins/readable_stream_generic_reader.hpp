#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_MIXINS_READABLE_STREAM_GENERIC_READER_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_MIXINS_READABLE_STREAM_GENERIC_READER_HPP

#include "dom_object.hpp"
namespace streams::mixins {class readable_stream_generic_reader;}
namespace streams::mixins {class readable_stream_generic_reader_private;}


namespace streams::readable {class readable_stream;}


class streams::mixins::readable_stream_generic_reader
        : public virtual dom_object
{
public constructors:
    readable_stream_generic_reader();
    MAKE_PIMPL(readable_stream_generic_reader);
    MAKE_V8_AVAILABLE;

public js_methods:
    auto cancel(ext::any reason) -> ext::promise<void>;

private js_properties:
    DEFINE_GETTER(closed, const ext::promise<void>&);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_MIXINS_READABLE_STREAM_GENERIC_READER_HPP
