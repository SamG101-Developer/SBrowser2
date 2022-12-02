#include "rfc6455_internals.hpp"

#include "ext/enums.ixx"

#include "fetch/_typedefs.hpp"
#include "fetch/detail/fetch_internals.hpp"
#include "fetch/detail/header_internals.hpp"
#include "fetch/detail/request_internals.hpp"

#include "infra/detail/infra_strings_internals.hpp"
#include "referrer_policy/_typedefs.hpp"
#include "url/detail/url_internals.hpp"

#include <range/v3/view/join.hpp>
#include <range/v3/algorithm/any_of.hpp>
#include <qabstractsocket.h>
#include <qsslconfiguration.h>
#include <qurl.h>
#include <qwebsocket.h>
#include <qwebsocketprotocol.h>


auto websockets::detail::rfc::establish_websocket_connection(
        const ext::string& host,
        ext::number<ushort> port,
        ext::string_view resource_name,
        ext::boolean secure)
        -> std::unique_ptr<websocket_t>
{
    auto url = QUrl{};
    url.setHost(QString::fromStdU16String(host));
    url.setPort(port);

    if (!url.isValid())
        fail_websocket_connection();

    if (ranges::any_of(websocket_t::connections, [&host, port](websocket_t* w) {return w->connection->requestUrl().host().toStdU16String() == host && w->connection->requestUrl().port() == port;}))
        fail_websocket_connection(); // TODO : wait for that connection to establish or fail

    auto connection = std::make_unique<QWebSocket>();
    connection->open(url);
    if (!connection->isValid())
        fail_websocket_connection();

    if (secure)
        perform_tls_handshake();

    if (connection->error() & (QAbstractSocket::SslInternalError | QAbstractSocket::SslInvalidUserDataError))
        fail_websocket_connection();

    auto websocket = std::make_unique<websocket_t>();
    websocket->connection = std::move(connection);

    return websocket;
}


auto websockets::detail::obtain_websocket_connection(
        const url::detail::url_t& url)
        -> ext::expected<std::unique_ptr<websocket_t>>
{
    auto path = ranges::views::join(url.path, u'/') | ranges::to<ext::string>();
    auto query = !url.query.empty() ? u'?' + url.query : u"";
    auto resource_name = u'/' + std::move(path) + std::move(query);
    auto secure = url.scheme != u"http";

    return rfc::establish_websocket_connection(url.host, url.port, resource_name, secure);
}


auto websockets::detail::establish_websocket_connection(
        const url::detail::url_t& url,
        ext::vector<ext::string>&& protocols,
        v8::Local<v8::Object> client)
        -> void
{
    auto request_url = std::make_unique<url::detail::url_t>(url);
    request_url->scheme = url.scheme == u"ws" ? u"http" : u"https";

    auto request = std::make_unique<fetch::detail::request_t>();
    request->url = std::move(request_url);
    request->client = client;
    request->service_workers_mode = fetch::detail::service_workers_mode_t::NONE;
    request->referrer = fetch::detail::referrer_t::NO_REFERRER;
    request->mode = fetch::detail::mode_t::WEBSOCKET;
    request->credentials_mode = fetch::detail::credentials_t::INCLUDE;
    request->cache_mode = fetch::detail::cache_t::NO_STORE;
    request->redirect_mode = fetch::detail::redirect_t::ERROR;

    using namespace ext::literals;
    fetch::detail::append_header(ext::make_pair(u"Upgrade"_s16, u"websocket"_s16), request->header_list);
    fetch::detail::append_header(ext::make_pair(u"Connection"_s16, u"Upgrade"_s16), request->header_list);

    auto key_value = infra::detail::isomorphic_encode(infra::detail::base64_encode());
    fetch::detail::append_header(ext::make_pair(u"Sec-WebSocket-Key"_s16, std::move(key_value)), request->header_list);
    fetch::detail::append_header(ext::make_pair(u"Sec-WebSocket-Version"_s16, ext::to_string(13)), request->header_list);

    for (decltype(auto) protocol: protocols)
        fetch::detail::combine_header(ext::make_pair(u"Sec-WebSocket-Protocol"_s16, std::move(protocol)), request->header_list);

    auto premessage_deflate = fetch::detail::header_value_t{/* TODO */};
    fetch::detail::append_header(ext::make_pair(u"Sec-WebSocket-Extensions"_s16, std::move(premessage_deflate)), request->header_list);

    auto process_response =
            [&request](fetch::detail::response_t& response)
            {
        if (fetch::detail::is_network_error(response) || response.status != 101)
            rfc::fail_websocket_connection();

        if (!protocols.empty() && fetch::detail::extract_header_list_values(u"Sec-WebSocket-Protocol", request->header_list) /* TODO : null / failure */)
            rfc::fail_websocket_connection();

        // TODO
            };

    fetch::detail::fetch(*request, nullptr, nullptr, nullptr, std::move(process_response), nullptr, nullptr, true);
}
