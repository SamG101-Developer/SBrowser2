#include "link_internals.hpp"

#include "ext/casting.hpp"

#include "content_security_policy/detail/csp_internals.hpp"

#include "dom/detail/node_internals.hpp"
#include "dom/detail/shadow_internals.hpp"
#include "dom/detail/observer_internals.hpp"
#include "dom/nodes/window.hpp"

#include "fetch/detail/request_internals.hpp"

#include "html/detail/context_internals.hpp"
#include "html/detail/html_element_internals.hpp"
#include "html/detail/miscellaneous_internals.hpp"
#include "html/detail/task_internals.hpp"
#include "html/elements/html_link_element.hpp"
#include "html/mixins/html_hyperlink_element_utils.hpp"

#include <magic_enum.hpp>
#include <range/v3/algorithm/contains.hpp>
#include <range/v3/view/map.hpp>


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


auto html::detail::link_internals::cannot_navigate(
        const elements::html_element* element)
        -> ext::boolean
{
    return dom::detail::node_internals::is_document_fully_active(element->owner_document())
            || element->local_name() != "a" && !dom::detail::shadow_internals::is_connected(element);
}


auto html::detail::link_internals::follow_hyperlink(
        const linkable_element auto* element,
        ext::string_view hyperlink_suffix)
        -> void
{
    return_if(cannot_navigate(element));

    auto* source = element->owner_document()->m_browsing_context.get();
    ext::string target_attribute_value{element->local_name() == "a" || element->local_name() == "area" ? html_element_internals::get_elements_target(element) : ""};
    ext::boolean replace;

    auto noopener = get_elements_noopener(element, target_attribute_value);
    auto* target = context_internals::choose_browsing_context(target_attribute_value, source, noopener).first;
    return_if(!target);

    auto url = detail::miscellaneous_internals::parse_url(ext::cross_cast<const mixins::html_hyperlink_element_utils*>(element)->href(), element->owner_document());
    if (url.first.empty())
    {
        // TODO : report to user
        dom::detail::observer_internals::queue_element_task(task_internals::dom_manipulation_task_source(), element, [target] {context_internals::navigate(target);});
        return;
    }

    url.second += hyperlink_suffix;

    fetch::detail::request_internals::internal_request request
    {
        .url = url.second,
        .referrer_policy = magic_enum::enum_cast<referrer_policy::referrer_policy_t>(element->referrer_policy())
    };

    // TODO : link types stuff
    dom::detail::observer_internals::queue_element_task(task_internals::dom_manipulation_task_source(), element, [target, source] {context_internals::navigate(target, source);});
}


auto html::detail::link_internals::consume_preloaded_resource(
        dom::nodes::window* window,
        url::url_object& url,
        fetch::detail::request_internals::destination_t destination,
        fetch::detail::request_internals::mode_t mode,
        fetch::detail::request_internals::credentials_t credentials,
        ext::string_view integrity_metadata,
        response_available_function_t&& on_response_available)
        -> ext::boolean
{
    auto key = preload_key
    {
        .url = url,
        .destination = destination,
        .mode = mode,
        .credentials_mode = credentials
    };

    auto& preloads = window->document->m_preloaded_resources;
    return_if(!ranges::contains(preloads | ranges::views::keys, key)) ext::boolean::FALSE();

    auto entry = preloads.at(&key); // TODO : wont work
    auto consumer_integrity_metadata = content_security_policy::detail::csp_internals::parse_metadata(integrity_metadata);
    auto preload_integrity_metadata = content_security_policy::detail::csp_internals::parse_metadata(entry->integrity_data);
    return_if(consumer_integrity_metadata.empty() || consumer_integrity_metadata == preload_integrity_metadata) ext::boolean::TRUE();

    if (!entry->response) entry->on_response_available = std::move(on_response_available);
    else on_response_available(entry->response);

    return ext::boolean::TRUE();
}
