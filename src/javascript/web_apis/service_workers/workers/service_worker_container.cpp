#include "service_worker_container.hpp"

#include "javascript/environment/environment_settings.hpp"

#include INCLUDE_INNER_TYPES(dom)
#include INCLUDE_INNER_TYPES(service_workers)

#include "service_workers/clients/client.hpp"
#include "service_workers/detail/job_internals.hpp"

#include "dom/detail/observer_internals.hpp"
#include "html/detail/task_internals.hpp"
#include "storage/detail/storage_internals.hpp"
#include "url/detail/url_internals.hpp"

#include <v8-exception.h>


auto service_workers::workers::service_worker_container::register_(
        ext::string_view script_url,
        detail::registration_options_t&& options)
        -> ext::promise<service_worker_registration>
{
    ACCESS_PIMPL(service_worker_container);

    JS_REALM_GET_RELEVANT(this);
    decltype(auto) settings_object = v8pp::from_v8<javascript::environment::settings_t*>(this_relevant_agent, this_relevant_settings_object);
    decltype(auto) api_base_url    = url::detail::url_serializer(*settings_object->api_base_url);
    decltype(auto) scope_url       = options.try_emplace("scope", "").first->second.to<ext::string>();

    auto promise = ext::promise<service_worker_registration>{};
    decltype(auto) client = d->service_worker_client;
    decltype(auto) parsed_script_url = url::detail::url_parser(script_url, api_base_url);
    decltype(auto) parsed_scope_url  = scope_url.empty() ? ""_url : url::detail::url_parser(scope_url, api_base_url);

    detail::start_register(std::move(parsed_scope_url), std::move(parsed_script_url), promise, client, "TODO", options["type"].to<ext::string>(), options["updateViaCache"].to<detail::update_via_cache_mode_t>());
    return promise;
}


auto service_workers::workers::service_worker_container::get_registration(
        ext::string_view client_url)
        -> ext::promise<service_worker_registration*>
{
    ACCESS_PIMPL(service_worker_container);
    using enum dom::detail::dom_exception_error_t;

    JS_REALM_GET_RELEVANT(this);
    decltype(auto) settings_object = v8pp::from_v8<javascript::environment::settings_t*>(this_relevant_agent, this_relevant_settings_object);
    decltype(auto) api_base_url    = url::detail::url_serializer(*settings_object->api_base_url);
    auto promise = ext::promise<service_worker_registration*>{};

    decltype(auto) client = d->service_worker_client;
    auto storage_key = storage::detail::obtain_storage_key(v8pp::to_v8(this_relevant_agent, client));
    auto parsed_client_url = url::detail::url_parser(client_url, api_base_url);

    return_if (!parsed_client_url.has_value()) promise.reject(v8::Exception::TypeError(v8pp::to_v8(this_relevant_agent, "TODO")));
    return_if (url::detail::origin(*parsed_client_url) != html::detail::origin(v8pp::to_v8(this_relevant_agent, client))) promise.reject(dom::other::dom_exception{"TODO", SECURITY_ERR});

    GO [&promise, storage_key = std::move(storage_key), parsed_client_url = std::move(*parsed_client_url)] mutable
    {
        decltype(auto) registration = detail::match_service_worker_registration(std::move(storage_key), std::move(parsed_client_url));
        promise.resolve(!registration ? nullptr : detail::get_the_service_worker_registration(this_relevant_settings_object, registration));
    };

    return promise;
}


auto service_workers::workers::service_worker_container::get_registrations()
        -> ext::promise<const ext::vector<service_worker_registration>>
{
    ACCESS_PIMPL(service_worker_container);

    JS_REALM_GET_RELEVANT(this);
    decltype(auto) client = d->service_worker_client;
    auto client_storage_key = storage::detail::obtain_storage_key(v8pp::to_v8(this_relevant_agent, client));
    auto promise = ext::promise<const ext::vector<service_worker_registration>>{};

    GO [&promise, storage_key = std::move(client_storage_key)]
    {
        // TODO
    };

    return promise;
}


auto service_workers::workers::service_worker_container::start_messages()
        -> void
{
    ACCESS_PIMPL(service_worker_container);
    d->client_message_queue.enabled = true;
}


auto service_workers::workers::service_worker_container::get_ready() const -> ext::promise<service_worker_registration*>
{
    ACCESS_PIMPL(const service_worker_container);

    if (d->ready_promise.is_pending) GO [this, d]
    {
        JS_REALM_GET_RELEVANT(this);

        decltype(auto) client = d->service_worker_client;
        auto storage_key = storage::detail::obtain_storage_key(v8pp::to_v8(this_relevant_agent, client));
        decltype(auto) registration = detail::match_service_worker_registration(storage_key /* TODO */);

        if (registration && registration->d_func()->active_worker)
            dom::detail::queue_task(html::detail::dom_manipulation_task_source, [] {/* TODO */}, this_relevant_agent);
    };

    return d->ready_promise;
}