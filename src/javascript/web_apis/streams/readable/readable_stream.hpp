#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_READABLE_READABLE_STREAM_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_READABLE_READABLE_STREAM_HPP

#include "dom_object.hpp"
namespace streams::readable {class readable_stream;}
namespace streams::readable {class readable_stream_private;}


#include INCLUDE_INNER_TYPES(streams)
#include INCLUDE_INNER_TYPES(html)
#include "ext/any.hpp"
#include "ext/boolean.hpp"
#include "ext/map.hpp"
#include "ext/variant.hpp"
#include "ext/vector.hpp"
namespace streams::readable {class readable_byte_stream_controller;}
namespace streams::readable {class readable_stream_default_controller;}
namespace streams::readable {class readable_stream_default_reader;}
namespace streams::readable {class readable_stream_byob_reader;}
namespace streams::readable_writable {class readable_writable_pair;}
namespace streams::writable {class writable_stream;}


class streams::readable::readable_stream
        : public virtual dom_object
{
public constructors:
    readable_stream(detail::underlying_source_t&& underlying_source, detail::queueing_strategy_t&& strategy = {});
    MAKE_PIMPL(readable_stream);
    MAKE_TRANSFERABLE(readable_stream);
    MAKE_V8_AVAILABLE;

public js_methods:
    auto cancel(ext::any reason) -> ext::promise<void>; // TODO : optional 'reason'?
    auto get_reader(detail::readable_stream_get_reader_options_t&& options = {}) -> std::unique_ptr<abstract_readable_stream_reader>;
    auto pipe_through(detail::readable_writable_pair_t&& transform, detail::stream_pipe_options_t&& options = {}) -> readable_stream*;
    auto pipe_to(writable::writable_stream* destination, detail::stream_pipe_options_t&& options = {}) -> ext::promise<void>;
    auto tee() -> ext::vector<std::unique_ptr<readable_stream>>;

private js_properties:
    DEFINE_GETTER(locked, ext::boolean);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_READABLE_READABLE_STREAM_HPP
