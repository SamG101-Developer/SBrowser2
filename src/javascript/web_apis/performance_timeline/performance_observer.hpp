#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PERFORMANCE_TIMELINE_PERFORMANCE_OBSERVER_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PERFORMANCE_TIMELINE_PERFORMANCE_OBSERVER_HPP

#include "dom_object.hpp"
namespace performance_timeline {class performance_observer;}

#include INCLUDE_INNER_TYPES(performance_timeline)
namespace performance_timeline {class performance_entry;}


class performance_timeline::performance_observer
        : public virtual dom_object
{
public constructors:
    DOM_CTORS(performance_observer);
    explicit performance_observer(detail::performance_observer_callback_t&& callback);

public js_static_constants:
    static const ext::vector<ext::string> supported_entry_types;

public js_methods:
    auto observer(detail::performance_observer_init_t&& options = {}) -> void;
    auto disconnect() -> void;
    auto take_records() -> ext::vector<performance_entry*>;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PERFORMANCE_TIMELINE_PERFORMANCE_OBSERVER_HPP
