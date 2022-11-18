#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBSOCKETS_DETAIL_PROTOCOL_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBSOCKETS_DETAIL_PROTOCOL_INTERNALS_HPP

#include "ext/expected.hpp"
#include "ext/string.hpp"
#include "ext/vector.hpp"
#include <v8-forward.h>
#include INCLUDE_INNER_TYPES(url)
#include INCLUDE_INNER_TYPES(websockets)
class QWebSocket;


namespace websockets::detail
{
    auto obtain_websocket_connection(
            const url::detail::url_t& url)
            -> ext::expected<std::unique_ptr<websocket_t>>;

    auto establish_websocket_connection(
            const url::detail::url_t& url,
            ext::vector<ext::string>&& protocols,
            v8::Local<v8::Object> client)
            -> void;
}


struct websockets::detail::websocket_t
{
    std::unique_ptr<QWebSocket> socket;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBSOCKETS_DETAIL_PROTOCOL_INTERNALS_HPP
