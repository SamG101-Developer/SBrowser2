#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_INTERSECTION_OBSERVER_INTERSECTION_OBSERVER_ENTRY_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_INTERSECTION_OBSERVER_INTERSECTION_OBSERVER_ENTRY_HPP

#include "dom_object.hpp"
namespace intersection_observer {class intersection_observer_entry;}

#include "ext/map.hpp"
#include INCLUDE_INNER_TYPES(hr_time)
#include INCLUDE_INNER_TYPES(intersection_observer)
namespace dom::nodes {class element;}
namespace css::geometry {class dom_rect_readonly;}

#include "intersection_observer_entry_private.hpp"


class intersection_observer::intersection_observer_entry
        : public virtual dom_object
{
public constructors:
    MAKE_PIMPL(intersection_observer_entry);
    intersection_observer_entry(detail::intersection_observer_entry_init_t&& init);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(time, hr_time::dom_high_res_time_stamp);
    DEFINE_GETTER(root_bounds, css::geometry::dom_rect_readonly*);
    DEFINE_GETTER(bounding_client_rect, css::geometry::dom_rect_readonly);
    DEFINE_GETTER(intersection_rect, css::geometry::dom_rect_readonly);
    DEFINE_GETTER(is_intersecting, ext::boolean);
    DEFINE_GETTER(intersection_ratio, ext::number<double>);
    DEFINE_GETTER(target, dom::nodes::element*);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_INTERSECTION_OBSERVER_INTERSECTION_OBSERVER_ENTRY_HPP
