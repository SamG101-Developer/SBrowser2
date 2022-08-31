#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_INTERACTIVE_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_INTERACTIVE_INTERNALS_HPP

#include "ext/boolean.hpp"
namespace html::elements {class html_element;}
namespace html::elements {class html_details_element;}


namespace html::detail
{
    auto details_notifications_task_steps(
            html::elements::html_details_element* element)
            -> void;

    auto ancestor_details_revealing_algorithm(
            html::elements::html_element* element)
            -> void;

    auto is_summary_for_parents_details(
            html::elements::html_element* element)
            -> ext::boolean;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_INTERACTIVE_INTERNALS_HPP
