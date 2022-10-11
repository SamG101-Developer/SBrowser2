#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PUSH_API_PUSH_MANAGER_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PUSH_API_PUSH_MANAGER_HPP

// Inheritance Includes & This Class
#include "dom_object.hpp"
namespace push_api {class push_manager;}
namespace push_api {class push_manager_private;}

// Other Includes & Forward Declarations
#include INCLUDE_INNER_TYPES(push_api)
#include "ext/promise.hpp"
#include "ext/span.hpp"
namespace push_api {class push_subscription;}


class push_api::push_manager
        : public dom_object
{
public constructors:
    push_manager();
    MAKE_PIMPL(push_manager);
    MAKE_V8_AVAILABLE;

public js_methods:
    auto subscribe(detail::push_subscription_options_init_t&& options = {}) -> ext::promise<push_subscription*>;

public js_properties:
    DEFINE_STATIC_GETTER(supported_content_encodings, ext::vector_span<ext::string>)
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PUSH_API_PUSH_MANAGER_HPP
