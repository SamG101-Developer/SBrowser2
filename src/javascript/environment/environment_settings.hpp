#ifndef SBROWSER2_SRC_JAVASCRIPT_ENVIRONMENT_ENVIRONMENT_SETTINGS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_ENVIRONMENT_ENVIRONMENT_SETTINGS_HPP

namespace js::env {struct settings_t;}

#include INCLUDE_INNER_TYPES(hr_time)
#include INCLUDE_INNER_TYPES(html)
#include INCLUDE_INNER_TYPES(url)
#include <v8pp/class.hpp>
#include <v8pp/convert.hpp>
namespace service_workers::workers {class service_worker_private;}
namespace service_workers::workers {class service_worker;}


struct js::env::settings_t
{
    /* [HTML] */
    // TODO : Realm, API-URL-Character-Encoding

    dom::detail::module_map_t module_map;
    std::unique_ptr<url::detail::url_t> api_base_url;
    html::detail::origin_t origin;
    ext::boolean cross_origin_isolated_capability;
    hr_time::dom_high_res_time_stamp time_origin;
    std::shared_ptr<html::detail::policy_container_t> policy_container;

    ext::boolean is_secure_context;

    /* [SERVICE-WORKERS] */
    ext::map<service_workers::workers::service_worker_private*, service_workers::workers::service_worker*> service_worker_object_map;

    static auto to_v8(v8::Isolate* isolate)
    {return v8pp::class_<settings_t>{isolate};}
};


#endif //SBROWSER2_SRC_JAVASCRIPT_ENVIRONMENT_ENVIRONMENT_SETTINGS_HPP
