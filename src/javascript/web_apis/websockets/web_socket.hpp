#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBSOCKETS_WEB_SOCKET_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBSOCKETS_WEB_SOCKET_HPP

// Inheritance Includes & This Class

namespace websockets {class web_socket;}
namespace websockets {class web_socket_private;}

// Other Includes & Forward Declarations
#include INCLUDE_INNER_TYPES(websockets)
#include "ext/array_buffer.hpp"


class websockets::web_socket
        : public dom::nodes::event_target
{
public constructors:
    web_socket(ext::string_view url, ext::vector<ext::string>&& protocols = {});
    web_socket(ext::string_view url, ext::string&& protocols);
    MAKE_PIMPL(web_socket);
    MAKE_V8_AVAILABLE;

public js_static_constants:
    static constexpr ext::number<ushort> CONNECTING = 0;
    static constexpr ext::number<ushort> OPEN       = 1;
    static constexpr ext::number<ushort> CLOSING    = 2;
    static constexpr ext::number<ushort> CLOSED     = 3;

public js_methods:
    auto close(ext::optional<ext::number<ushort>> code, ext::optional<ext::string> reason = u"") -> void;
    auto send(ext::buffer_source&& data) -> void;
    auto send(file_api::blob* data) -> void;
    auto send(ext::string&& data) -> void;

public js_properties:
    DEFINE_GETTER(url, ext::string);
    DEFINE_GETTER(ready_state, ext::number<ushort>);
    DEFINE_GETTER(buffered_amount, ext::number<ulonglong>);
    DEFINE_GETTER(extensions, ext::string_view);
    DEFINE_GETTER(protocol, ext::string_view);
    DEFINE_GETTER(binary_type, detail::binary_type_t);
    DEFINE_SETTER(binary_type, detail::binary_type_t);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBSOCKETS_WEB_SOCKET_HPP
