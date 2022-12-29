module;
#include "ext/macros/pimpl.hpp"


export module apis.dom.mixins.slottable_private;
import apis.dom_object_private;

import apis.html.types;
import ext.core;


DEFINE_PRIVATE_CLASS(dom::mixins, slottable)
        : virtual dom_object_private
{
public:
    MAKE_QIMPL(slottable);

public:
    ext::string name;
    std::observer_ptr<html::html_slot_element> assigned_slot;
    std::observer_ptr<html::html_slot_element> manual_slot_assignment;
};
