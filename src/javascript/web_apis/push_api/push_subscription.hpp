#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PUSH_API_PUSH_SUBSCRIPTION_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PUSH_API_PUSH_SUBSCRIPTION_HPP

// Inheritance Includes & This Class
#include "dom_object.hpp"
namespace push_api {class push_subscription;}
namespace push_api {class push_subscription_private;}

// Other Includes & Forward Declarations
#include INCLUDE_INNER_TYPES(hr_time)
#include INCLUDE_INNER_TYPES(push_api)
#include "ext/any.hpp"
#include "ext/boolean.hpp"
#include "ext/promise.hpp"
#include "ext/span.hpp"
#include <v8-forward.h>


class push_api::push_subscription
        : virtual public dom_object
{
public constructors:
    MAKE_PIMPL(push_subscription);
    MAKE_V8_AVAILABLE;
    MAKE_STRINGIFIER;

public js_methods:
    auto get_key(detail::push_encryption_key_name_t name) -> v8::Local<v8::ArrayBuffer>;
    auto unsubscribe() -> ext::promise<ext::boolean>;

public js_properties:
    DEFINE_GETTER(endpoint, ext::string);
    DEFINE_GETTER(expiration_time, hr_time::epoch_time_stamp);
    DEFINE_GETTER(options, ext::map_span<ext::string COMMA ext::any>);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PUSH_API_PUSH_SUBSCRIPTION_HPP
