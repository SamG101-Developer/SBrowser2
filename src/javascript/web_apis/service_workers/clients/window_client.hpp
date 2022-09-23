#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_CLIENTS_WINDOW_CLIENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_CLIENTS_WINDOW_CLIENT_HPP

#include "service_workers/clients/client.hpp"
namespace service_workers::clients {class window_client;}

#include "ext/promise.hpp"
#include INCLUDE_INNER_TYPES(html)
#include INCLUDE_INNER_TYPES(page_visibility)

class service_workers::clients::window_client
        : public client
{
public constructors:
    DOM_CTORS(window_client);
    window_client() = default;

public js_methods:
    auto focus() -> ext::promise<window_client*>;
    auto navigate(ext::string_view url) -> ext::promise<window_client*>;

private js_properties:
    ext::property<page_visibility::detail::visibility_state_t> visibility_state;
    ext::property<ext::boolean> focused;
    ext::property<const ext::vector<ext::string>> ancestor_origins;

private cpp_properties:
    std::unique_ptr<detail::service_worker_client_t> m_service_worker_client;
    std::unique_ptr<html::detail::browsing_context_t> m_browsing_context;

private js_properties:
    DEFINE_CUSTOM_GETTER(visibility_state)
    DEFINE_CUSTOM_GETTER(focused)
    DEFINE_CUSTOM_GETTER(ancestor_origins)
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_CLIENTS_WINDOW_CLIENT_HPP
