#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_READABLE_READABLE_BYTE_STREAM_CONTROLLER_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_READABLE_READABLE_BYTE_STREAM_CONTROLLER_HPP

#include "streams/readable/abstract_readable_stream_controller.hpp"
namespace streams::readable {class readable_byte_stream_controller;}

#include "streams/_typedefs.hpp"
namespace streams::readable {class readable_stream_byob_request;}

class streams::readable::readable_byte_stream_controller
        : public abstract_readable_stream_controller
{
public js_methods:
    auto close() -> void override;
    auto enqueue(v8::Local<v8::ArrayBufferView> chunk) -> void override;
    auto error(ext::any&& error) -> void override;

public js_properties:
    ext::property<readable_stream_byob_request*> byob_request;

private js_slots:
    ext::number<int> s_auto_allocate_chunk_size;
    std::unique_ptr<readable_stream_byob_request> s_byob_request;
    ext::vector<detail::pull_into_descriptor_t> s_pending_pull_intos;

private js_slot_methods:
    auto s_pull_steps(const detail::read_request_t& request) -> void override;
    auto s_release_steps() -> void override;
    auto s_cancel_steps(ext::any&& reason) -> void override;

private cpp_accessors:
    _EXT_NODISCARD auto get_desired_size() const -> ext::number<double> override;
    _EXT_NODISCARD auto get_byob_request() const -> readable_stream_byob_request*;

};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_READABLE_READABLE_BYTE_STREAM_CONTROLLER_HPP
