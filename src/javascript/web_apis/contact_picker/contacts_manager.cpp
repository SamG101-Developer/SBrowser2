#include "contacts_manager.hpp"

#include "javascript/environment/realms_2.hpp"

#include "contact_picker/detail/contact_internals.hpp"

#include "dom/detail/exception_internals.hpp"
#include "dom/detail/observer_internals.hpp"
#include "dom/other/dom_exception.hpp"

#include "html/detail/context_internals.hpp"
#include "html/detail/task_internals.hpp"

#include <range/v3/view/set_algorithm.hpp>


auto contact_picker::contacts_manager::get_properties()
        -> std::promise<ext::vector<detail::contact_property_t>>
{
    // Create a promise, and in parallel, set the value of it to the supported properties of the contact source
    // belonging to this ContactsManager object. Return the promise (value may have not been set when the promise is
    // returned)
    std::promise<ext::vector<detail::contact_property_t>> promise;
    std::jthread{ext::bind_front{&decltype(promise)::set_value, promise, m_contact_source->supported_properties}};
    return promise;
}


auto contact_picker::contacts_manager::select(
        ext::vector<detail::contact_property_t*>& properties,
        detail::contacts_select_options_t&& options)
        -> std::promise<ext::vector<detail::contact_info_t>>
{
    // Get the relevant browsing context from the relevant JavaScript realm. Create an empty promise for returning
    // either rejected or resolved.
    JS_REALM_GET_RELEVANT(this);
    decltype(auto) relevant_browsing_context = javascript::environment::realms_2::get<html::detail::browsing_context_t&>(this_relevant_global_object, "$BrowsingContext");
    std::promise<ext::vector<detail::contact_info_t>> promise;

    // If the relevant browsing context is not top level, then the ContactsManager is in an invalid state to select a
    // contact information (incorrect context).
    if (!html::detail::is_top_level_browsing_context(relevant_browsing_context))
    {
        promise.set_exception(dom::other::dom_exception{"Browsing context is not top level", INVALID_STATE_ERR});
        return promise;
    }

    if (/* TODO : SECURITY_ERR check here */)
    {
        promise.set_exception(dom::other::dom_exception{"TODO", SECURITY_ERR});
        return promise;
    }

    // If the contact picker is already showing in the relevant browsing context, then the ContactsManager is in an
    // invalid state, because this method is already running (close previous picker and open again)
    if (relevant_browsing_context.m_contact_picker_is_showing)
    {
        promise.set_exception(dom::other::dom_exception{"Browsing context can not have a contact picker showing", INVALID_STATE_ERR});
        return promise;
    }

    // If there are no properties, then there is nothing to choose from; this is a JavaScript TypeError, because the
    // properties is of an incorrect length.
    if (properties.empty())
    {
        promise.set_exception(); // TODO : JavaScript TypeError
        return promise;
    }

    // If any of the properties aren't supported, then this is a JavaScript TypeError (invalid properties are detected
    // by discovering any properties in the 'properties' list that aren't in the supported properties with a
    // 'set_difference' check.
    if (!ranges::views::set_difference(m_contact_source->supported_properties, properties).empty())
    {
        promise.set_exception(); // TODO : JavaScript TypeError
        return promise;
    }

    // Set the contacts picker showing flag to true for the relevant browsing context, as the picker is about to be
    // shown.
    relevant_browsing_context.m_contact_picker_is_showing = true;

    // In another thread (so GUI is non-blocking), begin the selection process to select a contact from the contacts
    // picker.
    go [&promise, &relevant_browsing_context, options = std::move(options), properties = std::move(properties)]
    {
        // Launch the contacts picker with the 'multiple' boolean option from the 'options', with the resulting selected
        // contact being 'selected_contacts' -- this is potentially thread blocking, because of the gUI, which is why
        // this part of the method is ran in another thread.
        JS_EXCEPTION_HANDLER;
        auto multiple = options.at("multiple").to<ext::boolean>();
        auto selected_contacts = detail::launch(std::move(multiple), std::move(properties));

        // Reject the promise if there was an issue with selecting a contact in the gUI, or if no contact was selected
        // TODO: is selecting no contact an error?
        if (JS_EXCEPTION_HAS_THROWN || !selected_contacts.has_value())
        {
            promise.set_exception(dom::other::dom_exception{"Error launching options and properties", INVALID_STATE_ERR});
            return;
        }

        // The contact picker is now no longer showing, so set the flag in the relevant browsing context to false. Queue
        // a task on the contact picker task source to create the list of contact information.
        relevant_browsing_context.m_contact_picker_is_showing = false;
        dom::detail::queue_task(
                html::detail::contact_picker_task_source()
                // TODO
                );
    };

    return promise;
}