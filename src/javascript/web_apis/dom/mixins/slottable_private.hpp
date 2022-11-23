#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_MIXINS_SLOTTABLE_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_MIXINS_SLOTTABLE_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "dom_object_private.hpp"

namespace html::elements {class html_slot_element;}


DEFINE_PRIVATE_CLASS(dom::mixins, slottable)
        : virtual dom_object_private
{
    MAKE_QIMPL(slottable);

    ext::string name;
    std::observer_ptr<html::elements::html_slot_element> assigned_slot;
    std::observer_ptr<html::elements::html_slot_element> manual_slot_assignment;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_MIXINS_SLOTTABLE_PRIVATE_HPP
