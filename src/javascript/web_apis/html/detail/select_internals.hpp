#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_SELECT_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_SELECT_INTERNALS_HPP

#include "ext/boolean.hpp"
#include "ext/number.hpp"
#include "ext/vector.hpp"
namespace html::elements {class html_option_element;}
namespace html::elements {class html_output_element;}
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
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_SELECT_INTERNALS_HPP
