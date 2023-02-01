#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PRESENTATION_PRESENTATION_CONNECTION_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PRESENTATION_PRESENTATION_CONNECTION_HPP

// Inheritance Includes & This Class

namespace presentation {class presentation_connection;}
namespace presentation {class presentation_connection_private;}

// Other Includes & Forward Declarations
#include INCLUDE_INNER_TYPES(presentation)


class presentation::presentation_connection
        : public dom::nodes::event_target
{
public constructors:
    presentation_connection();
    MAKE_PIMPL(presentation_connection);
    MAKE_V8_AVAILABLE;

private js_methods:
    auto close() -> void;
    auto terminate() -> void;
    auto send(ext::string&& data) -> void;
    auto send(file_api::blob* data) -> void;
    auto send(v8::Local<v8::ArrayBuffer> data) -> void;
    auto send(v8::Local<v8::ArrayBufferView> data) -> void;

private js_properties:
    DEFINE_GETTER(id, ext::string_view);
    DEFINE_GETTER(url, ext::string_view);
    DEFINE_GETTER(state, detail::presentation_connection_state_t);
    DEFINE_GETTER(binary_type, ext::string_view); // TODO : Return Type
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PRESENTATION_PRESENTATION_CONNECTION_HPP
