#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PRESENTATION_DETAIL_PRESENTATION_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PRESENTATION_DETAIL_PRESENTATION_INTERNALS_HPP

#include "ext/promise.hpp"
#include "ext/span.hpp"
#include "ext/string.hpp"

#include INCLUDE_INNER_TYPES(presentation)

namespace dom::nodes {class document;}
namespace presentation {class presentation;}
namespace presentation {class presentation_availability;}
namespace presentation {class presentation_connection;}
namespace presentation {class presentation_request;}


namespace presentation::detail
{
    auto in_controlling_browsing_context(
            presentation_connection* connection)
            -> ext::boolean;

    auto in_receiving_browsing_context(
            presentation_connection* connection)
            -> ext::boolean;

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
            detail::presentation_id_t presentation_id)
            -> ext::promise<presentation_connection>;

    auto get_presentation_displays_availability_information(
            presentation_request* request)
            -> ext::promise<presentation_availability>;

    auto monitor_list_of_available_presentation_displays()
            -> void;

    auto establish_presentation_connection(
            presentation_connection* connection)
            -> void;

    auto send_message(
            presentation_connection* connection,
            presentation_message_data_t&& data)
            -> void;

    auto receive_message(
            presentation_connection* connection,
            presentation_message_t message_type,
            presentation_message_data_t&& message_data)
            -> void;

    auto start_closing_presentation_connection(
            presentation_connection* connection,
            presentation_connection_close_reason close_reason,
            presentation_close_message_t&& close_message)
            -> void;

    auto close_presentation_connection(
            presentation_connection* connection,
            presentation_connection_close_reason close_reason,
            presentation_close_message_t&& close_message)
            -> void;

    auto terminate_presentation_in_controlling_browsing_context(
            presentation_connection* connection)
            -> void;

    auto terminate_presentation_in_receiving_browsing_context(
            presentation_connection* connection)
            -> void;

    auto send_termination_confirmation(
            presentation* presentation)
            -> void;
}


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PRESENTATION_DETAIL_PRESENTATION_INTERNALS_HPP
