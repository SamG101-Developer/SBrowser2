#include "web_socket.hpp"
#include "web_socket_private.hpp"

#include "dom/_typedefs.hpp"
#include "dom/detail/exception_internals.hpp"

#include "encoding/detail/encoding_internals.hpp"
#include "file_api/detail/blob_internals.hpp"
#include "url/detail/url_internals.hpp"
#include "websockets/detail/rfc6455_internals.hpp"

#include <qwebsocket.h>


websockets::web_socket::web_socket(
        ext::string_view url,
        ext::string&& protocols)

        : web_socket(url, ext::vector<ext::string>{std::move(protocols)})
{}


websockets::web_socket::web_socket(
        ext::string_view url,
        ext::vector<ext::string>&& protocols)
{
    INIT_PIMPL(web_socket)
    using enum dom::detail::dom_exception_error_t;
    auto url_record = url::detail::url_parser(url);

    dom::detail::throw_v8_exception<SYNTAX_ERR>(
            [&url_record] {return !url_record.has_value();});

    dom::detail::throw_v8_exception<SYNTAX_ERR>(
            [url_record = **url_record] {return url_record.scheme != u"ws" | url_record.scheme != u"wss";});

    dom::detail::throw_v8_exception<SYNTAX_ERR>(
            [url_record = **url_record] {return !url_record.fragment.empty();});

    // TODO : check protocols

    ACCESS_PIMPL(web_socket);
    d->url = std::move(*url_record);

    GO [d, e = js::env::env::relevant(this), protocols = std::move(protocols)] mutable
    {
        detail::establish_websocket_connection(*d->url, std::move(protocols), e.js.settings());
    };
}


auto websockets::web_socket::close(
        ext::optional<ext::number<ushort>> code,
        ext::optional<ext::string> reason)
        -> void
{
    ACCESS_PIMPL(web_socket);
    using enum dom::detail::dom_exception_error_t;

    dom::detail::throw_v8_exception<INVALID_ACCESS_ERR>(
            [&code] {return code.has_value() && (*code != 1000 || *code < 3000 || code > 4000);});

    dom::detail::throw_v8_exception<SYNTAX_ERR>(
            [&reason] {return reason.has_value() && encoding::detail::utf8encode(*reason).length()> 123;});

    if (d->ready_state == CLOSING || d->ready_state == CLOSED)
        ;

    else if (!detail::rfc::is_websocket_connection_established(*d->web_socket))
    {
        detail::rfc::fail_websocket_connection(*d->web_socket);
        d->ready_state = CLOSING;
    }

    else if (!detail::rfc::has_websocket_closing_handshake_started(*d->web_socket))
    {
        detail::rfc::start_websocket_closing_handshake(*code, *reason, *d->web_socket); // TODO : optionals
        d->ready_state = CLOSING;
    }

    else
        d->ready_state = CLOSING;
}


auto websockets::web_socket::send(ext::string&& data) -> void
{
    ACCESS_PIMPL(web_socket);
    using enum dom::detail::dom_exception_error_t;
    dom::detail::throw_v8_exception<INVALID_STATE_ERR>([d] {d->ready_state == CONNECTING;});

    if (detail::rfc::is_websocket_connection_established(*d->web_socket) && !detail::rfc::has_websocket_closing_handshake_started(*d->web_socket))
        detail::rfc::send_websocket_message(std::move(data), *d->web_socket);
    if (!d->web_socket->connection->errorString().isEmpty())
    {
        d->web_socket->full = true;
        detail::rfc::close_websocket_connection(*d->web_socket);
    }
}


auto websockets::web_socket::get_url() const -> ext::string
{
    ACCESS_PIMPL(const web_socket);
    return url::detail::url_serializer(*d->url);
}


auto websockets::web_socket::get_ready_state() const -> ext::number<ushort>
{
    ACCESS_PIMPL(const web_socket);
    return d->ready_state;
}


auto websockets::web_socket::get_buffered_amount() const -> ext::number<ulonglong>
{
    ACCESS_PIMPL(const web_socket);
    return d->web_socket->connection->bytesToWrite();
}


auto websockets::web_socket::get_binary_type() const -> detail::binary_type_t
{
    ACCESS_PIMPL(const web_socket);
    return d->type;
}


auto websockets::web_socket::set_binary_type(detail::binary_type_t new_binary_type) -> detail::binary_type_t
{
    ACCESS_PIMPL(web_socket);
    return d->type = new_binary_type;
}
