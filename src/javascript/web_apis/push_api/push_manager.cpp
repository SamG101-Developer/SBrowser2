#include "push_manager.hpp"
#include "push_manager_private.hpp"

#include "ext/boolean.hpp"
#include "ext/encoding.hpp"

#include INCLUDE_INNER_TYPES(dom)
#include INCLUDE_INNER_TYPES(permissions)
#include INCLUDE_INNER_TYPES(push_api)

#include "dom/detail/observer_internals.hpp"
#include "dom/other/dom_exception.hpp"

#include "html/detail/task_internals.hpp"
#include "permissions/detail/permission_internals.hpp"

#include "service_workers/workers/service_worker_registration.hpp"
#include "service_workers/workers/service_worker_registration_private.hpp"
#include "service_workers/workers/service_worker.hpp"
#include "service_workers/workers/service_worker_private.hpp"

#include <v8-array-buffer.h>


auto push_api::push_manager::subscribe(
        detail::push_subscription_options_init_t&& options)
        -> ext::promise<push_subscription*>
{
    ACCESS_PIMPL(push_manager);
    JS_REALM_GET_RELEVANT(this);
    auto promise = ext::promise<push_subscription*>{};
    using enum dom::detail::dom_exception_error_t;

    GO [d, this_relevant_global_object, &promise, options = std::move(options)] mutable
    {
        if (!options[u8"userVisibleOnly"].to<ext::boolean>() /* TODO : && ? */)
            dom::detail::queue_global_task(
                    html::detail::networking_task_source,
                    this_relevant_global_object,
                    [&promise] {promise.reject(dom::other::dom_exception{u8"TODO", NOT_ALLOWED_ERR});});

        if (!options.contains(u8"applicationServerKey") /* TODO : && ? */)
            dom::detail::queue_global_task(
                    html::detail::networking_task_source,
                    this_relevant_global_object,
                    [&promise] {promise.reject(dom::other::dom_exception{u8"TODO", NOT_SUPPORTED_ERR});});

        if (
                auto application_server_key = options[u8"applicationServerKey"].to<detail::application_server_key_t>();
                !ext::holds_alternative<ext::variant_monostate_t>(application_server_key))
        {
            auto parsed_application_server_key = ext::holds_alternative<ext::string>(application_server_key)
                    ? v8::ArrayBuffer::New(this_relevant_global_object->GetIsolate(), ext::get<ext::string>(application_server_key).size())
                    : ext::get<v8::Local<v8::ArrayBuffer>>(application_server_key);

            // TODO
        }

        if (!d->registration)
            dom::detail::queue_global_task(
                    html::detail::networking_task_source,
                    this_relevant_global_object,
                    [&promise] {promise.reject(dom::other::dom_exception{u8"Registration must not be null", INVALID_STATE_ERR});});

        if (
                auto permission = permissions::detail::request_permission_to_use(detail::push_permission_descriptor{{u8"name", u8"push"}});
                permission == permissions::detail::permission_state_t::DENIED)
            dom::detail::queue_global_task(
                    html::detail::networking_task_source,
                    this_relevant_global_object,
                    [&promise] {promise.reject(dom::other::dom_exception{u8"Permission to use 'Push' feature denied", NOT_ALLOWED_ERR});});

        if (/* TODO */ false)
        {}

        // TODO

    };

    return promise;
}
