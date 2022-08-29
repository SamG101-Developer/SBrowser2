#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_MIXINS_READABLE_STREAM_GENERIC_READER_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_MIXINS_READABLE_STREAM_GENERIC_READER_HPP

#include "dom_object.hpp"
namespace streams::mixins {class readable_stream_generic_reader;}

#include "ext/promise.hpp"
namespace streams::readable {class readable_stream;}


class streams::mixins::readable_stream_generic_reader
        : public virtual dom_object
{
public constructors:
    readable_stream_generic_reader();

public js_methods:
    template <typename T>
    auto cancel(T&& reason = nullptr) -> ext::promise<void>;

public js_properties:
    ext::property<ext::promise<void>> closed;

protected js_slots:
    ext::promise<void> s_closed_promise;
    readable::readable_stream* s_stream;

private cpp_accessors:
    DEFINE_GETTER(closed);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_MIXINS_READABLE_STREAM_GENERIC_READER_HPP
