#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_DETAIL_CLIENT_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_DETAIL_CLIENT_INTERNALS_HPP

#include <future>
#include "ext/string.hpp"
#include USE_INNER_TYPES(dom)
#include USE_INNER_TYPES(service_workers)
namespace service_workers::clients {class client;}
namespace service_workers::clients {class window_client;}


namespace service_workers::detail
{
    auto create_clint(
            const service_worker_client_t& client)
            -> clients::client;

    auto create_window_client(
            const service_worker_client_t& client)
            -> clients::window_client;

    auto get_frame_type(
            const dom::detail::browsing_context_t& browsing_context)
            -> ext::string;

    auto resolve_get_client_promise(
            const service_worker_client_t&,
            std::promise<void>&& promise)
            -> void;
}

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_DETAIL_CLIENT_INTERNALS_HPP
