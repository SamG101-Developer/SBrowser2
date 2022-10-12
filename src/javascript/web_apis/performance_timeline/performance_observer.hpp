#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PERFORMANCE_TIMELINE_PERFORMANCE_OBSERVER_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PERFORMANCE_TIMELINE_PERFORMANCE_OBSERVER_HPP

#include "dom_object.hpp"
namespace performance_timeline {class performance_observer;}
namespace performance_timeline {class performance_observer_private;}

#include INCLUDE_INNER_TYPES(performance_timeline)
namespace performance_timeline {class performance_entry;}


class performance_timeline::performance_observer
        : public virtual dom_object
{
public constructors:
    performance_observer(detail::performance_observer_callback_t&& callback);
    DOM_CTORS(performance_observer);
    MAKE_PIMPL(performance_observer);
    MAKE_V8_AVAILABLE;

public js_methods:
    auto observe(detail::performance_observer_init_t&& options = {}) -> void;
    auto disconnect() -> void;
    auto take_records() -> ext::vector<performance_entry*>;

public js_properties:
    DEFINE_STATIC_GETTER(supported_entry_types, ext::vector<ext::string>);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PERFORMANCE_TIMELINE_PERFORMANCE_OBSERVER_HPP
