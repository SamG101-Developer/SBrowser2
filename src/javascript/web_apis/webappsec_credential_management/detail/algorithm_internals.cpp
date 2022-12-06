#include "algorithm_internals.hpp"

#include "ext/enums.ixx"

#include "javascript/environment/settings.ixx"



#include "dom/detail/observer_internals.hpp"
#include "dom/nodes/document.hpp"
#include "dom/nodes/document_private.hpp"
#include "dom/nodes/window.hpp"
#include "dom/nodes/window_private.hpp"
#include "dom/other/dom_exception.hpp"

#include "html/detail/context_internals.hpp"
#include "html/detail/origin_internals.hpp"
#include "html/detail/task_internals.hpp"

#include "webappsec_credential_management/credential.hpp"
#include "webappsec_credential_management/credential_private.hpp"
#include "web_idl/detail/type_mapping_internals.hpp"

#include "range/v3/view/transform.hpp"
#include "range/v3/view/join.hpp"
#include "range/v3/algorithm/nth_element.hpp"
#include "range/v3/to_container.hpp"


auto webappsec::detail::same_origin_with_ancestors(
        js::env::env& e)
        -> ext::boolean
{
    decltype(auto) window = e.cpp.global<dom::nodes::window*>();
    return_if (!window->d_func()->document.get()) false;

    decltype(auto) origin = *e.cpp.settings()->origin;
    decltype(auto) current = window->d_func()->document->d_func()->browsing_context.get();

    while (current->parent_browsing_context)
    {
        current = current->parent_browsing_context;
        return_if (!html::detail::same_origin(window->d_func()->document->d_func()->origin, origin)) false;
    }

    return true;
}


auto webappsec::detail::relevant_credential_interface_objects(
        ext::map<ext::string, ext::any>&& options)
        -> ext::set<credential_management::credential*>
{
    auto e = js::env::env::current();
    auto relevant_interface_objects = ext::set<>();
    for (auto&& [option_key, option_value]: options)
    {}

    // TODO : types, so will be difficult
}


auto webappsec::detail::matchable_priori(
        detail::credential_request_options_t&& options)
        -> ext::boolean
{
    // TODO - needs to be looping through interfaces, and the access of the discovery_t will be changed
    return options[u"credential_store"].to<detail::discovery_t>() != detail::discovery_t::CREDENTIAL_STORE;
}


auto webappsec::detail::request_credential(
        detail::credential_request_options_t&& options)
        -> ext::promise<credential_management::credential*>
{
    auto e = js::env::env::current();
    ASSERT(e.cpp.settings()->is_secure_context);

    decltype(auto) abort_signal = options[u"signal"].to<dom::abort::abort_signal*>();
    if (abort_signal->d_func()->aborted())
        return web_idl::detail::create_rejected_promise<credential_management::credential*>(abort_signal->d_func()->abort_reason, e.js.realm());
    // TODO: mediation

    decltype(auto) origin = *e.cpp.settings()->origin;
    decltype(auto) is_same_origin_with_ancestors = same_origin_with_ancestors(e);
    decltype(auto) promise = ext::promise<credential_management::credential*>{};

    // TODO: publicKey (need to do spec first

    GO [is_same_origin_with_ancestors, &e, &origin, &promise, options = std::move(options)] mutable
    {
        JS_EXCEPTION_HANDLER;
        decltype(auto) credentials = collect_credentials(origin, std::move(options), is_same_origin_with_ancestors);
        decltype(auto) mediation = options[u"mediation"].to<detail::credential_mediation_requirement_t>();

        if (JS_EXCEPTION_HAS_THROWN)
            return web_idl::detail::reject_promise(promise, e.js.realm(), JS_EXCEPTION);

        if (credentials.size() == 1
                && !requires_use_mediation(origin)
                && matchable_priori(std::move(options))
                && !((credential_mediation_requirement_t::REQUIRED | credential_mediation_requirement_t::CONDITIONAL) & mediation))
            return web_idl::detail::resolve_promise(promise, e.js.realm(), &**credentials.begin()); // TODO : &** really

        if (mediation == credential_mediation_requirement_t::SILENT)
            return web_idl::detail::resolve_promise(promise, e.js.realm(), ext::nullptr_cast<credential_management::credential*>());

        decltype(auto) result = ask_user_to_choose_credentials(std::move(options), credentials);
        result = result ?: result->d_func()->discover_from_external_source(origin, std::move(options), is_same_origin_with_ancestors);
        if (result || mediation != credential_mediation_requirement_t::CONDITIONAL)
            return web_idl::detail::resolve_promise(promise, e.js.realm(), &*result); // TODO : &* really
    };

    return promise;
}


auto webappsec::detail::collect_credentials(
        const html::detail::origin_t& origin,
        detail::credential_request_options_t&& options,
        ext::boolean same_origin_with_ancestors)
        -> ext::set<credential_management::credential*>
{
    // TODO
    auto possible_matches = relevant_credential_interface_objects(std::move(options))
            | ranges::views::transform(ext::bind_front{&credential_management::credential::s_collect_from_credential_store, origin, std::move(options), same_origin_with_ancestors})
            | ranges::views::join
            | ranges::to<ext::set<credential_management::credential*>>;
}


auto webappsec::detail::store_credential(
        credential_management::credential* credential)
        -> ext::promise<credential_management::credential*>
{
    auto e = js::env::env::current();
    ASSERT(e.cpp.settings()->is_secure_context);

    auto is_same_origin_with_ancestors = same_origin_with_ancestors(e);
    auto promise = ext::promise<credential_management::credential*>{};

    GO [credential, is_same_origin_with_ancestors, &e, &promise]
    {
        JS_EXCEPTION_HANDLER;
        decltype(auto) result = credential->d_func()->store(credential, is_same_origin_with_ancestors);

        if (JS_EXCEPTION_HAS_THROWN)
            dom::detail::queue_task(html::detail::dom_manipulation_task_source,
                    BIND_FRONT(web_idl::detail::reject_promise, promise, e.js.realm(), JS_EXCEPTION));

        return web_idl::detail::resolve_promise(promise, e.js.realm(), &*result);
    };

    return promise;
}


auto webappsec::detail::create_credential(
        detail::credential_request_options_t&& options)
        -> ext::promise<credential_management::credential*>
{
    auto e = js::env::env::current();
    ASSERT(e.cpp.settings()->is_secure_context);

    // TODO
    // auto is_same_origin_with_ancestors = same_origin_with_ancestors(e);
    // if (!e.cpp.global<dom::nodes::window*>()->d_func()->document || )
    //     return web_idl::detail::create_rejected_promise<credential_management::credential*>(dom::other::dom_exception{NOT_SUPPORTED_ERROR, u""});
}


auto webappsec::detail::prevent_silent_access(
        js::env::env& e)
        -> ext::promise<void>
{
    decltype(auto) origin = *e.cpp.settings()->origin;
    auto promise = ext::promise<void>{};
    GO [&e, &promise]
    {
        // TOOD
        web_idl::detail::resolve_promise(promise, e.js.realm());
    };

    return promise;
}
