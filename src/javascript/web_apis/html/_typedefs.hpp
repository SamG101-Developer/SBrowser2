#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML__TYPEDEFS_HPP

#include "ext/pair.hpp"
#include "ext/vector.hpp"
namespace html::elements {class html_element;}

namespace html::detail
{
    enum class history_handling_behaviour_t {DEFAULT, /* TODO */};
    enum class directionality_t {LTR, RTL, AUTO};
    enum class bidirectional_char_t: char32_t {L = 0x200e, R = 0x200f, AL = 0x061c, EN, ES, ET, AN, CS, NSM, BN, B, S, WS, ON, LRE, LRO, RLE, PDF, LRI, RLI, FSI, PDI};
    enum class state_t {UNAVAILABLE, PARTIALLY_AVAILABLE, COMPLETELY_AVAILABLE, BROKEN};
    struct browsing_context;
    struct document_load_timing_info;
    struct document_unload_timing_info;
    struct image_request;
    struct available_image;
    struct image_source;
    using name_value_group_t = ext::pair<ext::vector<elements::html_element*>, ext::vector<elements::html_element*>>;
    using name_value_groups_t = ext::vector<name_value_group_t>;
}

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML__TYPEDEFS_HPP
