#ifndef SBROWSER2_WEBSOCKET_INTERNALS_HPP
#define SBROWSER2_WEBSOCKET_INTERNALS_HPP

#include "ext/number.hpp"
#include "ext/string.hpp"
#include "ext/vector.hpp"
#include "url/url.hpp"

#include USE_INNER_TYPES(fetch)

namespace fetch::detail
{
    auto obtain_websocket_connection(
            const url::url_object& url,
            const ext::number<int>& port)
            -> connection_t;

    auto establish_websocket_connection(
            url::url_object& url,
            ext::vector_view<ext::string> protocols,
            v8::Local<v8::Object> client)
            -> void;
}

#endif //SBROWSER2_WEBSOCKET_INTERNALS_HPP
