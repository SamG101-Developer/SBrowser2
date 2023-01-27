module;
#include "ext/macros.hpp"
#include <function2/function2.hpp>


export module apis.streams.mixins.readable_stream_generic_controller:p;
import apis.dom_object;

import apis.streams.types;


DEFINE_PRIVATE_CLASS(streams::mixins, readable_stream_generic_controller)
        : virtual dom_object_private
{
public:
    MAKE_QIMPL(readable_stream_generic_controller);

public:
    ext::unique_function<auto(ext::any&&) -> ext::promise<void>> cancel_algorithm;
    ext::unique_function<auto() -> ext::promise<void>> pull_algorithm;
    ext::boolean close_requested;
    ext::boolean pull_again;
    ext::boolean pulling;
    ext::boolean started;
    ext::number<int> strategy_hwm;
    ext::queue<std::remove_reference_t<detail::chunk_t>*> queue;
    ext::number<size_t> queue_total_size;
    std::observer_ptr<readable_stream> stream;

public:
    virtual auto pull_steps(const detail::read_request_t& request) -> void = 0;
    virtual auto release_steps() -> void = 0;
    virtual auto cancel_steps(ext::any&& reason) -> ext::promise<void>> = 0;
};
