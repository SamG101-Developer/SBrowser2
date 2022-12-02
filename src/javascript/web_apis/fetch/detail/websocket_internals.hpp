#ifndef SBROWSER2_WEBSOCKET_INTERNALS_HPP
#define SBROWSER2_WEBSOCKET_INTERNALS_HPP

#include "ext/number.ixx"
#include "ext/string.hpp"
#include "ext/vector.hpp"

#include INCLUDE_INNER_TYPES(fetch)
#include INCLUDE_INNER_TYPES(url)

namespace fetch::detail
{
    auto obtain_websocket_connection(
            const url::detail::url_t& url,
            ext::number<int> port)
            -> connection_t;

    auto establish_websocket_connection(
            url::detail::url_t& url,
            ext::vector_view<ext::string> protocols,
            v8::Local<v8::Object> client)
            -> void;
}

#endif //SBROWSER2_WEBSOCKET_INTERNALS_HPP
