#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PUSH_API_PUSH_SUBSCRIPTION_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PUSH_API_PUSH_SUBSCRIPTION_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "dom_object_private.hpp"

#include INCLUDE_INNER_TYPES(push_api)
#include "ext/number.hpp"
namespace service_workers::workers {class service_worker_registration;}


DEFINE_PRIVATE_CLASS(push_api, push_subscription_private) : virtual dom_object_private
{
    service_workers::workers::service_worker_registration* registration;
    std::unique_ptr<detail::push_endpoint_t> push_endpoint;
    ext::number<double> subscription_expiration_time;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PUSH_API_PUSH_SUBSCRIPTION_PRIVATE_HPP
