module;
#include "ext/macros.hpp"


export module apis.streams.readable_stream_default_controller:p;
import apis.streams.mixins.readable_stream_generic_controller;


DEFINE_PRIVATE_CLASS(readable, readable_stream_default_controller)
        : mixins::readable_stream_generic_controller_private
{
public:
    MAKE_QIMPL(readable_stream_default_controller);

public:
    ext::function<ext::number<int>(ext::queue<detail::chunk_t>)> strategy_size_algorithm;

public:
    auto pull_steps(const detail::read_request_t& request) -> void override;
    auto release_steps() -> void override;
    auto cancel_steps(ext::any&& reason) -> void override;
};
