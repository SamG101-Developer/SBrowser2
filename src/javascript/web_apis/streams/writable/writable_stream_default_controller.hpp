#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_WRITABLE_WRITABLE_STREAM_DEFAULT_CONTROLLER_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_WRITABLE_WRITABLE_STREAM_DEFAULT_CONTROLLER_HPP

// Inheritance Includes & This Class

namespace streams::writable {class writable_stream_default_controller;}
namespace streams::writable {class writable_stream_default_controller_private;}

// Other Includes & Forward Declarations
namespace dom::abort {class abort_signal;}


class streams::writable::writable_stream_default_controller
        : virtual public dom_object
{
public constructors:
    writable_stream_default_controller();
    MAKE_PIMPL(writable_stream_default_controller);
    MAKE_V8_AVAILABLE;

private js_methods:
    auto error(ext::any error) -> void;

private js_properties:
    DEFINE_GETTER(signal, dom::abort::abort_signal*);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_WRITABLE_WRITABLE_STREAM_DEFAULT_CONTROLLER_HPP
