#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BACKGROUND_TASKS_IDLE_DEADLINE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BACKGROUND_TASKS_IDLE_DEADLINE_HPP

#include "dom_object.hpp"
namespace background_tasks {class idle_deadline;}


#include "background_tasks/idle_deadline_private.hpp"
#include INCLUDE_INNER_TYPES(background_tasks)
#include INCLUDE_INNER_TYPES(hr_time)


class background_tasks::idle_deadline
        : public virtual dom_object
{
public constructors:
    idle_deadline();
    MAKE_PIMPL(idle_deadline);
    MAKE_V8_AVAILABLE;

public js_methods:
    auto time_remaining() -> hr_time::dom_high_res_time_stamp;

private js_properties:
    DEFINE_GETTER(did_timeout, ext::boolean);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BACKGROUND_TASKS_IDLE_DEADLINE_HPP
