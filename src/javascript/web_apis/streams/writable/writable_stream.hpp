#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_WRITABLE_WRITABLE_STREAM_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_WRITABLE_WRITABLE_STREAM_HPP

// Inheritance Includes & This Class

namespace streams::writable {class writable_stream;}
namespace streams::writable {class writable_stream_private;}

// Other Includes & Forward Declarations

namespace streams::writable {class writable_stream_default_writer;}


class streams::writable::writable_stream
        : public dom_object
{
public constructors:
    writable_stream();
    MAKE_PIMPL(writable_stream);
    MAKE_V8_AVAILABLE;

public js_methods:
    auto abort(ext::any reason) -> ext::promise<void>;
    auto close() -> ext::promise<void>;
    auto get_writer() -> writable_stream_default_writer*;

public js_properties:
    DEFINE_GETTER(locked, ext::boolean);

};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_WRITABLE_WRITABLE_STREAM_HPP
