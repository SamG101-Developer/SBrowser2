#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_READABLE_ABSTRACT_READABLE_STREAM_CONTROLLER_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_READABLE_ABSTRACT_READABLE_STREAM_CONTROLLER_HPP

#include "dom_object.hpp"
namespace streams::readable {class abstract_readable_stream_controller;}

#include "ext/queue.hpp"
#include "ext/promise.hpp"
#include <v8-forward.h>
#include INCLUDE_INNER_TYPES(streams)
namespace streams::readable {class readable_stream;}

class streams::readable::abstract_readable_stream_controller
        : public virtual dom_object
{
public constructors:
    abstract_readable_stream_controller();

public js_methods:
    virtual auto close() -> void = 0;
    virtual auto enqueue(v8::Local<v8::ArrayBufferView> chunk) -> void = 0;
    virtual auto error(ext::any&& error) -> void = 0;

private js_properties:
    ext::property<ext::number<double>> desired_size;

protected js_slots:
    ext::function<ext::promise<void>(detail::error_t&&)> s_cancel_algorithm;
    ext::function<ext::promise<void>()> s_pull_algorithm;
    ext::boolean s_close_requested;
    ext::boolean s_pull_again;
    ext::boolean s_pulling;
    ext::boolean s_started;
    ext::number<int> strategy_hwm;
    ext::queue<detail::chunk_t> s_queue;
    ext::number<size_t> s_queue_total_size;
    readable_stream* s_stream;

protected js_slot_methods:
    virtual auto s_pull_steps(const detail::read_request_t& request) -> void = 0;
    virtual auto s_release_steps() -> void = 0;
    virtual auto s_cancel_steps(ext::any&& reason) -> void = 0;

private js_properties:
    virtual DEFINE_CUSTOM_GETTER(desired_size) = 0;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_READABLE_ABSTRACT_READABLE_STREAM_CONTROLLER_HPP
