module;
#include "ext/macros/annotations.hpp"
#include "ext/macros/pimpl.hpp"
#include "ext/macros/property.hpp"
#include "javascript/macros/expose.hpp"


export module apis.aria.mixins.aria_mixin;
import apis.dom_object;

import apis.dom.types;
import ext.core;
import js.env.module_type;


DEFINE_PUBLIC_CLASS(aria::mixins, aria_mixin)
        : public virtual dom_object
{
public constructors:
    MAKE_PIMPL(aria_mixin);
    MAKE_V8_AVAILABLE(ALL);

private js_properties:
    DEFINE_GETTER(role, ext::string);
    DEFINE_GETTER(aria_atomic, ext::string);
    DEFINE_GETTER(aria_auto_complete, ext::string);
    DEFINE_GETTER(aria_busy, ext::string);
    DEFINE_GETTER(aria_checked, ext::string);
    DEFINE_GETTER(area_col_count, ext::string);
    DEFINE_GETTER(aria_col_index, ext::string);
    DEFINE_GETTER(aria_col_index_text, ext::string);
    DEFINE_GETTER(aria_col_span, ext::string);
    DEFINE_GETTER(aria_current, ext::string);
    DEFINE_GETTER(aria_description, ext::string);
    DEFINE_GETTER(aria_disabled, ext::string);
    DEFINE_GETTER(aria_expanded, ext::string);
    DEFINE_GETTER(aria_has_popup, ext::string);
    DEFINE_GETTER(aria_hidden, ext::string);
    DEFINE_GETTER(aria_invalid, ext::string);
    DEFINE_GETTER(aria_key_shortcut, ext::string);
    DEFINE_GETTER(aria_label, ext::string);
    DEFINE_GETTER(aria_level, ext::string);
    DEFINE_GETTER(aria_live, ext::string);
    DEFINE_GETTER(aria_modal, ext::string);
    DEFINE_GETTER(aria_multiline, ext::string);
    DEFINE_GETTER(aria_multi_selectable, ext::string);
    DEFINE_GETTER(aria_orientation, ext::string);
    DEFINE_GETTER(aria_placeholder, ext::string);
    DEFINE_GETTER(aria_pos_in_set, ext::string);
    DEFINE_GETTER(aria_pressed, ext::string);
    DEFINE_GETTER(aria_read_only, ext::string);

    DEFINE_GETTER(aria_required, ext::string);
    DEFINE_GETTER(aria_role_description, ext::string);
    DEFINE_GETTER(aria_row_count, ext::string);
    DEFINE_GETTER(aria_row_index, ext::string);
    DEFINE_GETTER(aria_row_index_text, ext::string);
    DEFINE_GETTER(aria_row_span, ext::string);
    DEFINE_GETTER(aria_selected, ext::string);
    DEFINE_GETTER(aria_set_size, ext::string);
    DEFINE_GETTER(aria_sort, ext::string);
    DEFINE_GETTER(aria_value_max, ext::string);
    DEFINE_GETTER(aria_value_min, ext::string);
    DEFINE_GETTER(aria_value_now, ext::string);
    DEFINE_GETTER(aria_value_text, ext::string);

    DEFINE_GETTER(aria_controls_elements, ext::span<dom::element*>);
    DEFINE_GETTER(aria_described_by_elements, ext::span<dom::element*>);
    DEFINE_GETTER(aria_details_elements, ext::span<dom::element*>);
    DEFINE_GETTER(aria_flow_to_elements, ext::span<dom::element*>);
    DEFINE_GETTER(aria_labelled_by_elements, ext::span<dom::element*>);
    DEFINE_GETTER(aria_owns_elements, ext::span<dom::element*>);

    DEFINE_GETTER(aria_active_descendant_element, dom::element*);
    DEFINE_GETTER(aria_error_message_element, dom::element*);
};
