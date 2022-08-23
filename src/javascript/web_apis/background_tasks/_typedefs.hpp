#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BACKGROUND_TASKS__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BACKGROUND_TASKS__TYPEDEFS_HPP

#include "ext/any.hpp"
#include "ext/functional.hpp"
#include "ext/map.hpp"
#include "ext/string.hpp"

namespace background_tasks {class idle_deadline;}

namespace background_tasks::detail
{
    using idle_request_options_t = ext::map<ext::string, ext::any>;
    using idle_request_callback_t = ext::function<void(idle_deadline*)>;
}

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BACKGROUND_TASKS__TYPEDEFS_HPP
