#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_INTERSECTION_OBSERVER_INTERSECTION_OBSERVER_ENTRY_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_INTERSECTION_OBSERVER_INTERSECTION_OBSERVER_ENTRY_HPP

#include "dom_object.hpp"
namespace intersection_observer {class intersection_observer_entry;}

#include "ext/map.hpp"
#include INCLUDE_INNER_TYPES(hr_time)
namespace dom::nodes {class element;}
namespace geometry {class dom_rect_readonly;}


class intersection_observer::intersection_observer_entry
        : public virtual dom_object
{
public constructors:
    intersection_observer_entry() = default;
    intersection_observer_entry(ext::map<ext::string, ext::any>&& init);

private js_properties:
    ext::property<hr_time::dom_high_res_time_stamp> time;
    ext::property<geometry::dom_rect_readonly*> root_bounds;
    ext::property<geometry::dom_rect_readonly*> bounding_client_rect;
    ext::property<geometry::dom_rect_readonly*> intersection_rect;
    ext::property<ext::boolean> is_intersecting;
    ext::property<ext::number<double>> intersection_ratio;
    ext::property<dom::nodes::element*> target;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_INTERSECTION_OBSERVER_INTERSECTION_OBSERVER_ENTRY_HPP
