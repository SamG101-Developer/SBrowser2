module;
#include "ext/macros.hpp"

module apis.streams.writable_stream;
import apis.streams.detail;
import apis.streams.types;

import apis.dom.detail;


streams::writable_stream::writable_stream(
        detail::underlying_sink_t&& underlying_sink,
        detail::queueing_strategy_t&& strategy)
{
    using namespace v8_primitive_error_t;
    dom::detail::throw_v8_exception<V8_RANGE_ERR>(
            [&underlying_sink] {return underlying_sink.contains(u"type")},
            u8"Underlying sink cannot contain a 'type' option", e);

    detail::initialize_writable_stream(this);
    auto size_algorithm = detail::extract_size_algorithm(strategy);
    auto high_water_mark = detail::extract_high_water_mark(std::move(strategy), 1);
    detail::setup_writable_stream_default_controller_from_underlying_sink(
            this, std::move(underlying_sink),
            std::move(high_water_mark), std::move(size_algorithm));
}


streams::writable_stream::a
