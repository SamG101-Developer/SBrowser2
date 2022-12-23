module;
#include "ext/macros/pimpl.hpp"


export module apis.intersection_observer.intersection_observer_entry_private;
import apis.dom_object_private;

import apis.intersection_observer.types;
import ext.core;


DEFINE_PRIVATE_CLASS(intersection_observer, intersection_observer_entry)
        : virtual dom_object_private
{
    std::observer_ptr<dom::nodes::element> target;
    std::observer_ptr<intersection_observer> observer;
};
