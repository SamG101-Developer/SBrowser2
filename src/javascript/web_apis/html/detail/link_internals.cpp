#include "link_internals.hpp"

#include "fetch/detail/request_internals.hpp"

#include "html/elements/html_link_element.hpp"

#include <range/v3/algorithm/contains.hpp>


auto html::detail::link_internals::default_fetch_and_process_linked_resource(
        elements::html_link_element* element)
        -> void
{
    auto options = create_link_options(element);
    auto request = create_link_request(std::move(options));
    // TODO : return if request failed (=nullptr?)
    // TODO : set request's synchonous flag -> doesn't exist?

    custom_fetch_and_process_linked_resource(element, request);
    auto initiator_type = ranges::contains(element->rel(), "stylesheet") ? "css" : "link";

    // TODO
}
