module;
#include "javascript/macros/expose.hpp"


module apis.aria.mixins.aria_mixin;

import ext.core;
import js.env.module_type;


auto aria::mixins::aria_mixin::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<this_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<dom_object>()
        .property("role", &aria_mixin::get_role)
        .property("ariaAtomic", &aria_mixin::get_aria_atomic)
        .property("ariaAutoComplete", &aria_mixin::get_aria_auto_complete)
        .property("ariaBusy", &aria_mixin::get_aria_busy)
        .property("ariaChecked", &aria_mixin::get_aria_checked)
        .property("areaColCount", &aria_mixin::get_area_col_count)
        .property("ariaColIndex", &aria_mixin::get_aria_col_index)
        .property("ariaColIndexText", &aria_mixin::get_aria_col_index_text)
        .property("ariaColSpan", &aria_mixin::get_aria_col_span)
        .property("ariaCurrent", &aria_mixin::get_aria_current)
        .property("ariaDescription", &aria_mixin::get_aria_description)
        .property("ariaDisabled", &aria_mixin::get_aria_disabled)
        .property("ariaExpanded", &aria_mixin::get_aria_expanded)
        .property("ariaHasPopup", &aria_mixin::get_aria_has_popup)
        .property("ariaHidden", &aria_mixin::get_aria_hidden)
        .property("ariaInvalid", &aria_mixin::get_aria_invalid)
        .property("ariaKeyShortcut", &aria_mixin::get_aria_key_shortcut)
        .property("ariaLabel", &aria_mixin::get_aria_label)
        .property("ariaLevel", &aria_mixin::get_aria_level)
        .property("ariaLive", &aria_mixin::get_aria_live)
        .property("ariaModal", &aria_mixin::get_aria_modal)
        .property("ariaMultiline", &aria_mixin::get_aria_multiline)
        .property("ariaMultiSelectable", &aria_mixin::get_aria_multi_selectable)
        .property("ariaOrientation", &aria_mixin::get_aria_orientation)
        .property("ariaPlaceholder", &aria_mixin::get_aria_placeholder)
        .property("ariaPosInSet", &aria_mixin::get_aria_pos_in_set)
        .property("ariaPressed", &aria_mixin::get_aria_pressed)
        .property("ariaReadOnly", &aria_mixin::get_aria_read_only)
        .property("ariaRequired", &aria_mixin::get_aria_required)
        .property("ariaRoleDescription", &aria_mixin::get_aria_role_description)
        .property("ariaRowCount", &aria_mixin::get_aria_row_count)
        .property("ariaRowIndex", &aria_mixin::get_aria_row_index)
        .property("ariaRowIndexText", &aria_mixin::get_aria_row_index_text)
        .property("ariaRowSpan", &aria_mixin::get_aria_row_span)
        .property("ariaSelected", &aria_mixin::get_aria_selected)
        .property("ariaSetSize", &aria_mixin::get_aria_set_size)
        .property("ariaSort", &aria_mixin::get_aria_sort)
        .property("ariaValueMax", &aria_mixin::get_aria_value_max)
        .property("ariaValueMin", &aria_mixin::get_aria_value_min)
        .property("ariaValueNow", &aria_mixin::get_aria_value_now)
        .property("ariaValueText", &aria_mixin::get_aria_value_text)
        .property("ariaControlsElements", &aria_mixin::get_aria_controls_elements)
        .property("ariaDescribedByElements", &aria_mixin::get_aria_described_by_elements)
        .property("ariaDetailsElements", &aria_mixin::get_aria_details_elements)
        .property("ariaFlowToElements", &aria_mixin::get_aria_flow_to_elements)
        .property("ariaLabelledByElements", &aria_mixin::get_aria_labelled_by_elements)
        .property("ariaOwnsElements", &aria_mixin::get_aria_owns_elements)
        .property("ariaActiveDescendantElement", &aria_mixin::get_aria_active_descendant_element)
        .property("ariaErrorMessageElement", &aria_mixin::get_aria_error_message_element)
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}
