#include "algorithm_internals.hpp"

#include "ext/enums.hpp"
#include "javascript/environment/realms_2.hpp"
#include "javascript/environment/environment_settings.hpp"

#include "dom/abort/abort_signal.hpp"
#include "dom/detail/observer_internals.hpp"
#include "dom/nodes/document.hpp"
#include "dom/nodes/window.hpp"

#include "html/detail/context_internals.hpp"
#include "html/detail/origin_internals.hpp"
#include "html/detail/task_internals.hpp"

#include "webappsec_credential_management/credential.hpp"

#include "range/v3/view/transform.hpp"
#include "range/v3/view/join.hpp"
#include "range/v3/to_container.hpp"


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


auto webappsec::detail::request_credential(
        credential_management::credential* credential,
        detail::credential_request_options_t&& options)
        -> ext::promise<credential_management::credential*>
{
    JS_REALM_GET_CURRENT;
    // TODO : assert settings is in a secure context
    auto promise = ext::promise<credential_management::credential*>{};

    decltype(auto) abort_signal = options.try_emplace("signal", nullptr).first->second.to<dom::abort::abort_signal*>();
    return_if (abort_signal->aborted()) promise.reject(abort_signal->reason());
    // TODO: mediation

    decltype(auto) settings_object = v8pp::from_v8<javascript::environment::settings_t*>(current_agent, current_settings_object);
    decltype(auto) origin = settings_object->origin;
    decltype(auto) is_same_origin_with_ancestors = same_origin_with_ancestors(settings_object);

    // TODO: publicKey (need to do spec first

    go [is_same_origin_with_ancestors, &origin, &promise, &options] mutable
    {
        JS_EXCEPTION_HANDLER;
        decltype(auto) credentials = collect_credentials(origin, std::move(options), is_same_origin_with_ancestors);
        decltype(auto) mediation = options.try_emplace("mediation").first->second.to<detail::credential_mediation_requirement_t>();

        if (JS_EXCEPTION_HAS_THROWN)
            return promise.reject(JS_EXCEPTION);

        if (credentials.size() == 1
                && !requires_use_mediation(origin)
                && matchable_priori(std::move(options))
                && !((credential_mediation_requirement_t::REQUIRED | credential_mediation_requirement_t::CONDITIONAL) & mediation))
            return promise.resolve(credentials[0]);

        if (mediation == credential_mediation_requirement_t::SILENT)
            return promise.resolve(nullptr);

        decltype(auto) result = ask_user_to_choose_credentials(std::move(options), credentials);
        result = result ?: result->s_discover_from_external_source(origin, std::move(options), is_same_origin_with_ancestors);
        if (result || mediation != credential_mediation_requirement_t::CONDITIONAL)
            promise.resolve(result);
    };

    return promise;
}


auto webappsec::detail::collect_credentials(
        const html::detail::origin_t& origin,
        detail::credential_request_options_t&& options,
        ext::boolean same_origin_with_ancestors)
        -> ext::set<credential_management::credential*>
{
    auto possible_matches = relevant_credential_interface_objects(std::move(options))
            | ranges::views::transform(ext::bind_front{&credential_management::credential::s_collect_from_credential_store, origin, std::move(options), same_origin_with_ancestors})
            | ranges::views::join
            | ranges::to<ext::set<credential_management::credential*>>;
}


auto webappsec::detail::store_credential(
        credential_management::credential* credential)
        -> ext::promise<credential_management::credential*>
{
    JS_REALM_GET_CURRENT;
    // TODO : assert settings is in a secure context
    auto is_same_origin_with_ancestors = same_origin_with_ancestors(current_settings_object);
    auto promise = ext::promise<credential_management::credential*>{};

    go [credential, is_same_origin_with_ancestors, &promise]
    {
        JS_EXCEPTION_HANDLER;
        decltype(auto) result = credential->s_store(credential, is_same_origin_with_ancestors);

        if (JS_EXCEPTION_HAS_THROWN)
            dom::detail::queue_task(html::detail::dom_manipulation_task_source,
                    [&promise, exception = JS_EXCEPTION]
                    {promise.reject(exception);});

        promise.resolve(result);
    };

    return promise;
}
