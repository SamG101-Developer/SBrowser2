#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBSOCKETS_DETAIL_RFC6455_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBSOCKETS_DETAIL_RFC6455_INTERNALS_HPP



#include "ext/expected.ixx"
#include "ext/number.ixx"
#include "ext/string.hpp"
#include "ext/vector.hpp"
#include <v8-forward.h>
#include INCLUDE_INNER_TYPES(url)
#include INCLUDE_INNER_TYPES(websockets)
namespace websockets {class web_socket;}
class QWebSocket;


namespace websockets::detail
{
    auto establish_websocket_connection(
            const url::detail::url_t& url,
            ext::vector<ext::string>&& protocols,
            v8::Local<v8::Object> client)
            -> void;

    auto obtain_websocket_connection(
            const url::detail::url_t& url)
            -> ext::expected<std::unique_ptr<websocket_t>>;

    auto make_disappear(
            web_socket* websocket)
            -> void;

    RFC_DEFINITION_BEGIN

    auto is_websocket_connection_established(
            const websocket_t& websocket)
            -> ext::boolean;

    auto establish_websocket_connection(
            const ext::string& host,
            ext::number<ushort> port,
            ext::string_view resource_name,
            ext::boolean secure)
            -> std::unique_ptr<websocket_t>;

    auto send_websocket_message(
            ext::string&& data,
            const websocket_t& websocket)
            -> void;

    auto close_websocket_connection(
            const websocket_t& websocket)
            -> void;

    auto start_websocket_closing_handshake(
            ext::number<int> code,
            ext::string_view reason,
            const websocket_t& websocket)
            -> void;

    auto has_websocket_closing_handshake_started(
            const websocket_t& websocket)
            -> ext::boolean;

    auto has_websocket_closed(
            const websocket_t& websocket)
            -> ext::boolean;

    auto fail_websocket_connection(
            const websocket_t& websocket)
            -> void;

    RFC_DEFINITION_END
}


struct websockets::detail::websocket_t
{
    ext::boolean full;
    std::unique_ptr<QWebSocket> connection;
    static ext::vector<websocket_t*> connections;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBSOCKETS_DETAIL_RFC6455_INTERNALS_HPP
