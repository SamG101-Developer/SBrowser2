#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_INTERSECTION_OBSERVER_INTERSECTION_OBSERVER_ENTRY_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_INTERSECTION_OBSERVER_INTERSECTION_OBSERVER_ENTRY_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "dom_object_private.hpp"

#include "ext/memory.hpp"
namespace dom::nodes {class element;}
namespace intersection_observer {class intersection_observer;}



DEFINE_PRIVATE_CLASS(intersection_observer, intersection_observer_entry) : virtual dom_object_private
{
    std::observer_ptr<dom::nodes::element> target = nullptr;
    std::observer_ptr<intersection_observer> observer;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_INTERSECTION_OBSERVER_INTERSECTION_OBSERVER_ENTRY_PRIVATE_HPP
