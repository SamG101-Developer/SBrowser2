#ifndef SBROWSER2_DOCUMENT_INTERNALS_HPP
#define SBROWSER2_DOCUMENT_INTERNALS_HPP

#include "ext/boolean.hpp"
#include INCLUDE_INNER_TYPES(html)
#include INCLUDE_INNER_TYPES(hr_time)

namespace dom::nodes {class document; class node;}
namespace html::elements {class html_meta_element;}

namespace html::detail
{
    auto node_is_browsing_context_connected(
            dom::nodes::node* node)
            -> ext::boolean;

    auto is_cookie_averse_document(
            const dom::nodes::document* document)
            -> ext::boolean;

    auto fallback_base_url(
            const dom::nodes::document* document)
            -> ext::string;

    auto document_base_url(
            const dom::nodes::document* document)
            -> ext::string;

    auto shared_declarative_refresh_steps(
            const dom::nodes::document* document,
            ext::string&& input,
            elements::html_meta_element* meta = nullptr)
            -> void;

    auto has_stylesheet_blocking_scripts(
            const dom::nodes::document* document)
            -> ext::boolean;

    auto has_no_stylesheet_blocking_scripts(
            const dom::nodes::document* document)
            -> ext::boolean;

    auto completely_loaded(
            const dom::nodes::document* document)
            -> ext::boolean;

    auto completely_finish_loading(
            const dom::nodes::document* document)
            -> void;

    auto allowed_to_use(
            dom::nodes::document* document,
            ext::string_view feature)
            -> ext::boolean;

    auto appropriate_template_contents_owner_document(
            dom::nodes::document* document)
            -> dom::nodes::document*;

    auto is_blocked_by_modal_dialog(
            dom::nodes::document* document)
            -> ext::boolean;
}


struct html::detail::document_load_timing_info_t
{
    ext::number<int> navigation_start_time;
    hr_time::dom_high_res_time_stamp dom_interactive_time;
    hr_time::dom_high_res_time_stamp dom_content_loaded_event_start_time;
    hr_time::dom_high_res_time_stamp dom_content_loaded_event_end_time;
    hr_time::dom_high_res_time_stamp dom_complete_time;
    hr_time::dom_high_res_time_stamp load_event_start_time;
    hr_time::dom_high_res_time_stamp load_event_unload_time;
};


struct html::detail::document_unload_timing_info_t
{
    hr_time::dom_high_res_time_stamp unload_event_start_time;
    hr_time::dom_high_res_time_stamp unload_event_unload_time;
};


#endif //SBROWSER2_DOCUMENT_INTERNALS_HPP
