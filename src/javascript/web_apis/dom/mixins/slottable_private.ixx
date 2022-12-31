module;
#include "ext/macros.hpp"


export module apis.dom.mixins.slottable:p;
import apis.dom_object;

IMPORT_ALL_TYPES(html);


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
