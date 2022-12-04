#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_WRITABLE_WRITABLE_STREAM_DEFAULT_WRITER_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_WRITABLE_WRITABLE_STREAM_DEFAULT_WRITER_HPP

// Inheritance Includes & This Class
#include "dom_object.hpp"
namespace streams::writable {class writable_stream_default_writer;}
namespace streams::writable {class writable_stream_default_writer_private;}

// Other Includes & Forward Declarations

namespace streams::writable {class writable_stream;}


class streams::writable::writable_stream_default_writer
        : virtual public dom_object
{
public constructors:
    writable_stream_default_writer(writable_stream* stream);
    MAKE_PIMPL(writable_stream_default_writer);
    MAKE_V8_AVAILABLE;

public js_methods:
    auto abort(ext::any reason) -> ext::promise<void>;
    auto close() -> ext::promise<void>;
    auto release_lock() -> void;
    auto write(ext::any chunk) -> ext::promise<void>;

public js_properties:
    DEFINE_GETTER(closed, ext::promise<void>);
    DEFINE_GETTER(desired_size, ext::number<double>);
    DEFINE_GETTER(ready, ext::promise<void>);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_WRITABLE_WRITABLE_STREAM_DEFAULT_WRITER_HPP
