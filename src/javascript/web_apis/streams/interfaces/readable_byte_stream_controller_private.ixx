module;
#include "ext/macros.hpp"


export module apis.streams.readable_byte_stream_controller:p;
import apis.streams.mixins.readable_stream_generic_controller;
import apis.streams.types;


DEFINE_PRIVATE_CLASS(streams, readable_byte_stream_controller)
        : mixins::readable_stream_generic_controller_private
{
public:
    MAKE_QIMPL(readable_byte_stream_controller);

public:
    ext::number<int> auto_allocate_chunk_size;
    std::observer_ptr<readable_stream_byob_request> byob_request;
    ext::vector<detail::pull_into_descriptor_t*> pending_pull_intos;

public:
    auto pull_steps(const detail::read_request_t& request) -> void override;
    auto release_steps() -> void override;
    auto cancel_steps(ext::any&& reason) -> ext::promise<void> override;
};
