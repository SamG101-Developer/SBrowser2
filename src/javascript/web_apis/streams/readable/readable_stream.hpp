#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_READABLE_READABLE_STREAM_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_READABLE_READABLE_STREAM_HPP

#include "dom_object.hpp"
namespace streams::readable {class readable_stream;}

#include "ext/any.hpp"
#include "ext/boolean.hpp"
#include "ext/map.hpp"
#include "ext/variant.hpp"
#include "ext/vector.hpp"
#include INCLUDE_INNER_TYPES(streams)
namespace streams::readable {class readable_byte_stream_controller;}
namespace streams::readable {class readable_stream_default_controller;}
namespace streams::readable {class readable_stream_default_reader;}
namespace streams::readable {class readable_stream_byob_reader;}
namespace streams::readable_writeable {class readable_writeable_pair;}
namespace streams::writeable {class writeable_stream;}


class streams::readable::readable_stream
        : public dom_object
{
public constructors:
    readable_stream();
    readable_stream(ext::map<ext::string, ext::any>&& underlying_source, ext::map<ext::string, ext::any>&& strategy = {});

public js_methods:
    template <typename T>
    auto cancel(T&& reason = nullptr) -> ext::promise<void>;
    auto get_reader(ext::map<ext::string, ext::any>&& options = {}) -> detail::readable_stream_reader_t;
    auto pipe_through(ext::map<ext::string, ext::any>&& transform, ext::map<ext::string, ext::any>&& options = {}) -> readable_stream*;
    auto pipe_to(writeable::writeable_stream* destination, ext::map<ext::string, ext::any>&& options = {}) -> ext::promise<void>;
    auto tee() -> ext::vector<readable_stream*>;

private js_properties:
    ext::property<ext::boolean> locked;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;

private js_slots:
    detail::readable_stream_controller_t s_controller;
    detail::readable_stream_reader_t s_reader;
    ext::boolean s_detached;
    ext::boolean s_disturbed;
    detail::readable_stream_state_t s_state;
    ext::string s_error;

private js_properties:
    DEFINE_CUSTOM_GETTER(locked);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_READABLE_READABLE_STREAM_HPP
