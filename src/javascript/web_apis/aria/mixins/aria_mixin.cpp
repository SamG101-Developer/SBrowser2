#include "aria_mixin.hpp"
#include "aria_mixin_private.hpp"


auto aria::mixins::aria_mixin::to_v8(
        v8::Isolate* isolate)
        -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<aria_mixin>{isolate}
        .inherit<dom_object>()
        .var("role", &aria_mixin::role, false)
        .var("ariaAtomic", &aria_mixin::aria_atomic, false)
        .var("ariaAutoComplete", &aria_mixin::aria_auto_complete, false)
        .var("ariaBusy", &aria_mixin::aria_busy, false)
        .var("ariaChecked", &aria_mixin::aria_checked, false)
        .var("areaColCount", &aria_mixin::area_col_count, false)
        .var("ariaColIndex", &aria_mixin::aria_col_index, false)
        .var("ariaColIndexText", &aria_mixin::aria_col_index_text, false)
        .var("ariaColSpan", &aria_mixin::aria_col_span, false)
        .var("ariaCurrent", &aria_mixin::aria_current, false)
        .var("ariaDescription", &aria_mixin::aria_description, false)
        .var("ariaDisabled", &aria_mixin::aria_disabled, false)
        .var("ariaExpanded", &aria_mixin::aria_expanded, false)
        .var("ariaHasPopup", &aria_mixin::aria_has_popup, false)
        .var("ariaHidden", &aria_mixin::aria_hidden, false)
        .var("ariaInvalid", &aria_mixin::aria_invalid, false)
        .var("ariaKeyShortcut", &aria_mixin::aria_key_shortcut, false)
        .var("ariaLabel", &aria_mixin::aria_label, false)
        .var("ariaLevel", &aria_mixin::aria_level, false)
        .var("ariaLive", &aria_mixin::aria_live, false)
        .var("ariaModal", &aria_mixin::aria_modal, false)
        .var("ariaMultiline", &aria_mixin::aria_multiline, false)
        .var("ariaMultiSelectable", &aria_mixin::aria_multi_selectable, false)
        .var("ariaOrientation", &aria_mixin::aria_orientation, false)
        .var("ariaPlaceholder", &aria_mixin::aria_placeholder, false)
        .var("ariaPosInSet", &aria_mixin::aria_pos_in_set, false)
        .var("ariaPressed", &aria_mixin::aria_pressed, false)
        .var("ariaReadOnly", &aria_mixin::aria_read_only, false)
        .var("ariaRequired", &aria_mixin::aria_required, false)
        .var("ariaRoleDescription", &aria_mixin::aria_role_description, false)
        .var("ariaRowCount", &aria_mixin::aria_row_count, false)
        .var("ariaRowIndex", &aria_mixin::aria_row_index, false)
        .var("ariaRowIndexText", &aria_mixin::aria_row_index_text, false)
        .var("ariaRowSpan", &aria_mixin::aria_row_span, false)
        .var("ariaSelected", &aria_mixin::aria_selected, false)
        .var("ariaSetSize", &aria_mixin::aria_set_size, false)
        .var("ariaSort", &aria_mixin::aria_sort, false)
        .var("ariaValueMax", &aria_mixin::aria_value_max, false)
        .var("ariaValueMin", &aria_mixin::aria_value_min, false)
        .var("ariaValueNow", &aria_mixin::aria_value_now, false)
        .var("ariaValueText", &aria_mixin::aria_value_text, false)
        .var("ariaControlsElements", &aria_mixin::aria_controls_elements, false)
        .var("ariaDescribedByElements", &aria_mixin::aria_described_by_elements, false)
        .var("ariaDetailsElements", &aria_mixin::aria_details_elements, false)
        .var("ariaFlowToElements", &aria_mixin::aria_flow_to_elements, false)
        .var("ariaLabelledByElements", &aria_mixin::aria_labelled_by_elements, false)
        .var("ariaOwnsElements", &aria_mixin::aria_owns_elements, false)
        .var("ariaActiveDescendantElement", &aria_mixin::aria_active_descendant_element, false)
        .var("ariaErrorMessageElement", &aria_mixin::aria_error_message_element, false)
        .auto_wrap_objects();

    return std::move(conversion);
}
