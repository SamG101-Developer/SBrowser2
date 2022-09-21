#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BACKGROUND_TASKS_IDLE_DEADLINE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BACKGROUND_TASKS_IDLE_DEADLINE_HPP

#include "dom_object.hpp"
#include USE_INNER_TYPES(background_tasks)
#include USE_INNER_TYPES(hr_time)
namespace background_tasks {class idle_deadline;}


class background_tasks::idle_deadline
        : public virtual dom_object
{
public constructors:
    idle_deadline();

public js_methods:
    auto time_remaining() -> hr_time::dom_high_res_time_stamp;

public js_properties:
    ext::property<ext::boolean> did_timeout;

public cpp_members:
    MAKE_PIMPL(idle_deadline);
    MAKE_V8_AVAILABLE;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BACKGROUND_TASKS_IDLE_DEADLINE_HPP
