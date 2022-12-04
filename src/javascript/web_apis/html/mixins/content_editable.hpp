#pragma once
#ifndef SBROWSER2_CONTENT_EDITABLE_HPP
#define SBROWSER2_CONTENT_EDITABLE_HPP

#include "dom_object.hpp"
namespace html::mixins {class content_editable;}
namespace html::mixins {class content_editable_private;}


#include INCLUDE_INNER_TYPES(html)
#include INCLUDE_INNER_TYPES(virtual_keyboard)


class html::mixins::content_editable
        : public virtual dom_object
{
public constructors:
    content_editable();
    MAKE_PIMPL(content_editable);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(is_content_editable, ext::boolean);
    DEFINE_GETTER(content_editable, ext::string);
    DEFINE_GETTER(enter_key_hit, detail::editable_enter_key_hit_t);
    DEFINE_GETTER(input_mode, detail::editable_input_mode_t);

    DEFINE_SETTER(content_editable, ext::string);
    DEFINE_SETTER(enter_key_hit, detail::editable_enter_key_hit_t);
    DEFINE_SETTER(input_mode, detail::editable_input_mode_t);

    /* [VIRTUAL-KEYBOARD] */
    DEFINE_GETTER(virtual_keyboard_policy, virtual_keyboard::detail::policy_t);
};


#endif //SBROWSER2_CONTENT_EDITABLE_HPP
