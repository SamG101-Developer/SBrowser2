#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_DETAIL_CLIENT_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_DETAIL_CLIENT_INTERNALS_HPP

#include "ext/promise.ixx"
#include "ext/string.hpp"
#include INCLUDE_INNER_TYPES(html)
#include INCLUDE_INNER_TYPES(service_workers)
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
            const html::detail::browsing_context_t& browsing_context)
            -> ext::string;

    auto resolve_get_client_promise(
            const service_worker_client_t&,
            ext::promise<void>&& promise)
            -> void;
}


struct service_workers::detail::service_worker_client_t
{
    ext::boolean discarded_flag;
//    client_private() {environment_discarding_steps = [this] {discarded_flag = true;};}
};

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_DETAIL_CLIENT_INTERNALS_HPP
