#ifndef SBROWSER2_ARIA_MIXIN_HPP
#define SBROWSER2_ARIA_MIXIN_HPP

#include "dom_object.hpp"
namespace aria::mixins {class aria_mixin;}
namespace dom::nodes {class element;}

#include "ext/vector.hpp"


class aria::mixins::aria_mixin
        : public virtual dom_object
{
public constructors:
    DOM_CTORS(aria_mixin);

public js_properties:
    ext::property<ext::string> role;
    ext::property<ext::string> aria_atomic;
    ext::property<ext::string> aria_auto_complete;
    ext::property<ext::string> aria_busy;
    ext::property<ext::string> aria_checked;
    ext::property<ext::string> area_col_count;
    ext::property<ext::string> aria_col_index;
    ext::property<ext::string> aria_col_index_text;
    ext::property<ext::string> aria_col_span;
    ext::property<ext::string> aria_current;
    ext::property<ext::string> aria_description;
    ext::property<ext::string> aria_disabled;
    ext::property<ext::string> aria_expanded;
    ext::property<ext::string> aria_has_popup;
    ext::property<ext::string> aria_hidden;
    ext::property<ext::string> aria_invalid;
    ext::property<ext::string> aria_key_shortcut;
    ext::property<ext::string> aria_label;
    ext::property<ext::string> aria_level;
    ext::property<ext::string> aria_live;
    ext::property<ext::string> aria_modal;
    ext::property<ext::string> aria_multiline;
    ext::property<ext::string> aria_multi_selectable;
    ext::property<ext::string> aria_orientation;
    ext::property<ext::string> aria_placeholder;
    ext::property<ext::string> aria_pos_in_set;
    ext::property<ext::string> aria_pressed;
    ext::property<ext::string> aria_read_only;

    ext::property<ext::string> aria_required;
    ext::property<ext::string> aria_role_description;
    ext::property<ext::string> aria_row_count;
    ext::property<ext::string> aria_row_index;
    ext::property<ext::string> aria_row_index_text;
    ext::property<ext::string> aria_row_span;
    ext::property<ext::string> aria_selected;
    ext::property<ext::string> aria_set_size;
    ext::property<ext::string> aria_sort;
    ext::property<ext::string> aria_value_max;
    ext::property<ext::string> aria_value_min;
    ext::property<ext::string> aria_value_now;
    ext::property<ext::string> aria_value_text;

    ext::property<std::unique_ptr<ext::vector<dom::nodes::element*>>> aria_controls_elements;
    ext::property<std::unique_ptr<ext::vector<dom::nodes::element*>>> aria_described_by_elements;
    ext::property<std::unique_ptr<ext::vector<dom::nodes::element*>>> aria_details_elements;
    ext::property<std::unique_ptr<ext::vector<dom::nodes::element*>>> aria_flow_to_elements;
    ext::property<std::unique_ptr<ext::vector<dom::nodes::element*>>> aria_labelled_by_elements;
    ext::property<std::unique_ptr<ext::vector<dom::nodes::element*>>> aria_owns_elements;

    ext::property<std::unique_ptr<dom::nodes::element>> aria_active_descendant_element;
    ext::property<std::unique_ptr<dom::nodes::element>> aria_error_message_element;

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;
};


#endif //SBROWSER2_ARIA_MIXIN_HPP
