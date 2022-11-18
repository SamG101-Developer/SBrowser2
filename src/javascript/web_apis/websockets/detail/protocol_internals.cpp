#include "protocol_internals.hpp"

#include "ext/enums.hpp"

#include "fetch/_typedefs.hpp"
#include "fetch/detail/fetch_internals.hpp"
#include "fetch/detail/header_internals.hpp"
#include "fetch/detail/request_internals.hpp"

#include "infra/detail/infra_strings_internals.hpp"
#include "referrer_policy/_typedefs.hpp"
#include "url/detail/url_internals.hpp"

#include <range/v3/view/join.hpp>
#include <qabstractsocket.h>
#include <qsslconfiguration.h>
#include <qurl.h>
#include <qwebsocket.h>
#include <qwebsocketprotocol.h>


auto websockets::detail::obtain_websocket_connection(
        const url::detail::url_t& url)
        -> ext::expected<std::unique_ptr<websocket_t>>
{
    auto resource_name = u'/'
            + (ranges::views::join(url.path, u'/') | ranges::to<ext::string>())
            + (!url.query.empty() ? u'?' + url.query : u"");

    auto secure = url.scheme != u"http";

    /* ↓ [RFC-6455] ↓ */
    auto qt_websocket = std::make_unique<QWebSocket>();
    auto qt_url = QUrl{};

    qt_url.setHost(QString::fromStdU16String(url.host));
    qt_url.setPort(url.port);
    qt_websocket->open(qt_url);

    // TODO : Steps 2, 3

    if (!qt_websocket->isValid())
        qt_websocket->close(QWebSocketProtocol::CloseCodeNormal);

    if (secure)
        qt_websocket->setSslConfiguration(QSslConfiguration{});

    if (qt_websocket->error() & (QAbstractSocket::SslInternalError | QAbstractSocket::SslInvalidUserDataError))
        qt_websocket->close(QWebSocketProtocol::CloseCodeTlsHandshakeFailed);

    /* ↑ [RFC-6455] ↑ */

    auto websocket = std::make_unique<websocket_t>();
    websocket->socket = std::move(qt_websocket);
    return websocket;
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
            ; // TODO : fail the websocket connection

        if (!protocols.empty() && fetch::detail::extract_header_list_values(u"Sec-WebSocket-Protocol", request->header_list) /* TODO : null / failure */)
            ; // TODO : fail the websocket connection

        // TODO
            };

    fetch::detail::fetch(*request, nullptr, nullptr, nullptr, std::move(process_response), nullptr, nullptr, true);
}
