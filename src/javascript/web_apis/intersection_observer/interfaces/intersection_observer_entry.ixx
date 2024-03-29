module;
#include "ext/macros.hpp"


export module apis.intersection_observer.intersection_observer_entry;
import apis.dom_object;


IMPORT_ALL_TYPES(dom);
IMPORT_ALL_TYPES(css.geometry);
IMPORT_ALL_TYPES(hr_time);


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
