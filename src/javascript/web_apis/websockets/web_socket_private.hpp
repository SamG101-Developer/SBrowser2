#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBSOCKETS_WEB_SOCKET_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBSOCKETS_WEB_SOCKET_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "dom/nodes/event_target_private.hpp"
namespace websockets {class web_socket;}

#include INCLUDE_INNER_TYPES(url)
#include INCLUDE_INNER_TYPES(websockets)


DEFINE_PRIVATE_CLASS(websockets, web_socket) : dom::nodes::event_target_private
{
    MAKE_QIMPL(web_socket);

    std::shared_ptr<url::detail::url_t> url;
    detail::binary_type_t type = detail::binary_type_t::BLOB;
    ext::number<ushort> ready_state;
    ext::string extensions;
    ext::string protocols;

    std::unique_ptr<detail::websocket_t> web_socket;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBSOCKETS_WEB_SOCKET_PRIVATE_HPP
