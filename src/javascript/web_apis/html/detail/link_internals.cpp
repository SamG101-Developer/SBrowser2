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


auto html::detail::default_fetch_and_process_linked_resource(
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


auto html::detail::cannot_navigate(
        const elements::html_element* element)
        -> ext::boolean
{
    return dom::detail::is_document_fully_active(element->owner_document())
            || element->local_name() != "a" && !dom::detail::is_connected(element);
}


auto html::detail::follow_hyperlink(
        const linkable_element auto* element,
        ext::string_view hyperlink_suffix)
        -> void
{
    return_if(cannot_navigate(element));

    auto* source = element->owner_document()->m_browsing_context.get();
    ext::string target_attribute_value{element->local_name() == "a" || element->local_name() == "area" ? html_element_internals::get_elements_target(element) : ""};
    ext::boolean replace;

    auto noopener = get_elements_noopener(element, target_attribute_value);
    auto* target = choose_browsing_context(target_attribute_value, source, noopener).first;
    return_if(!target);

    auto url = detail::miscellaneous_internals::parse_url(ext::cross_cast<const mixins::html_hyperlink_element_utils*>(element)->href(), element->owner_document());
    if (url.first.empty())
    {
        // TODO : report to user
        dom::detail::queue_element_task(task_internals::dom_manipulation_task_source(), element, [target] {navigate(target);});
        return;
    }

    url.second += hyperlink_suffix;

    fetch::detail::request_t request
    {
        .url = url.second,
        .referrer_policy = magic_enum::enum_cast<referrer_policy::referrer_policy_t>(element->referrer_policy())
    };

    // TODO : link types stuff
    dom::detail::queue_element_task(task_internals::dom_manipulation_task_source(), element, [target, source] {navigate(target, source);});
}


auto html::detail::consume_preloaded_resource(
        dom::nodes::window* window,
        url::detail::url_t& url,
        fetch::detail::destination_t destination,
        fetch::detail::mode_t mode,
        fetch::detail::credentials_t credentials,
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
    return_if(!ranges::contains(preloads | ranges::views::keys, key)) false;

    auto entry = preloads.at(&key); // TODO : wont work
    auto consumer_integrity_metadata = content_security_policy::detail::parse_metadata(integrity_metadata);
    auto preload_integrity_metadata = content_security_policy::detail::parse_metadata(entry->integrity_data);
    return_if(consumer_integrity_metadata.empty() || consumer_integrity_metadata == preload_integrity_metadata) true;

    if (!entry->response) entry->on_response_available = std::move(on_response_available);
    else on_response_available(entry->response);

    return true;
}
