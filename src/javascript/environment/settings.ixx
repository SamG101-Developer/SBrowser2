module;
#include <v8pp/class.hpp>
#include <v8pp/convert.hpp>


export module js.env.settings;
namespace js::env {export struct settings_t;}

namespace service_workers::workers {class service_worker_private;}
namespace service_workers::workers {class service_worker;}
namespace web_locks {class lock_manager;}

struct js::env::settings_t
{
    /* [HTML] */
    // TODO : Realm, API-URL-Character-Encoding

    dom::detail::module_map_t module_map;
    std::unique_ptr<url::detail::url_t> api_base_url;
    std::unique_ptr<html::detail::origin_t> origin;
    ext::boolean cross_origin_isolated_capability;
    hr_time::dom_high_res_time_stamp time_origin;
    std::shared_ptr<html::detail::policy_container_t> policy_container;

    ext::boolean is_secure_context;

    // Environment
    ext::string id;
    std::unique_ptr<url::detail::url_t> creation_url;
    std::unique_ptr<url::detail::url_t> top_level_creation_url;
    std::unique_ptr<html::detail::origin_t> top_level_origin;
    std::observer_ptr<html::detail::browsing_context_t> target_browsing_context;
    std::unique_ptr<service_workers::workers::service_worker> active_service_worker;
    ext::boolean execution_ready_flag;

    // ?
    ext::vector<html::detail::browsing_context_t*> browsing_contexts;

    /* [FETCH] */
    std::unique_ptr<fetch::detail::fetch_group_t> fetch_group;

    /* [STORAGE] */
    std::unique_ptr<storage::detail::storage_shed_t> local_storage;
    std::unique_ptr<storage::detail::storage_shed_t> session_storage;

    /* [SERVICE-WORKERS] */
    ext::map<service_workers::workers::service_worker_private*, service_workers::workers::service_worker*> service_worker_object_map;

    /* [WEB-LOCKS] */
    std::unique_ptr<web_locks::lock_manager> lock_manager;

    static auto to_v8(v8::Isolate* isolate)
    {return v8pp::class_<settings_t>{isolate};}
};
