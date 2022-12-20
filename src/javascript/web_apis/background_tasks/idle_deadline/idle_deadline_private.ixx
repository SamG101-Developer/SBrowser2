module;
#include "ext/macros/pimpl.hpp"


export module apis.background_tasks.idle_deadline_private;
import apis.dom_object_private;

import ext.boolean;


DEFINE_PRIVATE_CLASS(background_tasks, idle_deadline)
        : virtual dom_object_private
{
public:
    MAKE_QIMPL(idle_deadline);

public:
    auto get_deadline_time() -> hr_time::dom_high_res_timestamp;

public:
    ext::boolean timeout;
};
