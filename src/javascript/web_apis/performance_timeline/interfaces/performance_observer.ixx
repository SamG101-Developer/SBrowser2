module;
#include "ext/macros.hpp"


export module apis.performance_timeline.performance_observer;
import apis.dom_object;

IMPORT_ALL_TYPES(perfomance_timeline);


DEFINE_PUBLIC_CLASS(performance_timeline, performance_observer) final
        : public virtual dom_object
{
public constructors:
    performance_observer(detail::performance_observer_callback_t&& callback);
    MAKE_PIMPL(performance_observer);
    MAKE_V8_AVAILABLE(WINDOW | WORKER);

private js_methods:
    auto observe(detail::performance_observer_init_t&& options = {}) -> void;
    auto disconnect() -> void;
    auto take_records() -> ext::vector<performance_entry*>;

private js_properties:
    DEFINE_STATIC_GETTER(supported_entry_types, ext::vector_span<ext::string>);
};
