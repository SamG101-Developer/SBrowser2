module;
#include "ext/macros.hpp"


export module apis.streams.readable_stream;
import apis.dom_object;
import ext.mixins;

import apis.streams.types;
import ext.js;


DEFINE_PUBLIC_CLASS(streams, readable_stream) final
        : public virtual dom_object
        , public ext::async_vector_like<ext::any>
{
public typedefs:
    using readable_stream_get_reader_options_t = ext::map<ext::string, ext::any>;
    using readable_stream_iterator_options_t = ext::map<ext::string, ext::any>;
    using readable_writable_pair_t = ext::map<ext::string, ext::any>;
    using stream_pipe_options_t = ext::map<ext::string, ext::any>;

public constructors:
    readable_stream();
    readable_stream(detail::underlying_source_t&& underlying_source, detail::queueing_strategy_t&& strategy = {});
    MAKE_PIMPL(readable_stream);
    MAKE_TRANSFERABLE(readable_stream); // TODO
    MAKE_V8_AVAILABLE(ALL);

    auto operator[](const readable_stream_iterator_options_t& key) -> ext::any& override;

private js_methods:
    auto cancel(ext::any&& reason) -> ext::promise<void>;
    auto get_reader(readable_stream_get_reader_options_t&& options = {}) -> std::unique_ptr<mixins::readable_stream_generic_reader>;
    auto pipe_through(readable_writable_pair_t&& transform, stream_pipe_options_t&& options = {}) -> readable_stream*;
    auto pipe_to(writable_stream* destination, stream_pipe_options_t&& options = {}) -> ext::promise<void>;
    auto tee() -> ext::vector<std::unique_ptr<readable_stream>>;

private js_properties:
    DEFINE_GETTER(locked, ext::boolean);
};
