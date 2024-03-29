#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PUSH_API_PUSH_MANAGER_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PUSH_API_PUSH_MANAGER_HPP

// Inheritance Includes & This Class

namespace push_api {class push_manager;}
namespace push_api {class push_manager_private;}

// Other Includes & Forward Declarations
#include INCLUDE_INNER_TYPES(permissions)
#include INCLUDE_INNER_TYPES(push_api)

#include "ext/span.hpp"
namespace push_api {class push_subscription;}


class push_api::push_manager
        : public dom_object
{
public constructors:
    push_manager();
    MAKE_PIMPL(push_manager);
    MAKE_V8_AVAILABLE;

private js_methods:
    auto subscribe(detail::push_subscription_options_init_t&& options = {}) -> ext::promise<push_subscription*>;
    auto get_subscription() -> ext::promise<push_subscription*>;
    auto get_permission_state(detail::push_subscription_options_init_t&& options = {}) -> ext::promise<permissions::detail::permission_state_t>;

private js_properties:
    DEFINE_STATIC_GETTER(supported_content_encodings, ext::vector<ext::string>)
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PUSH_API_PUSH_MANAGER_HPP
