#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_INTERSECTION_OBSERVER_INTERSECTION_OBSERVER_ENTRY_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_INTERSECTION_OBSERVER_INTERSECTION_OBSERVER_ENTRY_HPP

#include "dom_object.hpp"
namespace intersection_observer {class intersection_observer_entry;}

#include "ext/map.hpp"
#include "high_resolution_time/_typedefs.hpp"
namespace dom::nodes {class element;}
namespace geometry {class dom_rect_readonly;}


class intersection_observer::intersection_observer_entry
        : public virtual dom_object
{
public constructors:
    intersection_observer_entry(ext::map<ext::string, ext::any>&& init);

public js_properties:
    ext::property<high_resolution_time::dom_high_res_time_stamp_t> time;
    ext::property<geometry::dom_rect_readonly*> root_bounds;
    ext::property<geometry::dom_rect_readonly*> bounding_client_rect;
    ext::property<geometry::dom_rect_readonly*> intersection_rect;
    ext::property<ext::boolean> is_intersecting;
    ext::property<ext::number<double>> intersection_ratio;
    ext::property<dom::nodes::element*> target;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_INTERSECTION_OBSERVER_INTERSECTION_OBSERVER_ENTRY_HPP
