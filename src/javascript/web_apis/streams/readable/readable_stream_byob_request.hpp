#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_READABLE_READABLE_STREAM_BYOB_REQUEST_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_READABLE_READABLE_STREAM_BYOB_REQUEST_HPP

#include "dom_object.hpp"
namespace streams::readable {class readable_stream_byob_request;}

#include <v8-forward.h>
namespace streams::readable {class readable_byte_stream_controller;}


class streams::readable::readable_stream_byob_request
        : public virtual dom_object
{
public constructors:
    readable_stream_byob_request();

public js_methods:
    auto respond(ext::number<ulonglong> bytes_written) -> void;
    auto respond_with_new_view(v8::Local<v8::ArrayBufferView> view) -> void;

public js_properties:
    ext::property<v8::ArrayBufferView> view;

private js_slots:
    readable_byte_stream_controller* s_controller;
    v8::ArrayBufferView s_view;

private cpp_accessors:
    DEFINE_CUSTOM_GETTER(view);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_READABLE_READABLE_STREAM_BYOB_REQUEST_HPP
