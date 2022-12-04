#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_FORM_CONTROLLED_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_FORM_CONTROLLED_INTERNALS_HPP


#include "ext/number.ixx"
#include "ext/vector.hpp"

#include USE_CONCEPTS(html)

namespace html::elements {class html_field_set_element;}
namespace html::elements {class html_option_element;}
namespace html::elements {class html_output_element;}
namespace html::elements {class html_progress_element;}
namespace html::elements {class html_select_element;}
namespace html::elements {class html_text_area_element;}


namespace html::detail
{
    auto display_size(
            elements::html_select_element* element)
            -> ext::number<int>;

    auto list_of_options(
            elements::html_select_element* element)
            -> ext::vector<elements::html_option_element*>;

    auto placeholder_label_option(
            elements::html_select_element* element)
            -> html::elements::html_option_element*;

    auto selectedness_settings_algorithm(
            elements::html_select_element* element)
            -> void;

    auto ask_for_reset(
            elements::html_option_element* element)
            -> void;

    auto send_select_update_notifications(
            elements::html_select_element* element)
            -> void;

    auto reset_algorithm(
            elements::html_select_element* element)
            -> void;

    auto reset_algorithm(
            elements::html_output_element* element)
            -> void;

    auto is_mutable(
            elements::html_select_element* element)
            -> ext::boolean;

    auto character_width(
            elements::html_text_area_element* element)
            -> ext::number<int>;

    auto character_height(
            elements::html_text_area_element* element)
            -> ext::number<int>;

    auto text_area_wrapping_transformation(
            elements::html_text_area_element* element)
            -> void;

    auto current_value(
            html::elements::html_progress_element* element)
            -> ext::number<double>;

    auto is_disabled_field_set(
            html::elements::html_field_set_element* element)
            -> ext::boolean;

    auto is_disabled_form_control(
            concepts::form_associated auto* element)
            -> ext::boolean;

    auto reset_form_owner(
            concepts::form_associated auto* element)
            -> void;

    auto autofill_hint_set(
            concepts::form_associated auto* element)
            -> void;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_FORM_CONTROLLED_INTERNALS_HPP
