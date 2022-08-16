#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_INTERSECTION_OBSERVER_INTERSECTION_OBSERVER_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_INTERSECTION_OBSERVER_INTERSECTION_OBSERVER_HPP

#include "dom_object.hpp"
namespace intersection_observer {class intersection_observer;}

#include "ext/functional.hpp"
#include "ext/map.hpp"
#include "ext/string.hpp"
#include "ext/vector.hpp"
#include USE_INNER_TYPES(intersection_observer)
namespace dom::nodes {class element;}
namespace intersection_observer {class intersection_observer_entry;}


class intersection_observer::intersection_observer
        : public virtual dom_object
{
public constructors:
    intersection_observer(intersection_observer_callback&& callback, ext::map<ext::string, ext::any>&& options);

public js_methods:
    auto observe(dom::nodes::element* target) -> void;
    auto unobserve(dom::nodes::element* target) -> void;
    auto disconnect() -> void;
    auto take_records() -> ext::vector<intersection_observer_entry*>;

public js_properties:
    ext::property<ext::variant<dom::nodes::node*, dom::nodes::document*>> root;
    ext::property<ext::string> rot_margin;
    ext::property<ext::vector<ext::number<double>>> threshold;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_INTERSECTION_OBSERVER_INTERSECTION_OBSERVER_HPP
