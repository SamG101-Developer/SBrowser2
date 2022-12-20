module;
#include "ext/macros/annotations.hpp"
#include "ext/macros/pimpl.hpp"
#include "ext/macros/property.hpp"
#include "javascript/macros/expose.hpp"


export module apis.performance_timeline.performance_observer;
import apis.dom_object;
import apis.performance_timeline.types;

import ext.enums;
import ext.string;
import ext.tuple;
import ext.span;
import ext.vector;

import js.env.module_type;

namespace performance_timeline {class performance_entry;}


DEFINE_PUBLIC_CLASS(performance_timeline, performance_observer) final
        : public virtual dom_object
{
public constructors:
    performance_observer(detail::performance_observer_callback_t&& callback);
    MAKE_PIMPL(performance_observer);
    MAKE_V8_AVAILABLE(WINDOW | WORKER);

public js_methods:
    auto observe(detail::performance_observer_init_t&& options = {}) -> void;
    auto disconnect() -> void;
    auto take_records() -> ext::vector<performance_entry*>;

public js_properties:
    DEFINE_STATIC_GETTER(supported_entry_types, ext::vector_span<ext::string>);
};
