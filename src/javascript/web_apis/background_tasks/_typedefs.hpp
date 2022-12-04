#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BACKGROUND_TASKS__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BACKGROUND_TASKS__TYPEDEFS_HPP





#include INCLUDE_INNER_TYPES(hr_time)
namespace background_tasks {class idle_deadline;}


namespace background_tasks::detail
{
    using idle_request_options_t = ext::map<ext::string, ext::any>;
    using idle_request_callback_t = ext::function<void(idle_deadline&&)>;
    using deadline_time_algorithm_t = ext::function<hr_time::dom_high_res_time_stamp()>;
}


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BACKGROUND_TASKS__TYPEDEFS_HPP
