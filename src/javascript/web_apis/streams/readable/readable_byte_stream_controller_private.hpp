#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_READABLE_READABLE_BYTE_STREAM_CONTROLLER_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_READABLE_READABLE_BYTE_STREAM_CONTROLLER_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "abstract_readable_stream_controller_private.hpp"

namespace streams::readable {class readable_stream_byob_request;}


DEFINE_PRIVATE_CLASS(streams::readable, readable_byte_stream_controller) : abstract_readable_stream_controller_private
{
    MAKE_QIMPL(readable_byte_stream_controller);
    
    ext::number<int> auto_allocate_chunk_size;
    std::observer_ptr<readable_stream_byob_request> byob_request;
    ext::vector<detail::pull_into_descriptor_t*> pending_pull_intos;
    
    auto pull_steps(const detail::read_request_t& request) -> void override;
    auto release_steps() -> void override;
    auto cancel_steps(ext::any reason) -> void override;
};


// auto streams::readable::readable_byte_stream_controller_private::pull_steps(const detail::read_request_t& request) -> void
// {
//     ASSERT(detail::readable_stream_has_default_reader(s_stream));
//     if (s_queue_total_size > 0)
//     {
//         ASSERT(detail::readable_stream_get_num_read_requests(s_stream) == 0);
//         detail::readable_byte_stream_controller_fill_read_request_from_queue(this, request);
//         return;
//     }
//
//     if (s_auto_allocate_chunk_size)
//     {
//         JS_REALM_GET_RELEVANT(this)
//         auto buffer = v8::ArrayBuffer::New(this_relevant_agent, d->auto_allocate_chunk_size);
//         if (buffer.IsEmpty())
//         {
//             request.error_steps(buffer);
//             return;
//         }
//
//         using detail::readable_stream_reader_mode_t;
//         d->pending_pull_intos.emplace_back(
//                 buffer, d->auto_allocate_chunk_size, 0, d->auto_allocate_chunk_size, 0, 1, v8::DataView::New(buffer, 0, 0),
//                 readable_stream_reader_mode_t::DEFAULT);
//     }
//
//     detail::readable_stream_add_read_request(stream, read_request);
//     detail::readable_byte_stream_controler_call_pull_if_needed(this);
// }
//
//
// auto streams::readable::readable_byte_stream_controller::s_cancel_steps(
//         ext::any&& reason)
// -> void
// {
//     detail::readable_byte_stream_controller_clear_pending_pull_intos(this);
//     detail::queue_internals::reset_queue(this);
//
//     auto result = d->cancel_steps(std::move(reason));
//     detail::readable_byte_stream_controller_clear_algorithms();
//     return result;
// }
//
//
// auto streams::readable::readable_byte_stream_controller::s_release_steps()
// -> void
// {
//     if (!s_pending_pull_intos.empty())
//     {
//         using detail::readable_stream_reader_mode_t;
//
//         decltype(auto) first_pending_ull_into = d->pending_pull_intos[0];
//         first_pending_ull_into.reader_type = readable_stream_reader_mode_t::NONE;
//         d->pending_pull_intos = {first_pending_ull_into};
//     }
// }


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_READABLE_READABLE_BYTE_STREAM_CONTROLLER_PRIVATE_HPP
