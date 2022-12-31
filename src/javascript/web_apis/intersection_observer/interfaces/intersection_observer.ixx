module;
#include "ext/macros.hpp"


export module apis.intersection_observer.intersection_observer;
import apis.dom_object;

IMPORT_ALL_TYPES(dom);
IMPORT_ALL_TYPES(intersection_observer);


DEFINE_PUBLIC_CLASS(intersection_observer, intersection_observer) final
        : public virtual dom_object
{
public typedefs:
    using intersection_observer_callback_t = ext::function<void(ext::vector<intersection_observer_entry*>, intersection_observer*)>;
    using intersection_observer_init_t = ext::map<ext::string, ext::any>;

public constructors:
    intersection_observer(intersection_observer_callback_t&& callback, intersection_observer_init_t&& options = {});
    MAKE_PIMPL(intersection_observer);
    MAKE_V8_AVAILABLE(WINDOW);

public js_methods:
    auto observe(dom::element* target) -> void;
    auto unobserve(dom::element* target) -> void;
    auto disconnect() -> void;
    auto take_records() -> ext::vector<intersection_observer_entry*>;

private js_properties:
    DEFINE_GETTER(root, detail::document_or_element_t);
    DEFINE_GETTER(root_margin, ext::string);
    DEFINE_GETTER(thresholds, ext::span<ext::number<double>>);
};
