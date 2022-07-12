#ifndef SBROWSER2_WEBSOCKET_INTERNALS_HPP
#define SBROWSER2_WEBSOCKET_INTERNALS_HPP

#include "ext/number.hpp"
#include "ext/string.hpp"
#include "ext/vector.hpp"
#include "url/url.hpp"
namespace fetch::detail::connection_internals {class connection;}

namespace fetch::detail::websocket_internals
{
    auto obtain_websocket_connection(
            const url::url_object& url,
            ext::number_view<int> port)
            -> connection_internals::connection;

    auto establish_websocket_connection(
            url::url_object& url,
            ext::string_vector_view protocols,
            v8::Local<v8::Object> client)
            -> void;
}

#endif //SBROWSER2_WEBSOCKET_INTERNALS_HPP
