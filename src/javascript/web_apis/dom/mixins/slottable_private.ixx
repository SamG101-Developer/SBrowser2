module;
#include "ext/macros/pimpl.hpp"


export module apis.dom.mixins.slottable_private;
import apis._.dom_object_private;
import ext.memory;
import ext.string;

namespace html {class html_slot_element;}


DEFINE_PRIVATE_CLASS(dom, slottable)
        : virtual dom_object_private
{
    MAKE_QIMPL(slottable);

    ext::string name;
    std::observer_ptr<html::html_slot_element> assigned_slot;
    std::observer_ptr<html::html_slot_element> manual_slot_assignment;
};
