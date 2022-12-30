module;
#include "ext/macros.hpp"


export module apis.background_tasks.idle_deadline:p;
import apis.dom_object;

import apis.hr_time.types;
import ext.core;


DEFINE_PRIVATE_CLASS(background_tasks, idle_deadline)
        : virtual dom_object_private
{
public:
    MAKE_QIMPL(idle_deadline);

public:
    auto get_deadline_time() -> hr_time::dom_high_res_time_stamp;

public:
    ext::boolean timeout;
};
