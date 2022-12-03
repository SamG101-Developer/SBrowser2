#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_CACHES_CACHE_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_CACHES_CACHE_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "dom_object_private.hpp"

#include INCLUDE_INNER_TYPES(service_workers)


DEFINE_PRIVATE_CLASS(service_workers::caches, cache) : virtual dom_object_private
{
    std::shared_ptr<detail::request_response_list_t> request_response_list;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_CACHES_CACHE_PRIVATE_HPP
