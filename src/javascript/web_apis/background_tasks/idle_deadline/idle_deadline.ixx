module;
#include "ext/macros/annotations.hpp"
#include "ext/macros/macros.hpp"
#include "ext/macros/property.hpp"
#include "javascript/macros/expose.hpp"


export module apis.background_tasks.idle_deadline;
import apis.dom_object;
import apis.hr_time.types;

import ext.core;
import js.env.module_type;


DEFINE_PUBLIC_CLASS(background_tasks, idle_deadline)
        : virtual public dom_object
{
public constructors:
    idle_deadline();
    MAKE_PIMPL(idle_deadline);
    MAKE_V8_AVAILABLE(WINDOW);

public js_methods:
    auto time_remaining() -> hr_time::dom_high_res_time_stamp;

private js_properties:
    DEFINE_GETTER(did_timeout, ext::boolean);
};
