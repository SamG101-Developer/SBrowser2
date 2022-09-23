#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_OTHER_NAVIGATION_PRELOAD_MANAGER_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_OTHER_NAVIGATION_PRELOAD_MANAGER_HPP

#include "dom_object.hpp"
namespace service_workers::other {class navigation_preload_manager;}

#include "ext/promise.hpp"

class service_workers::other::navigation_preload_manager
{
public constructors:
    DOM_CTORS(navigation_preload_manager);
    navigation_preload_manager() = default;

private js_properties:
    auto enable() -> ext::promise<void>;
    auto disable() -> ext::promise<void>;
    auto set_header_value(ext::string_view value) -> ext::promise<void>;
    auto get_state() -> ext::promise<detail::navigation_preload_state_t>;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_OTHER_NAVIGATION_PRELOAD_MANAGER_HPP
