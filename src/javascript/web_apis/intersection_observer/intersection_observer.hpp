#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_INTERSECTION_OBSERVER_INTERSECTION_OBSERVER_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_INTERSECTION_OBSERVER_INTERSECTION_OBSERVER_HPP

#include "dom_object.hpp"
namespace intersection_observer {class intersection_observer;}
namespace intersection_observer {class intersection_observer_private;}

#include "ext/array.ixx"


#include "ext/span.hpp"

#include "ext/vector.hpp"
#include INCLUDE_INNER_TYPES(intersection_observer)
namespace dom::nodes {class document;}
namespace dom::nodes {class element;}
namespace intersection_observer {class intersection_observer_entry;}


class intersection_observer::intersection_observer
        : public virtual dom_object
{
public constructors:
    intersection_observer(detail::intersection_observer_callback_t&& callback, detail::intersection_observer_init_t&& options = {});
    MAKE_PIMPL(intersection_observer);
    MAKE_V8_AVAILABLE;

public js_methods:
    auto observe(dom::nodes::element* target) -> void;
    auto unobserve(dom::nodes::element* target) -> void;
    auto disconnect() -> void;
    auto take_records() -> ext::vector<intersection_observer_entry*>;

private js_properties:
    DEFINE_GETTER(root, detail::document_or_element_t);
    DEFINE_GETTER(root_margin, ext::string);
    DEFINE_GETTER(thresholds, ext::vector_span<ext::number<double>>);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_INTERSECTION_OBSERVER_INTERSECTION_OBSERVER_HPP
