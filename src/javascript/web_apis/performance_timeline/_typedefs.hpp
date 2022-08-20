#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PERFORMANCE_TIMELINE__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PERFORMANCE_TIMELINE__TYPEDEFS_HPP

#include "ext/any.hpp"
#include "ext/functional.hpp"
#include "ext/map.hpp"
#include "ext/string.hpp"
#include "ext/vector.hpp"
namespace performance_timeline {class performance_entry;}
namespace performance_timeline {class performance_observer;}

namespace performance_timeline::detail
{
    using performance_observer_callback_options_t = ext::map<ext::string, ext::any>;
    using performance_observer_callback_t = ext::function<ext::vector<performance_observer*>*, performance_observer*, performance_observer_callback_options_t>;
    using performance_observer_init_t = ext::map<ext::string, ext::any>;

    struct performance_entry_buffer_map_tuple_t;
    using performance_entry_buffer_t = ext::vector<performance_entry*>;
    using performance_entry_buffer_map_t = ext::map<ext::string, performance_entry_buffer_map_tuple_t>;
}

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PERFORMANCE_TIMELINE__TYPEDEFS_HPP
