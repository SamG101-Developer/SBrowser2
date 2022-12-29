module;
#include "ext/macros/annotations.hpp"
#include "ext/macros/macros.hpp"
#include "ext/macros/property.hpp"
#include "javascript/macros/expose.hpp"


export module apis.intersection_observer.intersection_observer_entry_private;
import apis.dom_object;

import apis.css.geometry.types;
import apis.dom.types;
import apis.hr_time.types;
import ext.core;
import js.env.module_type;


DEFINE_PUBLIC_CLASS(intersection_observer, intersection_observer_entry) final
        : public virtual dom_object
{
public typedefs:
    using intersection_observer_entry_init_t = ext::map<ext::string, ext::any>;

public constructors:
    intersection_observer_entry(intersection_observer_entry_init_t&& init);
    MAKE_PIMPL(intersection_observer_entry);
    MAKE_V8_AVAILABLE(WINDOW);

private js_properties:
    DEFINE_GETTER(time, hr_time::dom_high_res_time_stamp);
    DEFINE_GETTER(root_bounds, css::geometry::dom_rect_readonly*);
    DEFINE_GETTER(bounding_client_rect, css::geometry::dom_rect_readonly);
    DEFINE_GETTER(intersection_rect, css::geometry::dom_rect_readonly);
    DEFINE_GETTER(is_intersecting, ext::boolean);
    DEFINE_GETTER(intersection_ratio, ext::number<double>);
    DEFINE_GETTER(target, dom::element*);
};
