#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_CLIENTS_WINDOW_CLIENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_CLIENTS_WINDOW_CLIENT_HPP

#include "service_workers/clients/client.hpp"
namespace service_workers::clients {class window_client;}
namespace service_workers::clients {class window_client_private;}

#include "ext/promise.hpp"
#include "ext/span.hpp"
#include INCLUDE_INNER_TYPES(html)
#include INCLUDE_INNER_TYPES(page_visibility)


class service_workers::clients::window_client
        : public client
{
public constructors:
    window_client();
    MAKE_PIMPL(window_client);
    MAKE_V8_AVAILABLE;

public js_methods:
    auto focus() -> ext::promise<window_client*>;
    auto navigate(ext::string_view url) -> ext::promise<window_client*>;

private js_properties:
    DEFINE_GETTER(visibility_state, page_visibility::detail::visibility_state_t);
    DEFINE_GETTER(focused, ext::boolean);
    DEFINE_GETTER(ancestor_origins, ext::vector_span<ext::string>);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_CLIENTS_WINDOW_CLIENT_HPP
