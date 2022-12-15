module;
#include <function2/function2.hpp>


export module apis.background_tasks.types;

import apis.hr_time.types;
import ext.functional;

namespace background_tasks {class idle_deadline;}


namespace background_tasks::detail
{
    using idle_request_callback_t = ext::function<void(idle_deadline*)>;
    using deadline_time_algorithm_t = ext::function<hr_time::dom_high_res_time_stamp()>;
}
