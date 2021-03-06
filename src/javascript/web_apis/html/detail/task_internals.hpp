#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_TASK_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_TASK_INTERNALS_HPP


#include <v8-platform.h>

namespace html::detail::task_internals
{
    auto timer_task_source()
            -> v8::Task&;

    auto dom_manipulation_task_source()
            -> v8::Task&;

    auto user_interaction_task_source()
            -> v8::Task&;

    auto networking_task_source()
            -> v8::Task&;

    auto history_traversal_task_source()
            -> v8::Task&;
}


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_TASK_INTERNALS_HPP
