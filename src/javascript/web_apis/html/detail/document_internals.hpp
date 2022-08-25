#ifndef SBROWSER2_DOCUMENT_INTERNALS_HPP
#define SBROWSER2_DOCUMENT_INTERNALS_HPP

#include "ext/boolean.hpp"
#include USE_INNER_TYPES(html)
#include USE_INNER_TYPES(high_resolution_time)

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
}


struct html::detail::document_load_timing_info
{
    ext::number<int> navigation_start_time;
    high_resolution_time::detail::dom_high_res_time_stamp_t dom_interactive_time;
    high_resolution_time::detail::dom_high_res_time_stamp_t dom_content_loaded_event_start_time;
    high_resolution_time::detail::dom_high_res_time_stamp_t dom_content_loaded_event_end_time;
    high_resolution_time::detail::dom_high_res_time_stamp_t dom_complete_time;
    high_resolution_time::detail::dom_high_res_time_stamp_t load_event_start_time;
    high_resolution_time::detail::dom_high_res_time_stamp_t load_event_unload_time;
};


struct html::detail::document_unload_timing_info
{
    high_resolution_time::detail::dom_high_res_time_stamp_t unload_event_start_time;
    high_resolution_time::detail::dom_high_res_time_stamp_t unload_event_unload_time;
};


#endif //SBROWSER2_DOCUMENT_INTERNALS_HPP
