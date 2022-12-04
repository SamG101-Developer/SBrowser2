#include "contacts_manager.hpp"
#include "contacts_manager_private.hpp"



#include "javascript/environment/realms.hpp"

#include "contact_picker/detail/contact_internals.hpp"

#include "dom/_typedefs.hpp"
#include "dom/detail/exception_internals.hpp"
#include "dom/detail/observer_internals.hpp"
#include "dom/other/dom_exception.hpp"
#include "dom/nodes/document.hpp"
#include "dom/nodes/document_private.hpp"
#include "dom/nodes/window.hpp"
#include "dom/nodes/window_private.hpp"

#include "html/detail/context_internals.hpp"
#include "html/detail/task_internals.hpp"

#include "v8-exception.h"
#include "web_idl/detail/type_mapping_internals.hpp"

#include <range/v3/view/set_algorithm.hpp>


contact_picker::contacts_manager::contacts_manager()
{
    INIT_PIMPL(contacts_manager);
}


auto contact_picker::contacts_manager::get_properties() -> ext::promise<ext::vector<detail::contact_property_t>>
{
    ACCESS_PIMPL(contacts_manager);

    // Create a promise, and in parallel, set the value of it to the supported properties of the contact source
    // belonging to this ContactsManager object. Return the promise (value may have not been set when the promise is
    // returned)
    ext::promise<ext::vector<detail::contact_property_t>> promise;
    GO [properties = d->supported_properties, e = js::env::env::relevant(this), &promise] mutable
    {web_idl::detail::resolve_promise(promise, e.js.realm(), std::move(properties));};

    return promise;
}


auto contact_picker::contacts_manager::select(
        ext::vector<detail::contact_property_t*>& properties,
        detail::contacts_select_options_t&& options)
        -> ext::promise<ext::vector<detail::contact_info_t>>
{
    ACCESS_PIMPL(contacts_manager);
    using enum dom::detail::dom_exception_error_t;

    // Get the relevant browsing context from the relevant JavaScript realm. Create an empty promise for returning
    // either rejected or resolved.
    auto e = js::env::env::relevant(this);
    decltype(auto) relevant_browsing_context = *e.cpp.global<dom::nodes::window*>()->d_func()->document->d_func()->browsing_context;
    auto promise = ext::promise<ext::vector<detail::contact_info_t>>{};

    // If the relevant browsing context is not top level, then the ContactsManager is in an invalid state to select a
    // contact information (incorrect context).
    if (!html::detail::is_top_level_browsing_context(relevant_browsing_context))
        return web_idl::detail::reject_promise(
                promise, e.js.realm(),
                dom::other::dom_exception{u8"Browsing context is not top level", INVALID_STATE_ERR});

    if (/* TODO : SECURITY_ERR check here */)
        return web_idl::detail::reject_promise(
                promise, e.js.realm(),
                dom::other::dom_exception{u8"TODO", SECURITY_ERR});

    // If the contact picker is already showing in the relevant browsing context, then the ContactsManager is in an
    // invalid state, because this method is already running (close previous picker and open again)
    if (relevant_browsing_context.m_contact_picker_is_showing)
        return web_idl::detail::reject_promise(
                promise, e.js.realm(),
                dom::other::dom_exception{u8"Browsing context can not have a contact picker showing", INVALID_STATE_ERR});

    // If there are no properties, then there is nothing to choose from; this is a JavaScript TypeError, because the
    // properties is of an incorrect length.
    if (properties.empty())
        return web_idl::detail::reject_promise(
                promise, e.js.realm(),
                v8::Exception::TypeError());

    // If any of the properties aren't supported, then this is a JavaScript TypeError (invalid properties are detected
    // by discovering any properties in the 'properties' list that aren't in the supported properties with a
    // 'set_difference' check.
    if (!ranges::views::set_difference(d->supported_properties, properties).empty())
        return web_idl::detail::reject_promise(
                promise, e.js.realm(),
                v8::Exception::TypeError());

    // Set the contacts picker showing flag to true for the relevant browsing context, as the picker is about to be
    // shown.
    relevant_browsing_context.m_contact_picker_is_showing = true;

    // In another thread (so GUI is non-blocking), begin the selection process to select a contact from the contacts
    // picker.
    GO [options, &e, &promise, &relevant_browsing_context, &properties]
    {
        // Launch the contacts picker with the 'multiple' boolean option from the 'options', with the resulting selected
        // contact being 'selected_contacts' -- this is potentially thread blocking, because of the gUI, which is why
        // this part of the method is ran in another thread.
        JS_EXCEPTION_HANDLER;
        decltype(auto) multiple = options.at(u"multiple").to<ext::boolean>();
        decltype(auto) selected_contacts = detail::launch(multiple, properties);

        // Reject the promise if there was an issue with selecting a contact in the gUI, or if no contact was selected
        // TODO: is selecting no contact an error?
        if (JS_EXCEPTION_HAS_THROWN || !selected_contacts.has_value())
        {
            web_idl::detail::reject_promise(promise, e.js.realm(), dom::other::dom_exception{u8"Error launching options and properties", INVALID_STATE_ERR});
            return;
        }

        // The contact picker is now no longer showing, so set the flag in the relevant browsing context to false. Queue
        // a task on the contact picker task source to create the list of contact information.
        relevant_browsing_context.m_contact_picker_is_showing = false;
        dom::detail::queue_task(
                html::detail::contact_picker_task_source
                // TODO
                );
    };

    return promise;
}


auto contact_picker::contacts_manager::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<self_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<dom_object>()
        .function("getProperties", &contacts_manager::get_properties)
        .function("select", &contacts_manager::select)
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}
