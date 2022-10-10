#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PRESENTATION_DETAIL_PRESENTATION_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PRESENTATION_DETAIL_PRESENTATION_INTERNALS_HPP

#include "ext/promise.hpp"
#include "ext/span.hpp"
#include "ext/string.hpp"

#include INCLUDE_INNER_TYPES(presentation)

namespace dom::nodes {class document;}
namespace presentation {class presentation_availability;}
namespace presentation {class presentation_connection;}
namespace presentation {class presentation_request;}


namespace presentation::detail
{
    auto construct_presentation_request(
            presentation_request* request,
            ext::vector_span<ext::string> urls)
            -> presentation_request*;

    auto select_presentation_display(
            presentation_request* request)
            -> ext::promise<presentation_connection>;

    auto start_presentation_from_default_presentation_request(
            dom::nodes::document* document,
            detail::presentation_display_t& presentation_display)
            -> void;

    auto start_presentation_connection(
            presentation_request* request,
            detail::presentation_display_t& presentation_display,
            ext::promise<presentation_connection>& promise)
            -> void;

    auto reconnect_to_presentation(
            presentation_request* request,
            detail::presentation_id presentation_id)
            -> ext::promise<presentation_connection>;

    auto get_presentation_displays_availability_information(
            presentation_request* request)
            -> ext::promise<presentation_availability>;

    auto monitor_list_of_available_presentation_displays()
            -> void;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PRESENTATION_DETAIL_PRESENTATION_INTERNALS_HPP
