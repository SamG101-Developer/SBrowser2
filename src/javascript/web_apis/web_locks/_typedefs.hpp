#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_LOCKS__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_LOCKS__TYPEDEFS_HPP

#include "ext/any.hpp"
#include "ext/map.hpp"
#include "ext/promise.hpp"
#include "ext/queue.hpp"
#include "ext/string.hpp"
namespace web_locks {class lock;}


namespace web_locks::detail
{
    struct lock_manager_t;
    struct lock_t;
    struct lock_request_t;

    enum class lock_mode_t {EXCLUSIVE, SHARED};

    using resource_name_t = ext::string;
    using lock_request_queue_t = ext::vector<std::unique_ptr<lock_request_t>>;
    using lock_request_queue_map_t = ext::map<resource_name_t, lock_request_queue_t>;
    using lock_options_t = ext::map<ext::string, ext::any>;
    using lock_manager_snapshot_t = ext::map<ext::string, ext::any>;
    using lock_info_t = ext::map<ext::string, ext::any>;
    using lock_granted_callback_t = ext::unique_function<ext::promise<ext::any>(lock* lock)>;
}

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_LOCKS__TYPEDEFS_HPP
