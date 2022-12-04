#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_WORKER_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_WORKER_INTERNALS_HPP



#include INCLUDE_INNER_TYPES(html)
namespace html::mixins {class window_or_worker_global_scope;}


namespace html::detail
{
    template <typename ...Args>
    auto timer_initialization_steps(
            mixins::window_or_worker_global_scope* global,
            detail::timer_handler_t&& handler,
            ext::number<long> timeout,
            Args&&... arguments,
            ext::boolean repeat,
            ext::number<int> previous_id = 0)
            -> ext::number<long>;
}


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_WORKER_INTERNALS_HPP
