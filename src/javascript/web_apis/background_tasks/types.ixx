module;
#include "ext/macros/pimpl.hpp"
#include <function2/function2.hpp>


export module apis.background_tasks.types;
import apis.hr_time.types;
import ext.functional;


DEFINE_FWD_DECL_NAMESPACE(background_tasks)
{
    class idle_deadline;
}


DEFINE_FWD_DECL_NAMESPACE_DETAIL(background_tasks)
{
    using idle_request_callback_t = ext::function<void(idle_deadline*)>;
    using deadline_time_algorithm_t = ext::function<hr_time::dom_high_res_time_stamp()>;
}
