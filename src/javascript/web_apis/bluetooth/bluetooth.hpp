#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BLUETOOTH_BLUETOOTH_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BLUETOOTH_BLUETOOTH_HPP

#include "dom/nodes/event_target.hpp"
namespace bluetooth {class bluetooth;}

#include "ext/boolean.hpp"
#include "ext/promise.hpp"
#include "ext/vector.hpp"
#include USE_INNER_TYPES(bluetooth)
namespace bluetooth {class bluetooth_device;}


class bluetooth::bluetooth
        : public virtual dom::nodes::event_target
{
public constructors:
    bluetooth() = default;

public js_methods:
    auto get_availability() -> ext::promise<ext::boolean>;
    auto get_devices() -> ext::promise<ext::vector<bluetooth_device*>>;
    auto request_device(detail::request_device_options_t&& options=  {}) -> ext::promise<bluetooth_device*>;

public js_properties:
    ext::property<bluetooth_device*> referring_device;

private js_slots:
    ext::slot<ext::map<detail::bluetooth_device_t*, bluetooth_device*>> s_device_instance_map;
    ext::slot<ext::map<detail::bluetooth_cache_t*, ext::promise<ext::map<ext::string, ext::any>>>> m_attribute_instance_map;
    ext::slot<std::unique_ptr<bluetooth_device>> s_referring_device;

private cpp_accessors:
    DEFINE_GETTER(referring_device) {return s_referring_device().get();};
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BLUETOOTH_BLUETOOTH_HPP
