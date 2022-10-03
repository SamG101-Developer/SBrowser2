#ifndef SBROWSER2_SLOTTABLE_HPP
#define SBROWSER2_SLOTTABLE_HPP

#include "dom_object.hpp"
namespace dom::mixins {class slottable;}
namespace dom::mixins {class slottable_private;}

namespace html::elements {class html_slot_element;}


class dom::mixins::slottable
        : public virtual dom_object
{
public constructors:
    slottable();
    MAKE_PIMPL(slottable);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(assigned_slot, html::elements::html_slot_element*);
};


#endif //SBROWSER2_SLOTTABLE_HPP
