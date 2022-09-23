#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_READABLE_READABLE_STREAM_DEFAULT_CONTROLLER_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_READABLE_READABLE_STREAM_DEFAULT_CONTROLLER_HPP

#include "streams/readable/abstract_readable_stream_controller.hpp"
namespace streams::readable {class readable_stream_default_controller;}

#include "ext/boolean.hpp"
#include "ext/functional.hpp"
#include "ext/number.hpp"
#include "ext/queue.hpp"
#include INCLUDE_INNER_TYPES(streams)

class streams::readable::readable_stream_default_controller
        : public abstract_readable_stream_controller
{
public js_methods:
    auto close() -> void override;
    auto enqueue(v8::Local<v8::ArrayBufferView> chunk) -> void override;
    auto error(ext::any&& error) -> void override;

private js_slots:
    ext::function<ext::number<int>(ext::queue<detail::chunk_t>)> s_strategy_size_algorithm;

private js_slot_methods:
    auto s_pull_steps(const detail::read_request_t& request) -> void override;
    auto s_release_steps() -> void override {}
    auto s_cancel_steps(ext::any&& reason) -> void override;

private js_properties:
    DEFINE_CUSTOM_GETTER(desired_size) override;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_READABLE_READABLE_STREAM_DEFAULT_CONTROLLER_HPP
