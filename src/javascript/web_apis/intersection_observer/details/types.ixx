module;
#include "ext/macros/macros.hpp"
#include <function2/function2.hpp>
#include <swl/variant.hpp>


export module apis.intersection_observer.types;
import apis.dom.types;
import ext.core;


DEFINE_FWD_DECL_NAMESPACE(intersection_observer)
{
    class intersection_observer;
    class intersection_observer_entry;
}


DEFINE_FWD_DECL_NAMESPACE_DETAIL(intersection_observer)
{
    struct intersection_observer_registration_t;

    using document_or_element_t = ext::variant<dom::document*, dom::element*>;
}


struct intersection_observer::detail::intersection_observer_registration_t
{
    std::observer_ptr<intersection_observer> observer;
    ext::number<int> previous_threshold_index;
    ext::boolean previous_is_intersecting;
};
