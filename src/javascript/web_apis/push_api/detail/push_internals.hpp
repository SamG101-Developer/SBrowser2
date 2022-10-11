#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PUSH_API_DETAIL_PUSH_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PUSH_API_DETAIL_PUSH_INTERNALS_HPP

#include "ext/keywords.hpp"
#include INCLUDE_INNER_TYPES(push_api)
namespace push_api::detail {class push_subscription;}


namespace push_api::detail
{
    auto create_push_subscription(
            push_subscription_options_init_t&& options)
            -> push_subscription;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PUSH_API_DETAIL_PUSH_INTERNALS_HPP
