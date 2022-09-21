#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BACKGROUND_TASKS_IDLE_DEADLINE_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BACKGROUND_TASKS_IDLE_DEADLINE_PRIVATE_HPP

#include "ext/boolean.hpp"
#include "ext/keywords.hpp"
#include "ext/pimpl.hpp"
#include INCLUDE_INNER_TYPES(background_tasks)


DEFINE_PRIVATE_CLASS(background_tasks, idle_deadline)
{
    ext::boolean timeout;
    detail::deadline_time_algorithm_t get_deadline_time = [] {return 0.0;};
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BACKGROUND_TASKS_IDLE_DEADLINE_PRIVATE_HPP
