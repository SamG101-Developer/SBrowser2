#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_DETAIL_CACHE_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_DETAIL_CACHE_INTERNALS_HPP

#include "ext/string.hpp"
#include USE_INNER_TYPES(fetch)
#include USE_INNER_TYPES(service_workers)


struct service_workers::detail::cache_batch_operation_t
{
    cache_batch_operation_type_t type;
    fetch::detail::request_t& request;
    fetch::detail::response_t& response;
    detail::cache_query_options_t options;
};

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_DETAIL_CACHE_INTERNALS_HPP
