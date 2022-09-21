#ifndef SBROWSER2_SLOTTABLE_HPP
#define SBROWSER2_SLOTTABLE_HPP

#include "dom_object.hpp"
namespace dom::mixins {class slottable;}

namespace html::elements {class html_slot_element;}


class dom::mixins::slottable
        : public virtual dom_object
{
public friends:
    friend class html::elements::html_slot_element;

public constructors:
    slottable();

public js_properties:
    ext::property<std::unique_ptr<html::elements::html_slot_element>> assigned_slot;

private cpp_members:
    MAKE_V8_AVAILABLE;

private cpp_accessors:
    DEFINE_CUSTOM_GETTER(assigned_slot);
};


#endif //SBROWSER2_SLOTTABLE_HPP
