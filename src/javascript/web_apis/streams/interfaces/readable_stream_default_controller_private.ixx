module;
#include "ext/macros.hpp"
#include <function2/function2.hpp>


export module apis.streams.readable_stream_default_controller:p;
import apis.streams.mixins.readable_stream_generic_controller;
import apis.streams.types;

import ext.js;


DEFINE_PRIVATE_CLASS(streams, readable_stream_default_controller)
        : mixins::readable_stream_generic_controller_private
{
public:
    MAKE_QIMPL(readable_stream_default_controller);

public:
    ext::unique_function<ext::number<int>(ext::queue<detail::chunk_t>)> strategy_size_algorithm; // TODO : or view?

public:
    auto pull_steps(const detail::read_request_t& request) -> void override;
    auto release_steps() -> void override;
    auto cancel_steps(ext::any&& reason) -> ext::promise<void>> override;
};
