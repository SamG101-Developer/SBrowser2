#include "algorithm_internals.hpp"

#include "javascript/environment/realms_2.hpp"
#include "javascript/environment/environment_settings.hpp"

#include "dom/nodes/document.hpp"
#include "dom/nodes/window.hpp"

#include "html/detail/context_internals.hpp"
#include "html/detail/origin_internals.hpp"
#include "webappsec_credential_management/_typedefs.hpp"


auto webappsec::detail::same_origin_with_ancestors(
        v8::Local<v8::Object> settings)
        -> ext::boolean
{
    JS_REALM_GET_RELEVANT(settings);
    decltype(auto) window = v8pp::from_v8<dom::nodes::window*>(settings_relevant_agent, settings_relevant_global_object);
    return_if (!window->document()) false;

    decltype(auto) settings_object = v8pp::from_v8<javascript::environment::settings_t*>(settings_relevant_agent, settings);
    decltype(auto) origin = settings_object->origin;
    decltype(auto) current = window->document()->m_browsing_context.get();

    while (current->parent_browsing_context)
    {
        current = current->parent_browsing_context;
        return_if (!html::detail::same_origin(window->document()->m_orign, origin)) false;
    }

    return true;
}


auto webappsec::detail::matchable_priori(
        detail::credential_request_options_t&& options)
        -> ext::boolean
{
    // TODO
    return options.try_emplace("credential_store").first->second.to<detail::discovery_t>() != detail::discovery_t::CREDENTIAL_STORE;
}
