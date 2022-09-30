#include "service_worker_container.hpp"

#include "javascript/environment/environment_settings.hpp"

#include INCLUDE_INNER_TYPES(service_workers)

#include "service_workers/clients/client.hpp"
#include "service_workers/detail/job_internals.hpp"

#include "dom/detail/observer_internals.hpp"
#include "html/detail/task_internals.hpp"
#include "storage/detail/storage_internals.hpp"
#include "url/detail/url_internals.hpp"


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
    decltype(auto) parsed_scope_url  = scope_url.empty() ? "" : url::detail::url_parser(scope_url, api_base_url);

    detail::start_register(parsed_scope_url, parsed_script_url, promise, client, "TODO", options["type"].to<ext::string>(), options["updateViaCache"].to<detail::update_via_cache_mode_t>());
    return promise;
}


auto service_workers::workers::service_worker_container::get_ready() const -> ext::promise<service_worker_registration*>
{
    ACCESS_PIMPL(const service_worker_container);

    if (d->ready_promise.is_pending) go [this, d]
    {
        JS_REALM_GET_RELEVANT(this);

        decltype(auto) client = d->service_worker_client;
        decltype(auto) storage_key = storage::detail::obtain_storage_key(v8pp::to_v8(this_relevant_agent, client));
        decltype(auto) registration = detail::match_service_worker_registration(storage_key /* TODO */);

        if (registration && registration->d_func()->active_worker)
            dom::detail::queue_task(html::detail::dom_manipulation_task_source, [] {/* TODO */}, this_relevant_agent);
    };

    return d->ready_promise;
}