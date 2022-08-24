#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BACKGROUND_TASKS_IDLE_DEADLINE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BACKGROUND_TASKS_IDLE_DEADLINE_HPP

#include "dom_object.hpp"
#include USE_INNER_TYPES(background_tasks)
#include USE_INNER_TYPES(high_resolution_time)
namespace background_tasks {class idle_deadline;}


class background_tasks::idle_deadline
        : public virtual dom_object
{
public constructors:
    DOM_CTORS(idle_deadline);
    idle_deadline() = default;

public js_methods:
    auto time_remaining() -> high_resolution_time::detail::dom_high_res_time_stamp_t;

public js_properties:
    ext::property<ext::boolean> did_timeout;

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;

private cpp_properties:
    ext::boolean m_timeout;
    detail::deadline_time_algorithm_t m_get_deadline_time = [] {return 0.0;};
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BACKGROUND_TASKS_IDLE_DEADLINE_HPP
