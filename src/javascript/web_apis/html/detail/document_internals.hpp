#ifndef SBROWSER2_DOCUMENT_INTERNALS_HPP
#define SBROWSER2_DOCUMENT_INTERNALS_HPP

#include "ext/boolean.hpp"
#include "high_resolution_time/_typedefs.hpp"
namespace dom::nodes {class document;}

namespace html::detail::document_internals
{
    struct document_load_timing_info;
    struct document_unload_timing_info;
    
    auto is_cookie_averse_document(
            const dom::nodes::document* document)
            -> ext::boolean;
}


struct html::detail::document_internals::document_load_timing_info
{
    ext::number<int> navigation_start_time;
    high_resolution_time::dom_high_res_time_stamp dom_interactive_time;
    high_resolution_time::dom_high_res_time_stamp dom_content_loaded_event_start_time;
    high_resolution_time::dom_high_res_time_stamp dom_content_loaded_event_end_time;
    high_resolution_time::dom_high_res_time_stamp dom_complete_time;
    high_resolution_time::dom_high_res_time_stamp load_event_start_time;
    high_resolution_time::dom_high_res_time_stamp load_event_unload_time;
};


struct html::detail::document_internals::document_unload_timing_info
{
    high_resolution_time::dom_high_res_time_stamp unload_event_start_time;
    high_resolution_time::dom_high_res_time_stamp unload_event_unload_time;
};


#endif //SBROWSER2_DOCUMENT_INTERNALS_HPP
