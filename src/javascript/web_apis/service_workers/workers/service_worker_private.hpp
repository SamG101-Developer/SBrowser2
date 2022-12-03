#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_WORKERS_SERVICE_WORKER_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_WORKERS_SERVICE_WORKER_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "dom/nodes/event_target_private.hpp"
#include "html/mixins/abstract_worker_private.hpp"

#include INCLUDE_INNER_TYPES(html)
#include INCLUDE_INNER_TYPES(service_workers)
#include "ext/set.hpp"


DEFINE_PRIVATE_CLASS(service_workers::workers, service_worker)
        : dom::nodes::event_target_private
        , html::mixins::abstract_worker_private
{
    detail::service_worker_state_t state = detail::service_worker_state_t::PARSED;
    detail::service_worker_type_t type = detail::service_worker_type_t::CLASSIC;
    detail::script_resource_map_t script_resource_map;
    service_worker_registration_private* containing_worker_registration;

    std::unique_ptr<url::detail::url_t> script_url;
    html::detail::script_t script;
    html::detail::policy_container_t& policy_container;
    service_worker_global_scope* global_object;

    ext::boolean has_even_been_evaluated_flag;
    ext::boolean skip_waiting_flag;
    ext::boolean classic_scripts_imported_flag;

    ext::set<std::unique_ptr<url::detail::url_t>> used_scripts;
    ext::set<ext::string> events_types_to_handle;
    ext::set<events::extendable_event*> extended_events;

    ext::boolean start_status;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_WORKERS_SERVICE_WORKER_PRIVATE_HPP
